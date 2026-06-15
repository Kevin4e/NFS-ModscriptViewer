#include "SupportDialog.hpp"

#include "ui_SupportDialog.h"

SupportDialog::SupportDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SupportDialog)
{
    ui->setupUi(this);
    setFixedSize(size()); // Makes the window unresizable
    setWindowTitle("Support");
}

SupportDialog::~SupportDialog()
{
    delete ui;
}
