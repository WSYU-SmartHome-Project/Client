#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "MyHome.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals :
    void signal_mysignall(QString ip,QString port);

public slots:
    void slot_swap();
    void on_connected();

private slots:
    void on_pushButton_clicked();


private :
    Ui::Widget *ui;
    MyHome *myhomep;

};

#endif // WIDGET_H
