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
    static void closeLogin(){
        Widget::close();
    };

signals :
    void signal_mysignall(QString ip,int port);

public slots:
    void slot_swap();

private slots:
    void on_pushButton_clicked();


private :
    Ui::Widget *ui;
    MyHome *myhomep;

};

#endif // WIDGET_H