#include "MyHome.h"
#include "ui_MyHome.h"

MyHome::MyHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyHome)
{
    ui->setupUi(this);

    tcpsocket = new QTcpSocket;//通过new运算符创建新的QTcpsocket对象，并将其分配给tcpsocket指针

    //判断是否连接成功
    connect(tcpsocket,&QTcpSocket::connected,this,[=](){ui->label_3->setText("connect ok");});
}

MyHome::~MyHome()
{
    delete ui;
}

//槽函数的定义
 void MyHome::slot_myfun1(QString ip, int port)
 {
     //连接服务器
     tcpsocket->connectToHost(ip,port);

     int i = 100000000;//延时等待服务器链接
     while(i--);
 }

 //开灯关灯

 void MyHome::on_pushButton_clicked()
 {
     if(led_on==0)
     {
         ui->pushButton->setStyleSheet("border-image: url(:/image/button _light open.png)");
         ui->label_2->setStyleSheet("border-image: url(:/image/light _on.png)");
         ui->label->setStyleSheet("border-image: url(:/image/home.png)");

         ui->textEdit->insertPlainText("led_on\n");

         led_on=1;
         QString data1="led_on\n";
         tcpsocket->write(data1.toUtf8());
     }
     else
     {
         ui->pushButton->setStyleSheet("border-image: url(:/image/butoon _light close.png)");
         ui->label_2->setStyleSheet("border-image: url(:/image/light _off.png)");
         ui->label->setStyleSheet("border-image: url(:/image/home_dark.png)");

         ui->textEdit->insertPlainText("led_off\n");

         led_on=0;
         QString data1="led_off\n";
         tcpsocket->write(data1.toUtf8());
     }
 }

 //空调开关

 void MyHome::on_pushButton_3_clicked()
 {
     if(kongtiao_on==0)
     {
         ui->pushButton_3->setStyleSheet("border-image: url(:/image/button_kongtiao_open.png)");
         ui->label_4->setStyleSheet("border-image: url(:/image/kongtiao_open.png)");

         ui->textEdit->insertPlainText("kongtiao_on\n");

         kongtiao_on=1;
         QString data1="kongtiao_on\n";
         tcpsocket->write(data1.toUtf8());
     }
     else
     {
         ui->pushButton_3->setStyleSheet("border-image: url(:/image/button_kongtiao_close.png)");
         ui->label_4->setStyleSheet("border-image: url(:/image/kongtiao_close(1).png)");

         ui->textEdit->insertPlainText("kongtiao_off\n");

         kongtiao_on=0;
         QString data1="led_off\n";
         tcpsocket->write(data1.toUtf8());
     }
 }

 //灯的模式变化

 void MyHome::on_pushButton_4_clicked()
 {
     if(led_on==0)
     {
         ui->textEdit->insertPlainText("开灯才可以切换模式\n");
         QString data1="需要开灯才能调换模式\n";
         tcpsocket->write(data1.toUtf8());
     }
     if(led_on==1){
     if(model%3==0)
     {
         ui->label_2->setStyleSheet("border-image: url(:/image/light_blue.png)");
         ui->label->setStyleSheet("border-image: url(:/image/home_blue.png)");

         ui->textEdit->insertPlainText("led_blue\n");
         QString data1="led_blue\n";
         tcpsocket->write(data1.toUtf8());
     }
     if(model%3==1)
     {
         ui->label_2->setStyleSheet("border-image: url(:/image/light_yellow.png)");
         ui->label->setStyleSheet("border-image: url(:/image/home_yellow.png)");

         ui->textEdit->insertPlainText("led_yellow\n");
         QString data1="led_yellow\n";
         tcpsocket->write(data1.toUtf8());
     }
     if(model%3==2)
     {
         ui->label_2->setStyleSheet("border-image: url(:/image/light_orange.png)");
         ui->label->setStyleSheet("border-image: url(:/image/home_orange.png)");

         ui->textEdit->insertPlainText("led_orange\n");
         QString data1="led_orange\n";
         tcpsocket->write(data1.toUtf8());
     }


     }

model++;

 }


 //返回按钮

 void MyHome::on_pushButton_2_clicked()
 {
     emit signal_swap();
 }
