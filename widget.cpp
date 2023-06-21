#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "websocketclient.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //给指针分配空间
    myhomep =new MyHome;


    connect(this,&Widget::signal_mysignall,myhomep,&MyHome::slot_myfun1);

    connect(myhomep,&MyHome::signal_swap,this,&Widget::slot_swap);
}

Widget::~Widget()
{
    delete ui;
}

//界面切换
void Widget::slot_swap()
{
    myhomep->close();
    this->show();
}


QString ip;
QString port;
//链接按钮
void Widget::on_pushButton_clicked()
{



    if(nullptr == ui->lineEdit->text()||nullptr == ui->lineEdit_2->text())//判断是否输入ip 和port
        {
        qDebug()<<"错误：端口或ip地址为空";
        return;
    }
    else
    {
        //text获取控件上的文本信息
        ip = ui->lineEdit->text();
        port = ui->lineEdit_2->text();
        WebSocketClient* socket = new WebSocketClient();
        QString api = "/control";
        socket->setWidget(this);
        socket->setMyHome(myhomep);
        socket->createWebsocketClient(ip,port,api);

    }
}
void Widget::on_connected(){

    //        调用该对象show方法show出界面
            myhomep->show();
    //        发送信号
            emit signal_mysignall(ip,port);
    //        调用当前对象中的close方法，关闭当前界面
            this->close();
}


