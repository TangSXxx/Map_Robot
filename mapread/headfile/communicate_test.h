#ifndef COMMUNICATE_TEST_H
#define COMMUNICATE_TEST_H

#include <QJsonValue>
#include <QMetaType>
#include <QObject>
#include <QThread>
#include <stdint.h>
#include <qhostaddress.h>
#include <QtEndian>
#include <QTcpSocket>
#include "XStateClient.h"
#include "car_test.h"
#include <QTimer>

class MapThread : public QObject
{
    Q_OBJECT
public:
    MapThread(car_test* car);
    void connectMap(QString ip, int port);
    void disconnectMap(int num);
    void Recv_loop();
    QString recv_data();
    void write_data(QString data);


    QTcpSocket* map_tcp;
    QTimer * loop_timer;//代码定时器
    bool loop_tricker = 0;
    bool read_ok = 0;

    void get_currentmap();          //获取当前地图名称

signals:
    void recv_value(double x,double y,double angle);
    void got_currentmap();
    void connect_OK();
    void Stop_thread(int num);

private:
    car_test* m_car;     //维护仙工车对象
    QByteArray _lastMessage;

};

#endif // COMMUNICATE_TEST_H
