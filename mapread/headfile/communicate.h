#ifndef COMMUNICATE_H
#define COMMUNICATE_H

#include <QJsonValue>
#include <QMetaType>
#include <QObject>
#include <QThread>
#include <stdint.h>
#include <qhostaddress.h>
#include <QtEndian>
#include <QTcpSocket>
#include "XStateClient.h"
#include "car.h"
#include <QTimer>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtWidgets/QWidget>
#include <QTextCodec>
#include <QString>
#include <QUrl>
#include <QDialog>

enum{Ctrl = 0, Navi, Config, Other};
enum{I_AMR_B1 = 0, I_AMR_B2, I_AMR_D1, I_AMR_D2};
enum{Out = 0, In};

//小车状态接收线程
class RecvThread : public QObject
{
    Q_OBJECT
public:
    RecvThread(car* car);
    void connectRecv(QString ip);
    void disconnectRecv(int num);
    void Recv_loop();
    void write_data(quint16 sendCommand, const QByteArray &sendData, quint16 number);
    QString recv_data();
    void stopThread();

    XStateClient* xt;       //接收小车位置信息
    QTcpSocket* recv_tcp;
    QTimer * loop_timer;//代码定时器
    bool loop_tricker = 0;
    bool read_ok = 0;

    QString get_location();
    QString get_task_status();
    QString get_battery();

    QString get_map();//小车中存储的地图的名称
    QString map_load_state();//地图加载状态
signals:
    void recv_value(double x,double y,double angle);
    void send_json(QByteArray json);

public slots:
    void thread_error(QAbstractSocket::SocketState);

private:

    QString m_ip;
    car* m_car;     //维护仙工车对象
    QByteArray _lastMessage;
    bool  m_Paused=true;
    bool  m_stop=true;
    bool  thread_start = false;
};

//小车指令发送线程
class SendThread : public QObject
{
    Q_OBJECT

public:
    explicit SendThread(car *amr, QObject *parent = nullptr);
    ~SendThread();
    void disconnectSend(int num);
    void write_data(quint16 sendCommand, int mode, const QByteArray &sendData, quint16 number);
    void send_move_task(QStringList movelist);
    void get_send_tasklist(QStringList tasklist);
    void connectSend(QString ip);

    void send_ctrl_motion(double vx, double w, double time = 0);
    void config_motion_par(double maxspeed, double maxwspeed, double maxacc, double maxwacc);
    void stop_ctrl_motion();
    void send_car_pause();
    void send_car_resume();
    void send_car_cancel();

    void send_car_terminal(int pot,int mode, int frame_floor, int car_floor);
    void send_car_terminal_roll(int pot,int mode);
    void send_car_point(QString point);
    void send_car_reset();
    void get_control();
    void release_control();

    void http_slam();//监听建图实时画面
    void start_slam();//开启建图
    void stop_slam();//停止建图
    void load_map(QString map);//加载指定的地图
    void download_map(QString map);//下载指定的地图
    void upload_map();
    QString recv_data();

private:
    car* send_car;      //维护仙工车对象
    QTcpSocket* navi_tcp;
    QTcpSocket* ctrl_tcp;
    QTcpSocket* config_tcp;
    QTcpSocket* other_tcp;
    int send_id;

    QNetworkAccessManager *m_manager;
    QNetworkReply *m_Reply;
    QByteArray _lastMessage;
    int slam_flag=0;
private slots:

    void requestFinished(QNetworkReply* reply);


signals:
    void stop_thread(int num);

};

#endif // COMMUNICATE_H

