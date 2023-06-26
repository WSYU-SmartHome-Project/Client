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
    void open_fengming();
    void close_fengming();
    int closeType = 0;
    void addTp();
    void subTp();

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
    void on_pushButton_5_clicked();//蜂鸣开关
    void on_add_clicked();
    void on_sub_clicked();


private:
    Ui::MyHome *ui;
    int led_on = 0;
    int kongtiao_on=0;
    int model=0;
    int fengming_on=0;
    QTcpSocket *tcpsocket;//声明了一个名为tcpsocket的指向QTcpsocket类型的指针
    int tp = 24;//空调温度；


};

#endif // MYHOME_H
