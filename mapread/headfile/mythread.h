#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <QMainWindow>

#pragma once
struct AMR{
    QPointF startPos;
    QPointF endPos;
    int stangle;
    int endangle;
    int mode;
    int speed;
    int agspeed;
};

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    void stop();
    AMR* fAMR;
    double XForword(double x,int AMRNum);
    double YForword(double y,int AMRNum);
    double XYForword(int *x,int *y,int dx,int dy,int angle,int AMRNum);
    double Turn(double angle,double endangle,int AMRNum);
    int xi,yi,ai;

    double deltaX;
    double deltaY;
    double deltagl;

public slots:
    void Accept(QPointF startPos,QPointF endPos,double stangle,double endangle,int mode,int speed,int agspeed);
    void DeltaChange(int x,int y,int angle);
protected:
    void run();
private:
    volatile bool stopped;
    int xsend = 0;
signals:
    void updatex(double x);
    void updatey(double y);
    void updatea(double angle);
    void TaskFh(int AMRNum,QPointF TaskPoint,double TaskAngle);

};

#endif // MYTHREAD_H
