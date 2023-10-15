#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "map_read.h"
#include "car_test.h"
#include "communicate_test.h"
#include <QLabel>
#include <QTimer>

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

private:
    Ui::MainWindow *ui;
    void timerEvent(QTimerEvent *event);
    MapThread* mapthread[4];
    QThread* maptask[4];
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
};
#endif // MAINWINDOW_H
