#include "car_tcp.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"



car_tcp::car_tcp(map_read *Map)
{
    tcpServer = new QTcpServer(this);
    tcp_widget= new QWidget();
    connect(tcpServer,SIGNAL(newConnection()),this,SLOT(do_newConnection()));
    tcp_map = Map;
}


QString car_tcp::getLocalIP()
{
    QString localHostName = QHostInfo::localHostName();
    QHostInfo hostInfo = QHostInfo::fromName(localHostName);
    QString local_ip = " ";
    QList<QHostAddress> addrList = hostInfo.addresses();
    if(addrList.isEmpty())
        return local_ip;
       foreach(QHostAddress aHost, addrList)
       {
           if(aHost.protocol() == QAbstractSocket::IPv4Protocol)
           {
              local_ip = aHost.toString();
              break;
           }
       }
       return local_ip;
}
void car_tcp::send_message(QByteArray str, uint16_t type = 0)
{
    qDebug() << "send_message str"<<str;
    qDebug()<<"send_message线程:"<<QThread::currentThreadId();
    int data_size = str.length() + 16;
    qDebug() << "字符串长度: "<<data_size;
    char* msg = (char*)malloc(data_size);
    if (msg == NULL)
        {
            qDebug() << "数据包内存分配失败!";
            return;
        }
        XHeader *_header = new XHeader;
        _header->_type = type;
        _header->_length = str.length();
        memset(msg, 0, data_size);
        memcpy(msg, _header, 16);
        if (!str.isEmpty())
        {
            memcpy((msg+16), str.data(), _header->_length);
        }
        //QByteArray test = QByteArray(msg);
        int send_size = tcpSocket->write(msg,data_size);
        qDebug()<<"发送的信息长度为："<<send_size;

        qDebug() << "send_message msg"<<msg;
        delete _header;
        free(msg);
}

void car_tcp::start_listen()
{
    /*QString IP = "127.0.0.1";
    QHostAddress address(IP);*/
    int port = 8888;
    tcpServer->listen(QHostAddress::Any,port);
    qDebug()<<"start_listen:"<<QThread::currentThreadId();
}
void car_tcp::stop_listen()
{
    if(tcpServer->isListening())
    {
        if(tcpSocket != nullptr)
            if(tcpSocket->state()==QAbstractSocket::ConnectedState)
                tcpSocket->disconnectFromHost();
        tcpServer->close();
    }
}

void car_tcp::do_newConnection()
{
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(do_socketReadyread()));
    connect(tcpSocket,SIGNAL(connected()),this,SLOT(do_clientConnect()));
    qDebug()<<"有新的客户端连接:"<<QThread::currentThreadId();
    tcp_map->online =true;
}
void car_tcp::do_socketReadyread()
{
    qDebug()<<"do_socketReadyread:"<<QThread::currentThreadId();
    QByteArray message = tcpSocket->readAll();
    //qDebug()<<"tcp test:"<<message<<'\n';
    message = _lastMessage + message;
    int size = message.size();
    if(size > 0){
        if (message.contains('Z')){//检测第一位是否为0x5A.
            message = message.mid(message.indexOf('Z'));
            if (size >= 16) {//返回的数据最小长度为16位,如果大小小于16则数据不完整等待再次读取.
                XHeader* header = new XHeader;
                memcpy(header, message.data(), 16);

                uint64_t data_size = header->_length;//返回数据区总长值.
                //qToBigEndian(header->_length,(uint8_t*)&(data_size));
                delete header;

                uint32_t remaining_size = size - 16;//已读数据总长度 - 头部总长度16 = 现有数据区长度.
                //如果返回数据长度值 大于 已读取数据长度 表示数据还未读取完整，跳出循环等待再次读取..
               if (data_size > remaining_size) {
                    _lastMessage.clear();
                    _lastMessage = message;
                    return;
                }
                    //截取报头16位后面的数据区数据.
                    QByteArray json_data = message.mid(16,data_size);

                    _lastMessage.clear();
                    _lastMessage = message.mid(16+data_size);

                    QString json_string = QString(json_data);
                    tcp_map->tcp_message = json_data;

            } else{
                //qDebug()<<"error!帧头不完整";
            }
        }else{
            //报头数据错误.
            //qDebug()<<"error!帧首不对";
        }
    }
}
void car_tcp::do_clientConnect()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////
//   通信线程相关
/////////////////////////////////////////////////////////////////////////////////////////////


















