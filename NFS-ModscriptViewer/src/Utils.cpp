#include "Utils.hpp"

#include <QChar>
#include <QString>
#include <QStringList>

QStringList splitCommandLine(const QString& command) {
    QStringList tokens{};
    QString currentToken{};
    bool insideQuotes{ false };

    for (QChar c : command) {
        if (c == '"') {
            insideQuotes = !insideQuotes;
            currentToken.append(c);
        }
        else if (c.isSpace() && !insideQuotes) {
            if (!currentToken.isEmpty()) {
                tokens.append(currentToken);
                currentToken.clear();
            }
        }
        else
            currentToken.append(c);
    }

    if (!currentToken.isEmpty())
        tokens.append(currentToken);

    return tokens;
}