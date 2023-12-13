#include "mythread.h"
#include <QDebug>
#include <QTime>
#include <sys/time.h>
#include <qelapsedtimer.h>
#include <QMetaType>
#include <cmath>


MyThread::MyThread(QObject *parent ):
    QThread(parent)
{
     stopped = false;
     fAMR = new AMR();
     deltaX = 1;
     deltaY = 1;
     deltagl = 1;
}

void MyThread::run()
{

    while(!stopped)
    {
        QElapsedTimer mstimer;
        mstimer.start();



    }



}


void MyThread::stop()
{
    stopped = true;
}

