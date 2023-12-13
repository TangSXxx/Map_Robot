#ifndef CAR_TCP_H
#define CAR_TCP_H
#include <QJsonValue>
#include <QMetaType>
#include <QObject>
#include <QThread>
#include <stdint.h>
#include <qhostaddress.h>
#include <QtEndian>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include "car_test.h"
#include "map_read.h"
#include <QTimer>
#include <QHostInfo>

class car_tcp : public QObject
{
    Q_OBJECT
public:
    car_tcp(map_read *Map);
    void start_listen();
    void stop_listen();
    void send_message(QByteArray str,uint16_t type);

signals:

private slots:
    void do_newConnection();
    void do_socketReadyread();
    void do_clientConnect();

private:
    QTcpSocket *tcpSocket = nullptr;
    QTcpServer *tcpServer;
    QString getLocalIP();
    QWidget *tcp_widget;
    map_read *tcp_map;
    //保存上一次读取的tcp信息
    QByteArray _lastMessage;
};

class XHeader
{
private:
    /* data */
public:
    uint8_t _sync = 0x5a;                      // 同步头
    uint8_t _fromID;                   // 版本号
    uint16_t _type = 0;                      // 序号
    uint64_t _length = 0;                      // 数据区长度

    XHeader(){};
    ~XHeader(){};
};
#endif // CAR_TCP_H
