#include "Utils.hpp"

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QWidget>

bool isFileModified(const QString& currentText, const QString& filePath, QWidget* parent) {
    QFile file{ filePath };

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return true; // Se non riesco ad aprire il file, considero che sia modificato (o gestisci l'errore come preferisci)

    QTextStream in{ &file };
    const QString fileContent{ in.readAll() };
    file.close();

    return currentText != fileContent;
}

QMessageBox::StandardButton ProceedWithUnsavedChangesUserChoice(QWidget* parent) {
    return QMessageBox::question(
        parent,
        "Unsaved changes",
        "There are unsaved changes. Are you sure you want to proceed?",
        QMessageBox::Yes | QMessageBox::No
    );
}
