#pragma once

#include <QString>
#include <QStringList>

// Splits a command line into tokens while preserving quoted arguments
QStringList splitCommandLine(const QString& command);