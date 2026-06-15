#include "AboutDialog.hpp"
#include "version.hpp"

#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setFixedSize(size()); // Makes the window unresizable
    setWindowTitle("About");

    ui->lblVersion->setText(QString("Version %1").arg(APP_VERSION));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
