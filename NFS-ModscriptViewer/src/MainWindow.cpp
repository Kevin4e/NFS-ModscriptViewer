#include "MainWindow.hpp"

#include "AboutDialog.hpp"
#include "Highlighter.hpp"
#include "SupportDialog.hpp"
#include "Utils.hpp"
#include "version.hpp"

#include <QFile>
#include <QFileDialog>
#include <QInputDialog>
#include <QKeySequence>
#include <QProcess>
#include <QTextEdit>

#include "ui_MainWindow.h"

static constexpr const char* FILE_FILTER{ "NFS Modscripts (*.nfsms *.end);;All Files (*.*)" };

// --- private fields --- //

const QString MainWindow::APP_NAME{ "NFS-ModscriptViewer" };
const QString MainWindow::APP_DISPLAY_NAME{ APP_NAME + ' ' + APP_VERSION };

// constructor / destructor
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow{parent}, ui{new Ui::MainWindow}
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
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    currentFilePath = filePath;

    updateTitle();

    ui->textEdit->setPlainText(QString::fromUtf8(file.readAll()));

    QFileInfo info(filePath);
    QString extension = info.suffix(); // without the dot

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

Highlighter* MainWindow::getHighlighter() const noexcept
{
    return highlighter;
}

// --- protected methods --- //

void MainWindow::closeEvent(QCloseEvent* event)
{
    if (ui->textEdit->toPlainText().isEmpty()) {
        event->accept(); // Close if no text
        return;
    }

    if (!isFileModified(ui->textEdit->toPlainText(), currentFilePath, this)) {
        event->accept(); // Close if saved
        return;
    }

    const QMessageBox::StandardButton reply{ ProceedWithUnsavedChangesUserChoice(this) };

    if (reply == QMessageBox::Yes)
        event->accept(); // Close the window
    else
        event->ignore(); // User chose "No", don't close
}

// --- private slots methods --- //

// Creates an open file dialog, then triggers the file loader
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

// Attempts to save the file.
// If no file is opened, it triggers saveFileAs();
// otherwise, it writes the text to the current file
void MainWindow::saveFile()
{
    if (currentFilePath.isEmpty())
        saveFileAs();
    else
        writeTextToFile(currentFilePath);
}

// Prompts the user for a new file path,
// updates the current file state, and writes the text
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

    updateTitle();

    writeTextToFile(currentFilePath);
}

// Sets the language to Attribulator
void MainWindow::setAttribulator() noexcept
{
    highlighter->setLanguage(Highlighter::Language::Attribulator);
}

// Sets the language to Binary
void MainWindow::setBinary() noexcept
{
    highlighter->setLanguage(Highlighter::Language::Binary);
}

// Increases line spacing by the specified value
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

    // Cambia l'icona qui
    dialog.setWindowIcon(QIcon{ ":/icons/spacing.png" });

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

void MainWindow::killProcess(const QString& exeName) const noexcept
{
    QString cmd;
    #ifdef Q_OS_WIN
        cmd = QString("taskkill /IM %1 /F").arg(exeName);
    #else
        cmd = QString("killall -9 %1").arg(exeName);
    #endif

    QProcess::startDetached(cmd);
}

void MainWindow::exit() noexcept
{
    close(); // Call the close function.
}

void MainWindow::applyLineSpacing() const noexcept
{
    QTextBlockFormat format;
    format.setLineHeight(lineSpacingValue, QTextBlockFormat::FixedHeight);

    QTextCursor cursor(ui->textEdit->document());
    cursor.select(QTextCursor::Document);
    cursor.setBlockFormat(format);
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
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::exit);

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
    else
        setWindowTitle(APP_DISPLAY_NAME + " | " + currentFilePath);
}