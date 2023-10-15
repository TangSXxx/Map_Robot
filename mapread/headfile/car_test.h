#ifndef CAR_TEST_H
#define CAR_TEST_H

#include <QObject>
#include <QString>

class car_test : public QObject
{
    Q_OBJECT
public:
    QString map_str;

signals:
    void ConnectMap(QString ip,int port);   //建立连接

    void DisconnectSend(int num);          //取消连接

};

#endif // CAR_TEST_H
