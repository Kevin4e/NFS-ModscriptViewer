#include "MainWindow.hpp"

#include "AboutDialog.hpp"
#include "Highlighter.hpp"
#include "SupportDialog.hpp"
#include "version.hpp"

#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QKeySequence>
#include <QMessageBox>
#include <QProcess>
#include <QTextEdit>

#include "ui_MainWindow.h"

static constexpr const char* FILE_FILTER{ "NFS Modscripts (*.nfsms *.end);;All Files (*.*)" };

// --- private fields --- //

const QString MainWindow::APP_NAME{ "NFS-ModscriptViewer" };

const QString MainWindow::APP_DISPLAY_NAME{ APP_NAME + " v" + APP_VERSION };

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{ parent }, ui{ new Ui::MainWindow }
{
    ui->setupUi(this);

    setCentralWidget(ui->textEdit);

    highlighter = new Highlighter(ui->textEdit);

    setupUi();
    setupConnections();
    setupShortcuts();

    setWindowTitle(APP_DISPLAY_NAME);
}

MainWindow::~MainWindow() noexcept
{
    delete ui;
}

// --- public methods --- //

void MainWindow::loadFile(const QString& filePath)
{
    QFile file{ filePath };

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    currentFilePath = filePath;

    savedContent = QString::fromUtf8(file.readAll());

    ui->textEdit->setPlainText(savedContent);

    updateTitle();

    QFileInfo info{ filePath };
    const QString extension{ info.suffix() }; // without the dot

    if (extension == "nfsms")
        setAttribulator();
    else if (extension == "end")
        setBinary();
}

void MainWindow::writeTextToFile(const QString& filePath)
{
    QFile file{ filePath };
    if (!file.open(QIODevice::WriteOnly))
        return;

    file.write(ui->textEdit->toPlainText().toUtf8());
}

// --- protected methods --- //

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (ui->textEdit->toPlainText().isEmpty()) {
        event->accept();
        return; // Close if no text
    }

    if (!isCurrentFileModified()) {
        event->accept();
        return; // Close if saved
    }

    const QMessageBox::StandardButton reply
    {
        QMessageBox::question
        (
            this,
            "Unsaved changes",
            "There are unsaved changes. Are you sure you want to proceed?",
            QMessageBox::Yes | QMessageBox::No
        )
    };

    if (reply == QMessageBox::Yes)
        event->accept(); // User chose "Yes", close the window
    else
        event->ignore(); // User chose "No", don't close
}

// --- private slots methods --- //

void MainWindow::openFile()
{
    const QString filePath
    {
        QFileDialog::getOpenFileName(
            this,
            "Open File",
            {},
            FILE_FILTER
        )
    };

    if (filePath.isEmpty())
        return;

    loadFile(filePath);
}

void MainWindow::saveFile()
{
    if (currentFilePath.isEmpty())
        saveFileAs();
    else {
        writeTextToFile(currentFilePath);
        savedContent = ui->textEdit->toPlainText();
        updateTitle();
    }
}

void MainWindow::saveFileAs()
{
    const QString filePath
    {
        QFileDialog::getSaveFileName(
            this,
            "Save File",
            {},
            FILE_FILTER
        )
    };

    if (filePath.isEmpty())
        return;

    currentFilePath = filePath;

    writeTextToFile(currentFilePath);

    updateTitle();
}

void MainWindow::setAttribulator() noexcept
{
    highlighter->setLanguage(Highlighter::Language::Attribulator);
}

void MainWindow::setBinary() noexcept
{
    highlighter->setLanguage(Highlighter::Language::Binary);
}

void MainWindow::increaseLineSpacing() noexcept
{
    if (lineSpacingValue == maxLineSpacingValue)
        return;

    lineSpacingValue += 1.0;
    applyLineSpacing();
}

void MainWindow::decreaseLineSpacing() noexcept
{
    if (lineSpacingValue == minLineSpacingValue)
        return;

    lineSpacingValue -= 1.0;
    applyLineSpacing();
}

