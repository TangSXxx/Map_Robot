#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "map_read.h"
#include "car_test.h"
#include "communicate_test.h"
#include "car_tcp.h"
#include <QLabel>
#include <QMetaType>
#include <QTimer>
#include <QThread>
#include "ui_mainwindow.h"
#include "map_read.h"
#include "qcustomplot.h"
#include <iostream>
#include <stdint.h>
#include <sstream>
#include <QDebug>
#include <mutex>
#include <windows.h>
#include <thread>
#include <chrono>
#include <map>
struct Site {
    QString name;
    double x;
    double y;
    int yaw;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintmap();
    void connect_thread(int num, car_test *car);
    void delete_thread(int num);
    void success_connect();
    car_test* amr[4];
    map_read map;

public slots:
    void on_mousePressEvent(QMouseEvent *event);
    void on_mouseMoveEvent(QMouseEvent *event);
    void on_mouseRealseEvent(QMouseEvent *event);


signals:
    void send_tcp(QByteArray str,uint16_t type);

private:
    Ui::MainWindow *ui;
    void timerEvent(QTimerEvent *event);
    MapThread* mapthread[4];
    QThread* maptask[4];

    int seqNum=0;//站点数量
    int potnum = 0;
    QString cpot = NULL;

    QList<QPoint> selectedPoints; // 声明选中站点的列表
    std::map<QString, Site> siteMap;



    car_tcp* cartomap;
    QThread* tcp_thread;
//protected:
//    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_connect_clicked();
    void on_testplus_clicked();
    void on_move_map_clicked();
    void on_add_clicked();
    void on_del_clicked();
    void on_clamp_control_clicked();
    void on_clamp_clicked();
    void on_nav_clicked();
    void on_ip_button_clicked();
    void on_NewIPButton_clicked();
    void on_map_clicked();
    void on_nav_stop_clicked();
    void on_nav_start_clicked();
    void on_qr_code_clicked();
    void on_setNewItem_clicked();
    void on_NavcontinueButton_clicked();
    void on_NavstopButton_clicked();
    void on_XposEdit_textChanged(const QString &arg1);
    void on_PositionButton_clicked();
    void on_LineButton_clicked();
    void on_SDeIeteButton_clicked();
    void on_listWidget_itemPressed(QListWidgetItem *item);
};
#endif // MAINWINDOW_H
