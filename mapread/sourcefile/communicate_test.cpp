#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "communicate_test.h"
#include "string.h"
#include <QMessageBox>

MapThread::MapThread(car_test* car){
    m_car = car;
}

void MapThread::write_data(QString data){
    map_tcp->write((char*)data.toLatin1().data(), data.size());
}

void MapThread::connectMap(QString ip, int port)
{
    loop_timer = new QTimer();
    map_tcp = new QTcpSocket;
    connect(map_tcp,&QTcpSocket::connected,this,&MapThread::Recv_loop);
    connect(map_tcp,&QTcpSocket::connected,this,&MapThread::connect_OK);
    map_tcp->connectToHost(QHostAddress(ip),port);
}

void MapThread::disconnectMap(int num){
    loop_timer->stop();
    delete loop_timer;
    map_tcp->close();
    map_tcp->deleteLater();
    emit Stop_thread(num);
}


QString MapThread::recv_data()
{
    map_tcp->waitForReadyRead();
    QByteArray message = map_tcp->readAll();
    int size = message.size();

    if(size > 0){
        char a0 = message.at(0);

        if (uint8_t(a0) == '{'){

               while (!message.contains('}')) {
                    _lastMessage = message;
                    message.clear();
                    map_tcp->waitForReadyRead();
                    message = map_tcp->readAll();
                    message = _lastMessage + message;
                }
                    //截取报头16位后面的数据区数据.
                    _lastMessage.clear();

                    QString json_string = QString(message);
                    return json_string;
        }else{
            //报头数据错误.
            qDebug()<<"error!帧首不对";
            return 0;
        }
    }

    return 0;
}

void MapThread::Recv_loop(){
    loop_timer->start(200);
    write_data("{\"type\": \"login\",\"name\": \"0\"}");
    connect(loop_timer,&QTimer::timeout,this,[=](){
        m_car->map_str = recv_data();
        //qDebug()<<m_car->map_str;
    });
}


/////////////////////////////////////////////////////////////////////////////////////////////
//   通信线程相关
/////////////////////////////////////////////////////////////////////////////////////////////
//上线车辆初始化函数
void MainWindow::connect_thread(int num, car_test *car){
    mapthread[num] = new MapThread(car);
    maptask[num] = new QThread;
    mapthread[num]->moveToThread(maptask[num]);

    //连接相关
    connect(amr[num],&car_test::ConnectMap,mapthread[num],&MapThread::connectMap);
    connect(amr[num],&car_test::DisconnectSend,mapthread[num],&MapThread::disconnectMap);
    connect(mapthread[num],&MapThread::Stop_thread,this,&MainWindow::delete_thread);
    connect(mapthread[num],&MapThread::connect_OK,this,&MainWindow::success_connect);

    //开启通信线程
    maptask[num]->start();
}

void MainWindow::success_connect(){
    QMessageBox::information(this,"连接","成功连接小车！");
    map.online = true;
}

void MainWindow::delete_thread(int num){
    maptask[num]->quit();
    maptask[num]->wait();
    delete mapthread[num];
    delete maptask[num];
    delete amr[num];
}

void MainWindow::on_connect_clicked()
{
    if(ui->connect->text() == "连接"){
        amr[0] = new car_test;
        map.get_car(amr[0]);
        connect_thread(0, amr[0]);
        emit amr[0]->ConnectMap(ui->IP->text(),ui->PORT->text().toInt());
        ui->connect->setText("断开");
    }
    else{
        emit amr[0]->DisconnectSend(0);
        ui->connect->setText("连接");
    }
}