void MainWindow::setCustomLineSpacing()
{
    QInputDialog dialog{ this };

    dialog.setWindowTitle("Set Line Spacing");
    dialog.setLabelText("Enter the line spacing (15.0 - 100.0):");
    dialog.setInputMode(QInputDialog::DoubleInput);
    dialog.setDoubleMinimum(minLineSpacingValue);
    dialog.setDoubleMaximum(maxLineSpacingValue);
    dialog.setDoubleDecimals(1);
    dialog.setDoubleValue(lineSpacingValue);

    if (dialog.exec() == QDialog::Accepted) {
        lineSpacingValue = dialog.doubleValue();
        applyLineSpacing();
    }
}

void MainWindow::showAboutDialog()
{
    AboutDialog aboutDialog(this);
    aboutDialog.exec();
}

void MainWindow::showSupportDialog()
{
    SupportDialog supportDialog(this);
    supportDialog.exec();
}

void MainWindow::updateLineNumbers() noexcept
{
    linesCount = ui->textEdit->document()->blockCount();
    statusBar()->showMessage("Lines: " + QString::number(linesCount));
}

// --- private methods --- //

void MainWindow::setupUi()
{
    setStyleSheet(R"(
        QTextEdit {
            border: none;
            background-color: rgb(23, 23, 23);
        }
    )");
}

void MainWindow::setupConnections()
{
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::saveFileAs);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    connect(ui->actionAttribulator, &QAction::triggered, this, &MainWindow::setAttribulator);
    connect(ui->actionBinary, &QAction::triggered, this, &MainWindow::setBinary);

    connect(ui->actionIncrease, &QAction::triggered, this, &MainWindow::increaseLineSpacing);
    connect(ui->actionDecrease, &QAction::triggered, this, &MainWindow::decreaseLineSpacing);
    connect(ui->actionSet_Spacing, &QAction::triggered, this, &MainWindow::setCustomLineSpacing);

    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::showAboutDialog);
    connect(ui->actionSupport, &QAction::triggered, this, &MainWindow::showSupportDialog);

    connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this, &MainWindow::updateLineNumbers);

    connect(ui->actionSpeedDotExe, &QAction::triggered,
            this, [this] { killProcess("speed.exe"); });

    connect(ui->actionNFSCDotExe, &QAction::triggered,
            this, [this] { killProcess("nfsc.exe"); });

    connect(ui->actionNFSDotExe, &QAction::triggered,
            this, [this] { killProcess("NFS.exe"); });

    connect(ui->textEdit, &QTextEdit::textChanged,
            this, [this] { updateTitle(); });
}

void MainWindow::setupShortcuts()
{
    ui->actionOpen->setShortcut(QKeySequence("Ctrl+O")); // Ctrl+O -> Open
    ui->actionSave->setShortcut(QKeySequence("Ctrl+S")); // Ctrl+S -> Save
    ui->actionSave_as->setShortcut(QKeySequence("Ctrl+Shift+S")); // Ctrl+Shift+S -> Save as
    ui->actionIncrease->setShortcut(QKeySequence("Ctrl+I")); // Ctrl+I -> Increase line spacing
    ui->actionDecrease->setShortcut(QKeySequence("Ctrl+D")); // Ctrl+D -> Decrease line spacing
}

void MainWindow::updateTitle()
{
    if (currentFilePath.isEmpty())
        setWindowTitle(APP_DISPLAY_NAME);
    else {
        if (isCurrentFileModified())
            setWindowTitle(APP_DISPLAY_NAME + " | *" +  currentFilePath);
        else
            setWindowTitle(APP_DISPLAY_NAME + " | " +  currentFilePath);
    }
}

void MainWindow::killProcess(const QString& exeName) const noexcept
{
    QString cmd;

    #ifdef Q_OS_WIN // Windows
        cmd = QString("taskkill /IM %1 /F").arg(exeName);

    #else // Linux & macOS
        cmd = QString("killall -9 %1").arg(exeName);

    #endif

    QProcess::startDetached(cmd);
}

bool MainWindow::isCurrentFileModified() const noexcept
{
    return savedContent != ui->textEdit->toPlainText();
}

void MainWindow::applyLineSpacing() const noexcept
{
    QTextBlockFormat format;
    format.setLineHeight(lineSpacingValue, QTextBlockFormat::FixedHeight);

    QTextCursor cursor(ui->textEdit->document());
    cursor.select(QTextCursor::Document);
    cursor.setBlockFormat(format);
}