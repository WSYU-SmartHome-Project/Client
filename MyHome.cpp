#include "MyHome.h"
#include "ui_MyHome.h"
#include "rest.h"
#include "websocketclient.h"

MyHome::MyHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyHome)
{
    ui->setupUi(this);

}

MyHome::~MyHome()
{
    delete ui;
}

//槽函数的定义
 void MyHome::slot_myfun1(QString ip, QString port)
 {
     ui->textEdit->insertPlainText("地址："+ip+"；端口号："+port+"\n");
 }

 //开灯关灯

 void MyHome::on_pushButton_clicked()
 {
     if(led_on==0)
     {
         Rest *open_light = new Rest();
         open_light->command = 600;
         open_light->message = "开灯";
         open_light->success = true;
         WebSocketClient::dataRecvWS->sendTextMessage(open_light->toJson());
     }
     else
     {
         Rest *open_light = new Rest();
         open_light->command = 601;
         open_light->message = "关灯";
         open_light->success = true;
         WebSocketClient::dataRecvWS->sendTextMessage(open_light->toJson());
     }
 }

 //空调开关

 void MyHome::on_pushButton_3_clicked()
 {
     if(kongtiao_on==0)
     {

         Rest *kongtiao = new Rest();
         kongtiao->command = 700;
         kongtiao->message = "打开空调";
         kongtiao->success = true;
         WebSocketClient::dataRecvWS->sendTextMessage(kongtiao->toJson());
     }
     else
     {

         Rest *kongtiao = new Rest();
         kongtiao->command = 701;
         kongtiao->message = "关闭空调";
         kongtiao->success = true;
         WebSocketClient::dataRecvWS->sendTextMessage(kongtiao->toJson());

     }
 }
 void MyHome::on_pushButton_5_clicked()
 {
     if(fengming_on==0)
     {

         Rest *kongtiao = new Rest();
         kongtiao->command = 702;
         kongtiao->message = "打开蜂鸣";
         kongtiao->success = true;
         WebSocketClient::dataRecvWS->sendTextMessage(kongtiao->toJson());
     }
     else
     {

         Rest *kongtiao = new Rest();
         kongtiao->command = 703;
         kongtiao->message = "关闭蜂鸣";
         kongtiao->success = true;
         WebSocketClient::dataRecvWS->sendTextMessage(kongtiao->toJson());

     }
 }
 //灯的模式变化

 void MyHome::on_pushButton_4_clicked()
 {
     if(led_on==0)
     {
         ui->textEdit->insertPlainText("开灯才可以切换模式\n");
         QString data1="需要开灯才能调换模式\n";
     }
     if(led_on==1){
     Rest *mod = new Rest();

     if(model%3==0)
     {
         mod->command = 610;
         mod->message = "切换模式一";
         mod->success = true;
         WebSocketClient::dataRecvWS->sendTextMessage(mod->toJson());

     }
     if(model%3==1)
     {
         mod->command = 620;
         mod->message = "切换模式二";
         mod->success = true;
         WebSocketClient::dataRecvWS->sendTextMessage(mod->toJson());
     }
     if(model%3==2)
     {

         mod->command = 630;
         mod->message = "切换模式三";
         mod->success = true;
         WebSocketClient::dataRecvWS->sendTextMessage(mod->toJson());
     }
     model++;
     }

 }

 //返回按钮

 void MyHome::on_pushButton_2_clicked()
 {
     closeType = 1;
     emit signal_swap();
     WebSocketClient::dataRecvWS->close();
 }

 void MyHome::open_light(){

     ui->pushButton->setStyleSheet("border-image: url(:/image/button _light open.png)");
     ui->label_2->setStyleSheet("border-image: url(:/image/light _on.png)");
     ui->label->setStyleSheet("border-image: url(:/image/home.png)");

     led_on=1;

 }

 void MyHome::close_light(){
     ui->pushButton->setStyleSheet("border-image: url(:/image/butoon _light close.png)");
     ui->label_2->setStyleSheet("border-image: url(:/image/light _off.png)");
     ui->label->setStyleSheet("border-image: url(:/image/home_dark.png)");

     led_on=0;
 }
 void MyHome::setText(QString text){
     ui->textEdit->insertPlainText(text);
 }

 void MyHome::switch_mod(int mod){
     if(led_on==0)
     {
         ui->textEdit->insertPlainText("开灯才可以切换模式\n");
         QString data1="需要开灯才能调换模式\n";
     }
     if(led_on==1){
     if(mod==0)
     {
         ui->label_2->setStyleSheet("border-image: url(:/image/light_blue.png)");
         ui->label->setStyleSheet("border-image: url(:/image/home_blue.png)");

     }
     if(mod==1)
     {
         ui->label_2->setStyleSheet("border-image: url(:/image/light_yellow.png)");
         ui->label->setStyleSheet("border-image: url(:/image/home_yellow.png)");

     }
     if(mod==2)
     {
         ui->label_2->setStyleSheet("border-image: url(:/image/light_orange.png)");
         ui->label->setStyleSheet("border-image: url(:/image/home_orange.png)");

     }


     }
 }

 void MyHome::open_kongtiao(){
     ui->pushButton_3->setStyleSheet("border-image: url(:/image/button_kongtiao_open.png)");
     ui->label_4->setStyleSheet("border-image: url(:/image/kongtiao_open.png)");

     kongtiao_on=1;
 }

 void MyHome::close_kongtiao(){
     ui->pushButton_3->setStyleSheet("border-image: url(:/image/button_kongtiao_close.png)");
     ui->label_4->setStyleSheet("border-image: url(:/image/kongtiao_close(1).png)");

     kongtiao_on=0;
 }
 void MyHome::open_fengming(){
     ui->pushButton_5->setStyleSheet("border-image: url(:/image/button_kongtiao_open.png)");
     ui->label_5->setStyleSheet("border-image: url(:/image/fengming_open.png)");

     fengming_on=1;
 }

 void MyHome::close_fengming(){
     ui->pushButton_6->setStyleSheet("border-image: url(:/image/button_kongtiao_close(1).png)");
     ui->label_5->setStyleSheet("border-image: url(:/image/fengming_close.png)");

     fengming_on=0;
 }
