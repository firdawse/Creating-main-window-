#ifndef GODIALOLOG_H
#define GODIALOLOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QString getCell()const;//getter pour le text du lineEdit

private:
    Ui::Dialog *ui;
};

#endif // GODIALOLOG_H
