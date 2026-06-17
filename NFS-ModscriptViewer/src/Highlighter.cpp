#include "Highlighter.hpp"

#include "Aliases.hpp"
#include "ColorFormats.hpp"
#include "Utils.hpp"

#include <QColor>
#include <QString>
#include <QStringList>
#include <QTextEdit>
#include <qtypes.h>
#include <QVector>

Highlighter::Highlighter(QTextEdit* editor, Language language)
    : QSyntaxHighlighter{ editor->document() }, currentLanguage{ language }, editor{ editor }
{}

Highlighter::Language Highlighter::getLanguage() const noexcept
{
    return currentLanguage;
}

void Highlighter::setLanguage(Language language) noexcept
{
    currentLanguage = language;
    rehighlight();
}

void Highlighter::setColors(const QString& text, const QStringList& tokens, const QColorList& colors) noexcept
{
    qsizetype pos{0};

    for (qsizetype i{0}; i < tokens.size(); ++i)
    {
        const QString& token{ tokens[i] };

        const qsizetype index{ text.indexOf(token, pos) };

        const qsizetype tokenLength{ token.length() };

        if (i < colors.size())
            setFormat(index, tokenLength, colors[i]);

        pos = index + tokenLength;
    }
}

void Highlighter::highlightBlock(const QString& text)
{
    if (text.isEmpty())
        return; // Empty text

    const qsizetype textLength{ text.length() };

    setFormat(0, textLength, 0xFFFFFF); // Make the whole text initially white

    const QStringList tokens{ splitCommandLine(text) }; // Split text in tokens

    if (tokens.isEmpty())
        return; // No tokens were found

    const qsizetype tokenCount{ tokens.size() };

    const QString& command{ tokens.first() }; // Get the first token of the line (command)

    switch (currentLanguage)
    {
        // Attribulator v2.0 rules
        case Language::Attribulator:
        {
            if (text.trimmed().startsWith('#')) {
                setFormat(0, textLength, Shared::CommentFormat); // Comment marker was found, highlight the whole line
                return;
            }

            const auto commandIt{ Attrib::rules.find(command) };

            if (commandIt == Attrib::rules.end())
                return; // Command not found

            QColorList colors{ commandIt->colors() };

            if (command == "update_field") {
                if (tokenCount >= 7)
                    colors.append({ Attrib::Arg::SubField, Attrib::Arg::SubField, Attrib::Arg::Value });
                else if (tokenCount >= 6)
                    colors.append({ Attrib::Arg::SubField, Attrib::Arg::Value });
                else
                    colors.append( Attrib::Arg::Value);
            }

            setColors(text, tokens, colors); // Command was found, highlight

            break;
        }

        // Binary rules
        case Language::Binary:
        {
            /* String Literal Highlighting */

            qsizetype pos{0};

            while ((pos = text.indexOf('"', pos)) != -1) {
                const qsizetype firstQuotationMark{ pos };

                if (firstQuotationMark == -1)
                    break;

                const qsizetype secondQuotationMark{ text.indexOf('"', firstQuotationMark + 1) };

                if (secondQuotationMark == -1)
                    break;

                setFormat(firstQuotationMark, secondQuotationMark - firstQuotationMark + 1, Shared::String);
                pos = secondQuotationMark + 1;
            }

            /* Comment Highlighting */

            const qsizetype commentIndex{ text.indexOf("//") };

            if (commentIndex != -1)
                setFormat(commentIndex, text.length(), { Shared::CommentFormat }); // Comment marker was found, highlight the whole line from where the comment starts

            /* Commands Highlighting */

            const auto commandIt{ Bin::rules.find(command) };

            if (commandIt == Bin::rules.end())
                return;

            QColorList colors;

            if (command == "bind_textures") {
                colors.append(commandIt->cmdColor);

                if (tokenCount > 1) {
                    const QString& type{ tokens[1] };

                    if (type == "negate" || type == "override" || type == "synchronize")
                        colors.append(commandIt->argColors);
                }
            }
            else if (command == "combobox") {
                colors = { commandIt->cmdColor };

                for (qsizetype i{1}; i < tokenCount - 1; ++i)
                    colors.append(Bin::Arg::Option);

                colors.append(Bin::Arg::Description);
            }
            else if (command == "if") { // WIP
                colors.append(commandIt->cmdColor);

                if (tokenCount > 1) {
                    const QString& condition{ tokens[1] };

                    if (condition == "collection_exists") {
                        colors.append({ Bin::Arg::Condition });
                    }
                    else if (condition == "string_exists") {
                        colors.append({ Bin::Arg::Condition });
                    }
                    else if (condition == "texture_exists") {
                        colors.append({ Bin::Arg::Condition });
                    }
                    else if (condition == "file_exists") {
                        colors.append({ Bin::Arg::Condition });
                    }
                    else if (condition == "directory_exists") {
                        colors.append({ Bin::Arg::Condition });
                    }
                    else if (condition == "collection_value_equals") {
                        colors.append({ Bin::Arg::Condition });
                    }
                }
            }
            else
                colors.append(commandIt->colors());

            setColors(text, tokens, colors);

            break;
        }
    }
}