#pragma once
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "ui_dialog.h"

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private:
    Ui::Dialog ui;
};


#endif // DIALOG_H
