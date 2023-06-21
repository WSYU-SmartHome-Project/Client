#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H
#include <QWidget>
#include "MyHome.h"

#include <QtWebSockets/QWebSocket>
namespace Ui {
class Widget;
}

class WebSocketClient : public QWidget
{
public:
    WebSocketClient();

public slots:
    void createWebsocketClient(QString ip,QString port,QString api);

private slots:
    void onConnected();                 /*-<socket建立成功后，触发该函数 */
    void onTextReceived(QString msg);   /*-<收到Sev端的数据时，触发该函数 */
    void onDisConnected();              /*-<socket连接断开后，触发该函数 */

private:
    static QWebSocket *dataRecvWS;     /*-<websocket类 */
    MyHome *myhomep;
};

#endif // WEBSOCKETCLIENT_H