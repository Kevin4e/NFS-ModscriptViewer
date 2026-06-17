#pragma once

#include "Aliases.hpp"

#include <QString>
#include <QStringList>
#include <QSyntaxHighlighter>
#include <QVector>

#include <cstdint>

class QTextEdit;

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    enum class Language : int8_t {
        Attribulator,
        Binary
    };

    Highlighter(QTextEdit* editor, Language language = Language::Attribulator); // Set "Attribulator" to default language

    // Returns the current language
    Language getLanguage() const noexcept;

    // Sets the current language
    void setLanguage(Language language) noexcept;

protected:
    // Applies language-specific syntax highlighting to a single text block
    void highlightBlock(const QString& text) override;

private:
    // Applies formatting to each token occurrence in order.
    // Each token is searched in the text starting from the last match position,
    // and the corresponding color is applied if present.
    void setColors(const QString& text, const QStringList& words, const QColorList& colors) noexcept;

private:
    Language currentLanguage;
    QTextEdit* editor;
};