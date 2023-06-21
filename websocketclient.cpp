#include "websocketclient.h"
#include "rest.h"
#include <QtWebSockets/QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include "device.h"

QWebSocket *WebSocketClient::dataRecvWS = nullptr;

WebSocketClient::WebSocketClient()
{
}

void WebSocketClient::createWebsocketClient(QString ip,QString port,QString api){

    dataRecvWS = new QWebSocket();
    qDebug()<<"create websocket!";
    connect(dataRecvWS,&QWebSocket::disconnected,this,&WebSocketClient::onDisConnected);
    connect(dataRecvWS,&QWebSocket::textMessageReceived,this,&WebSocketClient::onTextReceived);
    connect(dataRecvWS,&QWebSocket::connected,this,&WebSocketClient::onConnected);
    dataRecvWS->open(QUrl("ws://"+ip+":"+port+api));
}

/**
 * @breaf 判断连接状态
 * @note  当连接成功后，触发该函数
 */
void WebSocketClient::onConnected(){
    Rest* rest = new Rest();
    rest->message = "connected";
    rest->status = 200;
    rest->success = true;

    QJsonDocument doc(rest->toJsonObject());
    QString jsonStr(doc.toJson(QJsonDocument::Compact));

    qDebug() << "DataReveive websocket is already connect!";
    qDebug() << "Address:" << dataRecvWS->peerAddress();
    dataRecvWS->sendTextMessage(jsonStr);
}

/**
 * @breaf 数据处理函数
 * @param msg, 数据信息
 * @note  当收到服务端发送的数据时，触发该函数
 */
void WebSocketClient::onTextReceived(QString msg){
    qDebug()<<"----------------data-----------------";
    qDebug()<<msg;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject jsonObject = jsonDoc.object();
    Rest * rest = new Rest();
    rest->message = jsonObject["message"].toString();
    rest->status = jsonObject["status"].toInt();
    rest->success = jsonObject["success"].toBool();

    if(rest->status == 200){
        //返回设备信息；
        Device *device = new Device();
        device->status = 0;//状态码0代表已经连接
        device->type = "client";//设备属性

        QJsonDocument doc(device->toJsonObject());
        QString deviceJson(doc.toJson(QJsonDocument::Compact));

        Rest* restDevice = new Rest();
        restDevice->message = deviceJson;
        restDevice->status = 300;//状态码300 代表返回设备信息
        restDevice->success = true;

        QJsonDocument docNew(restDevice->toJsonObject());
        QString jsonStr(docNew.toJson(QJsonDocument::Compact));

        dataRecvWS->sendTextMessage(jsonStr);
    }

    if(rest->status == 301){//入池完成
        qDebug() << "连接完成";
        widget->on_connected();//连接结束，跳转页面
    }

    if(rest->status == 600){
        //开灯命令；
        myhomep->open_light();
        myhomep->setText(rest->toJson()+"\n");

    }

    if(rest->status == 601){
        //关灯命令；
        myhomep->close_light();
        myhomep->setText(rest->toJson()+"\n");

    }

    //切换灯模式
    if(rest->status == 610){
        myhomep->switch_mod(0);
        myhomep->setText(rest->toJson()+"\n");
    }

    if(rest->status == 620){
        myhomep->switch_mod(1);
        myhomep->setText(rest->toJson()+"\n");
    }

    if(rest->status == 630){
        myhomep->switch_mod(2);
        myhomep->setText(rest->toJson()+"\n");
    }

    if(rest->status == 700){
        myhomep->open_kongtiao();
        myhomep->setText(rest->toJson()+"\n");

    }

    if(rest->status == 701){
        myhomep->close_kongtiao();
        myhomep->setText(rest->toJson()+"\n");

    }



}

/**
 * @breaf 连接断开
 * @note  当连接断开时，触发该函数
 */
void WebSocketClient::onDisConnected(){
    qDebug()<<"Dialog websocket is disconnected!!!";
}
