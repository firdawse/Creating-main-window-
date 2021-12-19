#ifndef SELECT_H
#define SELECT_H

#include <QDialog>

namespace Ui {
class selectCol;
}

class select : public QDialog
{
    Q_OBJECT

public:
    explicit select(QWidget *parent = nullptr);
    ~select();
    QString getLoaction() const;

private:
    Ui::selectCol *ui;
};

#endif // SELECT_H
