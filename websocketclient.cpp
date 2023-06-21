#include "websocketclient.h"
#include "rest.h"
#include <QtWebSockets/QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include "device.h"
#include <QMessageBox>

QWebSocket *WebSocketClient::dataRecvWS = nullptr;

WebSocketClient::WebSocketClient()
{
}
int connecting = 0;

void WebSocketClient::createWebsocketClient(QString ip,QString port,QString api){

    dataRecvWS = new QWebSocket();
    qDebug()<<"create websocket!";
    connecting = 1;
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
    connecting = 0;
    Rest* rest = new Rest();
    rest->message = "connected";
    rest->status = 200;
    rest->success = true;

    QJsonDocument doc(rest->toJsonObject());
    QString jsonStr(doc.toJson(QJsonDocument::Compact));

    qDebug() << "服务器已连接!";
    qDebug() << "地址:" << dataRecvWS->peerAddress();
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

    myhomep->setText(rest->toJson()+"\n");

    if(rest->status == 200){//入池完成
        qDebug() << "连接完成";
        widget->on_connected();//连接结束，跳转页面
    }

    if(rest->status == 600){
        //开灯命令；
        myhomep->open_light();

    }

    if(rest->status == 601){
        //关灯命令；
        myhomep->close_light();

    }

    //切换灯模式
    if(rest->status == 610){
        myhomep->switch_mod(0);
    }

    if(rest->status == 620){
        myhomep->switch_mod(1);
    }

    if(rest->status == 630){
        myhomep->switch_mod(2);
    }

    if(rest->status == 700){
        myhomep->open_kongtiao();

    }

    if(rest->status == 701){
        myhomep->close_kongtiao();
    }



}

/**
 * @breaf 连接断开
 * @note  当连接断开时，触发该函数
 */
void WebSocketClient::onDisConnected(){
    qDebug()<<"连接断开";
    if(connecting!=0){
        QMessageBox::warning(myhomep, "网络错误", "服务器连接失败");
    }
    myhomep->on_pushButton_2_clicked();
}
