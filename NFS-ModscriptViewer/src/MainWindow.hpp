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
    void loadFile(const QString& filePath);
    void writeTextToFile(const QString& filePath);
    Highlighter* getHighlighter() const noexcept;

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void openFile();
    void saveFile();
    void saveFileAs();
    void setAttribulator() noexcept;
    void setBinary() noexcept;
    void increaseLineSpacing() noexcept;
    void decreaseLineSpacing() noexcept;
    void setCustomLineSpacing();
    void showAboutDialog();
    void showSupportDialog();
    void killProcess(const QString& exeName) const noexcept;

    void exit() noexcept;
    void applyLineSpacing() const noexcept;
    void updateLineNumbers() noexcept;

private:
    void setupUi();
    void setupConnections();
    void setupShortcuts();
    void updateTitle();

private:
    static const QString APP_NAME;
    static const QString APP_DISPLAY_NAME;

    Ui::MainWindow* ui;
    QString currentFilePath;  // Stores the current file path
    Highlighter* highlighter;  // Highlighter instance
    qreal lineSpacingValue{ 20.0 };
    int linesCount;
};