#ifndef MAP_READ_H
#define MAP_READ_H
#include<iostream>
#include<string>
#include <QPainter>
#include <QFile>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include "cJSON.h"
#include "car_test.h"

using namespace std;
struct MyPoint //创建点的数据
{
    double x;
    double y;
};

struct MyMark //创建点的数据
{
    double x;
    double y;
    QString instanceName;
};
struct MyPath
{
    QString startPos;
    QString endPos;
    MyPoint start;
    MyPoint end;
};

class map_read
{
public:
    car_test* m_car;
    void get_car(car_test* car);
    bool online = false;
    map_read();
    ~map_read();
    double size_x;
    double size_y;
    MyPoint cur_pose;
    MyPoint nav_endpose;
    int sum_plot;
    double origin_x;
    double origin_y;
    double x_left,x_right,y_left,y_right;
    bool map_move;
    double car_yaw;
    QPixmap carimage;
    QMatrix car_matrix;
    //cJSON* m_cjsonStr;
    QJsonDocument m_doc;
    QVector <MyPoint> Mypoints;
    QVector <MyPoint> path_point;   
    QVector <MyMark> Mymarks;
    QVector <MyPath> Mypaths;
    QVector <MyPoint> v_point;
    bool find_path(QString start_mark,QString end_mark);
    MyPath mark_path(QString start_mark,QString end_mark);
    void get_size();
    void get_json();
    void get_map();
    void get_mark();
    void get_path();
    void add_mark(QString Mark,float x,float y);
    void add_path(QString start_mark,QString end_mark);
    void Remove_path(QString start_mark,QString end_mark);
    void Remove_mark(QString Mark);
    void Remove_obstacles(double x1,double y1,double x2,double y2);
    void txt_to_vectordouble1(QString pathname);
    void car_pose();
    bool pose_nav(double x,double y,double yaw);
    bool pose_nav(double x1,double y1,double yaw1,double x2,double y2,double yaw2);
    bool mark_nav(QString mark1,QString mark2,double yaw1,double yaw2);
};

#endif // MAP_READ_H
