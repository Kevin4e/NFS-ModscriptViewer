#pragma once

#include <QMessageBox>
#include <QString>

class QWidget;

bool isFileModified(const QString& currentText, const QString& filePath, QWidget* parent);
QMessageBox::StandardButton ProceedWithUnsavedChangesUserChoice(QWidget* parent);