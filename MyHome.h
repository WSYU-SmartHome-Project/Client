#ifndef MYHOME_H
#define MYHOME_H

#include <QWidget>
#include <QTcpSocket.h>

namespace Ui {
class MyHome;
}

class MyHome : public   QWidget
{
    Q_OBJECT

public:
    explicit MyHome(QWidget *parent = 0);
    ~MyHome();
    void open_light();
    void close_light();
    void setText(QString text);
    void switch_mod(int mod);
    void open_kongtiao();
    void close_kongtiao();
    int closeType = 0;

 //声明一个槽函数，用于接收Widget对象中的数据
 public slots:
    void slot_myfun1(QString,QString);
    void on_pushButton_2_clicked();//返回按钮


 //界面切换信号
 signals:
    void signal_swap();

 private slots:
    void on_pushButton_clicked();//灯按钮槽函数
    void on_pushButton_3_clicked();//空调按钮
    void on_pushButton_4_clicked();//灯的模式变化


private:
    Ui::MyHome *ui;
    int led_on = 0;
    int kongtiao_on=0;
    int model=0;
    QTcpSocket *tcpsocket;//声明了一个名为tcpsocket的指向QTcpsocket类型的指针


};

#endif // MYHOME_H
