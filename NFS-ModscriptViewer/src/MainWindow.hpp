#pragma once

#include <QMainWindow>
#include <QString>

class Highlighter;

constexpr qreal minLineSpacingValue{ 15.0 };
constexpr qreal maxLineSpacingValue{ 100.0 };

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() noexcept;

    // Loads the specified file into the document,
    // updates the 'savedContent' member and the window title,
    // and sets the language based on the file extension
    void loadFile(const QString& filePath);

    // Writes the current text to the currently loaded file
    void writeTextToFile(const QString& filePath);

protected:
    // Handles window close event.
    //
    // Closes immediately if:
    // - editor is empty
    // - content has not been modified since last save
    //
    // Otherwise prompts the user to confirm closing when there are unsaved changes.
    void closeEvent(QCloseEvent* event) override;

private slots:
    // Creates an open file dialog, then triggers the file loader
    void openFile();

    // Attempts to save the file.
    // If no file is opened, it triggers saveFileAs();
    // otherwise, it writes the text to the current file
    void saveFile();

    // Prompts the user for a new file path,
    // updates the current file state, and writes the text
    void saveFileAs();

    // Sets the language to Attribulator
    void setAttribulator() noexcept;

    // Sets the language to Binary
    void setBinary() noexcept;

    // Increases line spacing by 1.0
    void increaseLineSpacing() noexcept;

    // Decreases line spacing by 1.0
    void decreaseLineSpacing() noexcept;

    // Opens an input dialog and applies the line spacing
    // based on the user's input
    void setCustomLineSpacing();

    // Opens the About dialog modally
    void showAboutDialog();

    // Opens the Support dialog modally
    void showSupportDialog();

    // Updates and displays the current line count in the status bar
    void updateLineNumbers() noexcept;

private:
    // Applies custom stylesheet to the main UI
    void setupUi();

    // Connects UI actions to their corresponding slots and handlers
    void setupConnections();

    // Assigns keyboard shortcuts to UI actions
    void setupShortcuts();

    // Updates the window title based on the current file state
    void updateTitle();

    // Terminates a process by executable name using platform-specific commands
    void killProcess(const QString& exeName) const noexcept;

    // Checks if the current file is modified
    bool isCurrentFileModified() const noexcept;

    // Applies the line spacing to the document
    void applyLineSpacing() const noexcept;

private:
    static const QString APP_NAME;
    static const QString APP_DISPLAY_NAME;

    Ui::MainWindow* ui;
    QString currentFilePath;  // Stores the current file path
    Highlighter* highlighter;  // Highlighter instance
    qreal lineSpacingValue{ 20.0 };
    int linesCount{0};
    QString savedContent;
};