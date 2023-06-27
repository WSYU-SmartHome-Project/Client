#include "MyHome.h"
#include "ui_MyHome.h"
#include "rest.h"
#include "websocketclient.h"

MyHome::MyHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyHome)
{
    ui->setupUi(this);
    ui->tp_display->close();
    ui->tp_display->setSegmentStyle(QLCDNumber::Flat);



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

 void MyHome::on_add_clicked(){
     if(kongtiao_on == 1){

         Rest *command = new Rest();
         command->command = 8;
         command->message = "温度增加";
         command->success = true;
         WebSocketClient::dataRecvWS->sendTextMessage(command->toJson());
     }else{
         ui->textEdit->insertPlainText("请先打开空调\n");
     }


 }

 void MyHome::on_sub_clicked(){
     if(kongtiao_on == 1){
         Rest *command = new Rest();
         command->command = 2;
         command->message = "温度降低";
         command->success = true;
         WebSocketClient::dataRecvWS->sendTextMessage(command->toJson());
     }else{
         ui->textEdit->insertPlainText("请先打开空调\n");
     }

 }

 void MyHome::addTp(){
     ++tp;
     ui->tp_display->display(tp);
     Rest *command = new Rest();
     command->command = 101;
     QString tp_s = QString::number(tp);
     command->message = tp_s;
     command->success = true;
     WebSocketClient::dataRecvWS->sendTextMessage(command->toJson());
 }

 void MyHome::subTp(){
     --tp;
     ui->tp_display->display(tp);
     Rest *command = new Rest();
     command->command = 102;
     QString tp_s = QString::number(tp);
     command->message = tp_s;
     command->success = true;
     WebSocketClient::dataRecvWS->sendTextMessage(command->toJson());
 }

 void MyHome::open_light(){

     ui->pushButton->setStyleSheet("border-image: url(:/image/button _light open.png)");
     ui->label_2->setStyleSheet("border-image: url(:/image/light _on.png)");
     ui->label->setStyleSheet("border-image: url(:/image/home.png)");

     led_on=1;

     Rest *result = new Rest();
     result->command = 501;
     result->message = "开灯完成";
     result->success = true;

     WebSocketClient::dataRecvWS->sendTextMessage(result->toJson());


 }

 void MyHome::close_light(){
     ui->pushButton->setStyleSheet("border-image: url(:/image/butoon _light close.png)");
     ui->label_2->setStyleSheet("border-image: url(:/image/light _off.png)");
     ui->label->setStyleSheet("border-image: url(:/image/home_dark.png)");

     led_on=0;

     Rest *result = new Rest();
     result->command = 502;
     result->message = "关灯完成";
     result->success = true;

     WebSocketClient::dataRecvWS->sendTextMessage(result->toJson());
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

         Rest *result = new Rest();
         result->command = 511;
         result->message = "模式1";
         result->success = true;

         WebSocketClient::dataRecvWS->sendTextMessage(result->toJson());

     }
     if(mod==1)
     {
         ui->label_2->setStyleSheet("border-image: url(:/image/light_yellow.png)");
         ui->label->setStyleSheet("border-image: url(:/image/home_yellow.png)");

         Rest *result = new Rest();
         result->command = 512;
         result->message = "模式2";
         result->success = true;

         WebSocketClient::dataRecvWS->sendTextMessage(result->toJson());

     }
     if(mod==2)
     {
         ui->label_2->setStyleSheet("border-image: url(:/image/light_orange.png)");
         ui->label->setStyleSheet("border-image: url(:/image/home_orange.png)");

         Rest *result = new Rest();
         result->command = 513;
         result->message = "模式3";
         result->success = true;

         WebSocketClient::dataRecvWS->sendTextMessage(result->toJson());

     }


     }
 }

 void MyHome::open_kongtiao(){
     ui->pushButton_3->setStyleSheet("border-image: url(:/image/button_kongtiao_open.png)");
     ui->label_4->setStyleSheet("border-image: url(:/image/kongtiao_open.png)");
     ui->tp_display->display(tp);
     ui->tp_display->show();
     kongtiao_on=1;

     Rest *result = new Rest();
     result->command = 521;
     result->message = "空调开启";
     result->success = true;

     WebSocketClient::dataRecvWS->sendTextMessage(result->toJson());
 }

 void MyHome::close_kongtiao(){
     ui->pushButton_3->setStyleSheet("border-image: url(:/image/button_kongtiao_close.png)");
     ui->label_4->setStyleSheet("border-image: url(:/image/kongtiao_close(1).png)");
     ui->tp_display->close();
     kongtiao_on=0;


     Rest *result = new Rest();
     result->command = 522;
     result->message = "空调关闭";
     result->success = true;

     WebSocketClient::dataRecvWS->sendTextMessage(result->toJson());
 }
 void MyHome::open_fengming(){
     ui->pushButton_5->setStyleSheet("border-image: url(:/image/button_kongtiao_open.png)");
     ui->label_5->setStyleSheet("border-image: url(:/image/fengming_open.png)");

     fengming_on=1;

     Rest *result = new Rest();
     result->command = 666;
     result->message = "蜂鸣开启";
     result->success = true;

     WebSocketClient::dataRecvWS->sendTextMessage(result->toJson());
 }

 void MyHome::close_fengming(){
     ui->pushButton_6->setStyleSheet("border-image: url(:/image/button_kongtiao_close(1).png)");
     ui->label_5->setStyleSheet("border-image: url(:/image/fengming_close.png)");

     fengming_on=0;

     Rest *result = new Rest();
     result->command = 667;
     result->message = "蜂鸣关闭";
     result->success = true;

     WebSocketClient::dataRecvWS->sendTextMessage(result->toJson());
 }
