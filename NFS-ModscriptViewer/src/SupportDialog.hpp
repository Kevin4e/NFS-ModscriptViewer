#pragma once

#include <QDialog>

namespace Ui {
    class SupportDialog;
}

class SupportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SupportDialog(QWidget* parent = nullptr);
    ~SupportDialog();

private:
    Ui::SupportDialog* ui;
};