#pragma once

#include <QString>
#include <QStringList>
#include <QSyntaxHighlighter>
#include <QVector>

#include <cstdint>

class QTextEdit;

class Highlighter : public QSyntaxHighlighter {
    Q_OBJECT

public:
    enum class Language : int8_t {
        Attribulator,
        Binary
    };

private:
    void setColors(const QString& text, const QStringList& words, const QVector<QColor>& colors) noexcept;

    Language currentLanguage;
    QTextEdit* editor;

protected:
    void highlightBlock(const QString& text) override;

public:
    Highlighter(QTextEdit* editor, Language language = Language::Attribulator);   // Set "Attribulator" to default language

    Language getLanguage() const noexcept;
    void setLanguage(Language mode) noexcept;
};