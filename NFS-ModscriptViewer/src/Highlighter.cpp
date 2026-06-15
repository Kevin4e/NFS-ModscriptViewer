#include "Highlighter.hpp"

#include "ColorFormats.hpp"

#include <QColor>
#include <QMap>
#include <QRegularExpression>
#include <QString>
#include <QStringlist>
#include <QTextEdit>
#include <qtypes.h>
#include <QVector>

Highlighter::Highlighter(QTextEdit* editor, Language language)
    : QSyntaxHighlighter{ editor->document() }, currentLanguage{ language }, editor{ editor }
{
    setLanguage(language);
}

void Highlighter::setLanguage(Language language) noexcept
{
    currentLanguage = language;
    rehighlight();
}

Highlighter::Language Highlighter::getLanguage() const noexcept
{
    return currentLanguage;
}

void Highlighter::setColors(const QString& text, const QStringList& words, const QVector<QColor>& colors) noexcept
{
    qsizetype pos{0};

    for (qsizetype i{0}; i < words.size(); ++i)
    {
        const qsizetype index{ text.indexOf(words[i], pos) };

        if (i < colors.size())
            setFormat(index, words[i].length(), colors[i]);

        pos = index + words[i].length();
    }
}

void Highlighter::highlightBlock(const QString& text)
{
    if (text.isEmpty())
        return;

    const qsizetype textLength{ text.length() };
    setFormat(0, textLength, 0xFFFFFF); // Make the whole text initially white 

    // Split text without comments in words
    const QStringList words{ text.split(QRegularExpression("\\s+")) };
    const qsizetype wordsSize{ words.size() };

    const QString command{ words.first() }; // Get the first word of the line (command)

    // Attribulator v2.0 rules
    if (currentLanguage == Language::Attribulator) {
        if (text.front() == '#')
            setFormat(0, textLength, Others::CommentFormat);

        else if (command == "update_field") {
            if (wordsSize >= 7 && !words[6].isEmpty()) {

                setColors(text, words,
                        {
                            Attrib::Cmd::Field,
                            Attrib::Arg::Class,
                            Attrib::Arg::Node,
                            Attrib::Arg::Field,
                            Attrib::Arg::SubFields,
                            Attrib::Arg::SubFields,
                            Attrib::Arg::Value
                        }
                );
            }
            else if (wordsSize >= 6 && !words[5].isEmpty()) {
                setColors(text, words,
                        {
                            Attrib::Cmd::Field,
                            Attrib::Arg::Class,
                            Attrib::Arg::Node,
                            Attrib::Arg::Field,
                            Attrib::Arg::SubFields,
                            Attrib::Arg::Value
                        }
                );
            }
            else {
                setColors(text, words,
                        {
                            Attrib::Cmd::Field,
                            Attrib::Arg::Class,
                            Attrib::Arg::Node,
                            Attrib::Arg::Field,
                            Attrib::Arg::Value
                        }
                );
            }
        }
        else {
            const auto commandIt{ Attrib::rules.find(command) };

            if (commandIt != Attrib::rules.end())
                setColors(text, words, commandIt->colors()); // Command was found, highlight
        }
    }

    // Binary rules
    else {
        const qsizetype commandLength{ command.length() };

        if (commandLength >= 2 && command[0] == '/' && command[1] == '/')
            setFormat(0, textLength, Others::CommentFormat);

        const auto commandIt{ Bin::rules.find(command) };

        if (commandIt != Bin::rules.end()) {
            bool highlightCommand{ false };
            bool highlightAll{ true };

            if (command == "bind_textures") {
                if (words.size() <= 1) {
                    highlightCommand = true;
                    highlightAll = false;
                }
                else {
                    const QString& type{ words[1] };

                    if (type == "negate" || type == "override" || type == "synchronize")
                        highlightAll = true;
                    else
                        highlightCommand = true;
                }
            }

            if (highlightCommand)
                setColors(text, words, { commandIt->cmdColor });
            else if (highlightAll)
                setColors(text, words, commandIt->colors());
        }
    }
}