/*********************************************
 * 此文件为网络管理部分
 * 包含新车相关通信功能，上线按钮创建通信线程
 * v1.0 添加指令下发和状态接收双线程功能
 * 2022.12.20 添加unity3d程序位置更新
 * 2022.12.21 添加指示灯与连接提醒
*********************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "communicate.h"
#include "string.h"
RecvThread::RecvThread(car* car){
    m_car = car;
}

void RecvThread::write_data(quint16 sendCommand, const QByteArray &sendData = Q_NULLPTR, quint16 number = 0){
    int size = 0;
    uint8_t* headBuf = Q_NULLPTR;
    int headSize = 0;
    XData* data = Q_NULLPTR;
    if(sendData.isEmpty()){
        headSize = sizeof(XHeader);
        headBuf = new uint8_t[headSize];
        data = (XData*)headBuf;
        size = data->set_data(sendCommand,Q_NULLPTR,0,number);
    }
    else{
    std::string json_str = sendData.toStdString();
    headSize = sizeof(XHeader) + json_str.length();
    headBuf = new uint8_t[headSize];
    data = (XData*)headBuf;
    size = data->set_data(sendCommand,(uint8_t*)json_str.data(),json_str.length(),number);
    }
    recv_tcp->write((char*)data, size);
    delete[] headBuf;
}


void RecvThread::thread_error(QAbstractSocket::SocketState){
    int error = recv_tcp->state();
    qDebug()<<"error: "<< error;
}

void RecvThread::connectRecv(QString ip){
    loop_timer = new QTimer();
    recv_tcp = new QTcpSocket;
    //connect(recv_tcp,&QTcpSocket::readyRead,this,&RecvThread::recv_data);
    connect(recv_tcp,&QTcpSocket::connected,this,&RecvThread::Recv_loop);
    recv_tcp->connectToHost(QHostAddress(ip),19204);

}

void RecvThread::disconnectRecv(int num){
    loop_timer->stop();
    delete loop_timer;
    recv_tcp->close();
    recv_tcp->deleteLater();
}






/*循环执行*/




void RecvThread::Recv_loop(){
    loop_timer->start(500);
    connect(loop_timer,&QTimer::timeout,this,[=](){

    QString loc_info_s = get_location();
    QString task_info_s = get_task_status();
    QString battery_info_s = get_battery();
    QString map_name=get_map();
    QString map_state=map_load_state();

    QJsonDocument doc;
    doc = doc.fromJson(loc_info_s.toUtf8());      //生成jsondocument对象,进行类型转换string->qstring->bytearrary
    m_car->pos[x] = doc.object().take("x").toDouble()*80;
    m_car->pos[y] = 800 - (doc.object().take("y").toDouble()*80);
    m_car->pos[angle] = - doc.object().take("angle").toDouble();
    doc = doc.fromJson(task_info_s.toUtf8());
    m_car->task_status = doc.object().take("task_status").toInt();
    doc = doc.fromJson(battery_info_s.toUtf8());
    m_car->battery_level = doc.object().take("battery_level").toDouble()*100;   //获取为小数需转换为百分比


    QJsonDocument doc_name;
    doc_name=doc_name.fromJson(map_name.toUtf8());
    QJsonObject rootObj_name = doc_name.object();
    QJsonValue cur_name = rootObj_name.value("current_map");
    if(m_car->map_name.empty()!=true)
    {
        m_car->map_name.clear();
    }
    m_car->map_name.push_back(cur_name.toString());
    QJsonValue name_value = rootObj_name.value("maps");
    if (name_value.type() == QJsonValue::Array) {
        QJsonArray nameArray =name_value.toArray();
        for (int i = 0; i < nameArray.size(); i++) {
            QJsonValue name = nameArray.at(i);
            m_car->map_name.push_back(name.toString());
        }
    }


    //qDebug()<<"x = "<<m_car->pos[x]<<"y = "<<m_car->pos[y]<<"battery = "<<m_car->battery_level;
    //qDebug()<<map_name;
    //qDebug()<<map_state;

    emit recv_value(m_car->pos[x],m_car->pos[y],m_car->pos[angle]);



    });

}






void RecvThread::stopThread()
{
    m_stop=true;
    thread_start=false;
}

QString RecvThread::recv_data()
{
    recv_tcp->waitForReadyRead();
    QByteArray message = recv_tcp->readAll();
    int size = message.size();


    if(size > 0){
        char a0 = message.at(0);

        if (uint8_t(a0) == 0x5A){//检测第一位是否为0x5A.
            if (size >= 16) {//返回的数据最小长度为16位,如果大小小于16则数据不完整等待再次读取.
                XHeader* header = new XHeader;
                memcpy(header, message.data(), 16);

                uint32_t data_size;//返回数据区总长值.
                qToBigEndian(header->_length,(uint8_t*)&(data_size));
                delete header;

                uint32_t remaining_size = size - 16;//已读数据总长度 - 头部总长度16 = 现有数据区长度.
                //如果返回数据长度值 大于 已读取数据长度 表示数据还未读取完整，跳出循环等待再次读取..
               while (data_size > remaining_size) {
                    _lastMessage = message;
                    message.clear();
                    recv_tcp->waitForReadyRead();
                    message = recv_tcp->readAll();
                    remaining_size += message.size();
                    message = _lastMessage + message;

                }
                    //截取报头16位后面的数据区数据.
                    QByteArray json_data = message.mid(16,data_size);
                    //qDebug()<<"recv:"<<json_data;
                    _lastMessage.clear();

                    QString json_string = QString(json_data);
                    return json_string;

            } else{
                qDebug()<<"error!帧头不完整";
                return 0;
            }
        }else{
            //报头数据错误.
            qDebug()<<"error!帧首不对";
            return 0;
        }
    }
    qDebug()<<"error!没收到数据";
    return 0;
}


/*
编号: 1004 (0x03EC)
名称: robot_status_loc_req
描述: 查询机器人位置
JSON 数据区: 无
*/
QString RecvThread::get_location()
{
    write_data(1004);
    QString get_local = recv_data();
    return get_local;
}

/*
编号: 1020 (0x03FC)
名称: robot_status_task_req
描述: 查询机器人当前的导航状态, 导航站点, 导航相关路径(已经经过的站点, 尚未经过的站点)等
JSON 数据区: simple字段
*/
QString RecvThread::get_task_status()
{
    write_data(1020);
    QString get_task_sta = recv_data();
    return get_task_sta;
}

/*
编号: 1007 (0x03EF)
名称: robot_status_battery_req
描述: 查询机器人电池状态
JSON 数据区: 见下表
字段名	类型	描述	可缺省
simple	boolean	是否只返回简单数据, true = 是，false = 否，缺省则为否	是
*/
QString RecvThread::get_battery()
{
    write_data(1007);
    QString get_battery = recv_data();
    return get_battery;
}




SendThread::SendThread(car *amr, QObject *parent) : QObject(parent)
{
    send_car = amr;
}

SendThread::~SendThread()
{}

void SendThread::connectSend(QString ip)
{
    navi_tcp = new QTcpSocket;
    ctrl_tcp = new QTcpSocket;
    config_tcp = new QTcpSocket;
    other_tcp=new QTcpSocket;
    navi_tcp->connectToHost(QHostAddress(ip),19206);    //导航API
    ctrl_tcp->connectToHost(QHostAddress(ip),19205);    //控制API
    config_tcp->connectToHost(QHostAddress(ip),19207);    //配置API
    other_tcp->connectToHost(QHostAddress(ip),19210);
}

void SendThread::disconnectSend(int num)
{
    navi_tcp->close();
    navi_tcp->deleteLater();
    ctrl_tcp->close();
    ctrl_tcp->deleteLater();
    other_tcp->close();
    other_tcp->deleteLater();
    config_tcp->close();
    config_tcp->deleteLater();
    emit stop_thread(num);
}

void SendThread::get_send_tasklist(QStringList tasklist)
{
    send_move_task(tasklist);
}

//构造命令发送的数据
void SendThread::write_data(quint16 sendCommand, int mode, const QByteArray &sendData = Q_NULLPTR, quint16 number = 0)
{
    int size = 0;
    uint8_t* headBuf = Q_NULLPTR;
    int headSize = 0;
    XData* data = Q_NULLPTR;
    if(sendData.isEmpty()){
        headSize = sizeof(XHeader);
        headBuf = new uint8_t[headSize];
        data = (XData*)headBuf;
        size = data->set_data(sendCommand,Q_NULLPTR,0,number);
    }
    else{
    std::string json_str = sendData.toStdString();
    headSize = sizeof(XHeader) + json_str.length();
    headBuf = new uint8_t[headSize];
    data = (XData*)headBuf;
    size = data->set_data(sendCommand,(uint8_t*)json_str.data(),json_str.length(),number);
    }
    switch(mode)
    {
    case Ctrl:
        ctrl_tcp->write((char*)data, size);         //发送控制api
        break;
    case Navi:
        navi_tcp->write((char*)data, size);         //发送导航api
        break;
    case Config:
        config_tcp->write((char*)data, size);
        break;
    case Other:
        other_tcp->write((char*)data, size);
        break;
    }
    delete[] headBuf;
}


/////////////////////////////////////////////////////////////////////////////////////////////
//   机器人导航API
/////////////////////////////////////////////////////////////////////////////////////////////
/*
编号: 3051 (0x0BFA)
名称: robot_task_gotargetlist_req
描述: 取货区目标
JSON 数据区: point:货架名称前缀(Loc-0x) mode:取货还是放货 frame_floor：货架层数 car_floor:背篓层数
*/
void SendThread::send_car_terminal(int pot,int mode, int frame_floor = 100, int car_floor = 100){
    QJsonObject list;
    QJsonObject args;
    QString localtion;
    QString head;
    if(pot<10)
    {
        head = "Loc-0";
    }
    else if(pot>=10)
    {
        head = "Loc-";
        frame_floor = 1;
    }

    QString point = head + QString::number(pot);
    qDebug()<<"frame："<<frame_floor;

    if(frame_floor<100&&car_floor<100){
        localtion = point + "-" + QString::number(frame_floor,10);
        args.insert("selfPosition",car_floor);
        list.insert("script_args",QJsonValue(args));
        list.insert("operation","script");
        list.insert("script_name","ctuNoBlock.py");
    }
    else if(frame_floor<100){
         qDebug()<<"kcnkjds";
         localtion = point + "-" + QString::number(frame_floor,10);
    }
    else{
        localtion = point;
    }
    list.insert("id",localtion);
    if(mode == 1){
        list.insert("binTask","unload");
    }
    else{
        list.insert("binTask","load");
    }

    QJsonDocument doc;
    doc.setObject(list);
    qDebug()<<"kdaj"<<list;

    QByteArray sendData = doc.toJson(QJsonDocument::Indented);
    qDebug()<<"jjjj"<<localtion<<"IN"<<In;

     write_data(3051, Navi, sendData ,0);

}

void SendThread::send_car_terminal_roll(int pot, int mode){
    QString head;
    head = "Loc-";
    QString point = head + QString::number(pot) + "-1";
    QJsonObject list;
    list.insert("id",point);
    if(mode == 1){
        list.insert("binTask","unload");
    }
    else{
        list.insert("binTask","load");
    }
    QJsonDocument doc;
    doc.setObject(list);
    QByteArray sendData = doc.toJson(QJsonDocument::Indented);
    write_data(3051, Navi, sendData ,0);

}

void SendThread::send_car_point(QString point){
    QJsonObject sendpoint;
    sendpoint.insert("id",point);
    sendpoint.insert("source_id","SELF_POSITION");
    sendpoint.insert("task_id",QString("%1").arg(send_id));
    send_id++;
    QJsonDocument doc;
    doc.setObject(sendpoint);

    QByteArray sendData = doc.toJson(QJsonDocument::Indented);
    write_data(3051, Navi, sendData ,0);
}

//料箱车标零操作
void SendThread::send_car_reset(){
    QJsonObject reset;
    reset.insert("operation","script");
    reset.insert("id","SELF_POSITION");
    reset.insert("script_name","ctuNoBlock.py");
    QJsonObject zero;
    zero.insert("operation","zero");
    reset.insert("script_args",QJsonValue(zero));
    QJsonDocument doc;
    doc.setObject(reset);

    QByteArray sendData = doc.toJson(QJsonDocument::Indented);
    write_data(3051, Navi, sendData ,0);
}



/*
编号: 3066 (0x0BFA)
名称: robot_task_gotargetlist_req
描述: 发送一组站点给小车导航
JSON 数据区: 分析站点进行构造
*/
void SendThread::send_move_task(QStringList movelist){
    int task_size = movelist.size();
    //构造Json格式字符串
    QJsonObject task_list[task_size];
    QJsonArray task_array;
    for(int i=0; i<task_size-1; i++){
    task_list[i].insert("id",movelist[i+1]);
    task_list[i].insert("source_id",movelist[i]);
    task_list[i].insert("task_id",QString("%1").arg(send_id));
    task_array.append(QJsonValue(task_list[i]));
    send_id++;
    }
    QJsonObject whole_list;
    whole_list.insert("move_task_list",QJsonValue(task_array));

    QJsonDocument doc;
    doc.setObject(whole_list);

    QByteArray sendData = doc.toJson(QJsonDocument::Indented);
    write_data(3066, Navi, sendData,0);
}

/*
编号: 3001 (0x0BB9)
名称: robot_task_pause_req
描述: 暂停当前导航
JSON 数据区: 无
*/
void SendThread::send_car_pause(){
    write_data(3001, Navi);
}

/*
编号: 3002 (0x0BBA)
名称: robot_task_resume_req
描述: 继续当前导航
JSON 数据区: 无
*/
void SendThread::send_car_resume(){
    write_data(3002, Navi);
}

/*
编号: 3003 (0x0BBB)
名称: robot_task_cancel_req
描述: 取消当前导航
JSON 数据区: 无
*/
void SendThread::send_car_cancel(){
   write_data(3003, Navi);
}


/////////////////////////////////////////////////////////////////////////////////////////////
//   机器人控制API
/////////////////////////////////////////////////////////////////////////////////////////////
/*
编号: 2010 (0x07DA)
名称: robot_control_motion_req
描述: 发送指令让小车进行开环运动
JSON 数据区: vx前后移动速度 w旋转速度 time持续时间（默认为0，一直保持运动）
*/
void SendThread::send_ctrl_motion(double vx, double w, double time){
    //构造Json格式字符串
    QJsonObject motion;
    motion.insert("vx", vx);
    motion.insert("w", w);
    motion.insert("duration",time);

    QJsonDocument doc;
    doc.setObject(motion);

    QByteArray sendData = doc.toJson(QJsonDocument::Indented);
    write_data(2010, Ctrl, sendData, 0);
}

/*
编号: 2000 (0x07D0)
名称: robot_control_stop_req
描述: 发送指令让小车停止开环运动
JSON 数据区:无
*/
void SendThread::stop_ctrl_motion(){
    write_data(2000, Ctrl);
}

/////////////////////////////////////////////////////////////////////////////////////////////
//   机器人配置API
/////////////////////////////////////////////////////////////////////////////////////////////
/*
编号: 4101 (0x1005)
名称: robot_config_saveparams_req
描述: 永久修改机器人参数（修改运动参数)
JSON 数据区:
*/
void SendThread::config_motion_par(double maxspeed, double maxwspeed, double maxacc, double maxwacc){
    QJsonObject speed;
    speed.insert("value",maxspeed);
    QJsonObject wspeed;
    wspeed.insert("value",maxwspeed);
    QJsonObject acc;
    acc.insert("value",maxacc);
    QJsonObject wacc;
    wacc.insert("value",maxwacc);
    //构造Json格式字符串
    QJsonObject movefactory;
    movefactory.insert("MaxAcc", QJsonValue(acc));
    movefactory.insert("MaxSpeed", QJsonValue(speed));
    movefactory.insert("MaxRotAcc", QJsonValue(wacc));
    movefactory.insert("MaxRotSpeed", QJsonValue(wspeed));

    QJsonObject plugin;
    plugin.insert("MoveFactory", QJsonValue(movefactory));

    QJsonDocument doc;
    doc.setObject(plugin);

    QByteArray sendData = doc.toJson(QJsonDocument::Indented);
    write_data(4101, Config, sendData, 0);
}

/*
编号: 4005 (0x0FA5)
名称: robot_config_lock_req
描述: 抢占机器人控制权
JSON 数据区: nick_name 抢占者名称
*/
void SendThread::get_control(){
    QJsonObject name;
    name.insert("nick_name","jason");
    QJsonDocument doc;
    doc.setObject(name);

    QByteArray sendData = doc.toJson(QJsonDocument::Indented);
    write_data(4005, Config, sendData, 0);

}

/*
编号: 4006 (0x0FA6)
名称: robot_config_unlock_req
描述: 释放机器人控制权
JSON 数据区: 无
*/
void SendThread::release_control(){
    write_data(4006, Config);
}

//上线车辆初始化函数
void MainWindow::connect_thread(int num, car *car){
    sendthread[num] = new SendThread(car);
    sendtask[num] = new QThread;
    sendthread[num]->moveToThread(sendtask[num]);
    recvthread[num] = new RecvThread(car);
    recvtask[num] = new QThread;
    recvthread[num]->moveToThread(recvtask[num]);

    //连接相关
    connect(amr[num],&car::ConnectSend,sendthread[num],&SendThread::connectSend);
    connect(amr[num],&car::DisconnectSend,sendthread[num],&SendThread::disconnectSend);
    connect(amr[num],&car::ConnectSend,recvthread[num],&RecvThread::connectRecv);
    connect(amr[num],&car::DisconnectSend,recvthread[num],&RecvThread::disconnectRecv);
    connect(sendthread[num],&SendThread::stop_thread,this,&MainWindow::delete_thread);
    //导航运动相关
    connect(amr[num],&car::send_task_list_sig,sendthread[num],&SendThread::get_send_tasklist);
    connect(amr[num],&car::car_pausedown,sendthread[num],&SendThread::send_car_pause);
    connect(amr[num],&car::car_resume,sendthread[num],&SendThread::send_car_resume);
    connect(amr[num],&car::car_cancel,sendthread[num],&SendThread::send_car_cancel);
    connect(amr[num],&car::send_car_task,sendthread[num],&SendThread::send_car_terminal);
    connect(amr[num],&car::send_car_pot,sendthread[num],&SendThread::send_car_point);
    connect(amr[num],&car::send_car_roll,sendthread[num],&SendThread::send_car_terminal_roll);
    //遥控相关
    connect(amr[num],&car::send_ctrl_motion,sendthread[num],&SendThread::send_ctrl_motion);
    connect(amr[num],&car::send_ctrl_stop,sendthread[num],&SendThread::stop_ctrl_motion);
    //配置相关
    connect(amr[num],&car::send_config_par,sendthread[num],&SendThread::config_motion_par);
    connect(amr[num],&car::send_car_reset,sendthread[num],&SendThread::send_car_reset);
    connect(amr[num],&car::send_car_control_get,sendthread[num],&SendThread::get_control);
    connect(amr[num],&car::send_car_control_release,sendthread[num],&SendThread::release_control);
    //其它相关
    connect(amr[num],&car::car_http_slam,sendthread[num],&SendThread::http_slam);
    connect(amr[num],&car::car_start_slam,sendthread[num],&SendThread::start_slam);
    connect(amr[num],&car::car_stop_slam,sendthread[num],&SendThread::stop_slam);
    connect(amr[num],&car::car_download_map,sendthread[num],&SendThread::download_map);
    connect(amr[num],&car::car_load_map,sendthread[num],&SendThread::load_map);
    connect(amr[num],&car::car_upload_map,sendthread[num],&SendThread::upload_map);
    //开启通信线程
    sendtask[num]->start();
    recvtask[num]->start();
}

void MainWindow::delete_thread(int num){
    recvtask[num]->quit();
    sendtask[num]->quit();
    recvtask[num]->wait();
    sendtask[num]->wait();
    delete recvthread[num];
    delete sendthread[num];
    delete recvtask[num];
    delete sendtask[num];
}

//1车上线
void MainWindow::on_startButton_clicked()
{
    amr[I_AMR_B1] = new car();
    connect_thread(I_AMR_B1, amr[I_AMR_B1]);
    QString ip = ui->enter_ip->text();  //网络页面输入ip地址
    emit amr[I_AMR_B1]->ConnectSend(ip);
    amr[I_AMR_B1]->online_status = 1;
    //界面状态改变
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
    setStatusLed(ui->status_1,1);
}

//1车下线
void MainWindow::on_stopButton_clicked()
{

    amr[I_AMR_B1]->online_status = 0;
    emit amr[I_AMR_B1]->DisconnectSend(I_AMR_B1);
    ui->startButton->setDisabled(false);
    ui->stopButton->setDisabled(true);
    setStatusLed(ui->status_1,0);
    delete amr[I_AMR_B1];

}


/*****************************************
 * 状态灯切换函数
 * label:要设置的状态灯  color：0红 1绿 2黄
*****************************************/
void MainWindow::setStatusLed(QLabel *label, int color)
{
    QString background = "background-color:";
    switch (color) {
    case 0: //红色
        background += "rgb(255,0,0)";
        break;
    case 1: //绿色
        background += "rgb(0,255,0)";
        break;
    case 2: //黄色
        background += "rgb(255,255,0)";
        break;
    }
    label->setStyleSheet(background);
}



/*****************************************
 * 启动建图以及接受实时的扫图图像画面
 * 一系列和地图相关的函数
*****************************************/


void SendThread::requestFinished(QNetworkReply *reply)
{
    if(reply->error()!=QNetworkReply::NoError){
        //处理中的错误信息
        qDebug()<<"reply error:"<<reply->errorString();
    }else{
        //请求方式
        qDebug()<<"operation:"<<reply->operation();
        //状态码
        qDebug()<<"status code:"<<reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug()<<"url:"<<reply->url();
        //qDebug()<<"raw header:"<<reply->rawHeaderList();
        //获取响应信息
        if(!send_car->pixmap.loadFromData(reply->readAll()))
         {
             qDebug()<<"网络地址获取图片失败";
         }
        send_car->pixmap.loadFromData(reply->readAll());
        //const QByteArray reply_data=reply->readAll();
        //qDebug()<<"read all:"<<reply_data;
    }
    reply->deleteLater();
}
void SendThread::http_slam()
{
    m_manager = new QNetworkAccessManager(this);    //新建QNetworkAccessManager对象
    connect(m_manager,SIGNAL(finished(QNetworkReply*)), this,
            SLOT(requestFinished(QNetworkReply*))); //关联信号和槽
    QNetworkRequest request;
    request.setUrl(QUrl("http://ip:9301/slam"));
    request.setRawHeader("Content-Type","image/png");
    m_manager->get(request);//发送请求
    qDebug()<<"正在发送请求";

}
void SendThread::start_slam()
{
    QJsonObject slam;
    slam.insert("slam_type",2);
    slam.insert("real_time",true);
    QJsonDocument doc;
    doc.setObject(slam);
    QByteArray sendData = doc.toJson(QJsonDocument::Indented);
    write_data(6100,Other,sendData,0);
    send_car->slam_flag=1;
}


void SendThread::stop_slam()
{
    write_data(6101,Other);
    send_car->slam_flag=0;
}



void SendThread::load_map(QString map)
{
    QJsonObject map_name;
    map_name.insert("map_name",map);
    QJsonDocument doc;
    doc.setObject(map_name);
    QByteArray sendData = doc.toJson(QJsonDocument::Indented);
    write_data(2022,Ctrl,sendData,0);
}
void SendThread::download_map(QString map)
{
    QJsonObject map_name;
    map_name.insert("map_name",map);
    QJsonDocument doc;
    doc.setObject(map_name);
    QByteArray sendData = doc.toJson(QJsonDocument::Indented);
    write_data(4011,Config,sendData,0);
    QString map2= recv_data();
    QJsonDocument j_map=QJsonDocument::fromJson(map2.toLocal8Bit().data());

    QFile file("C:\\WWCC\\实验室\\map读取\\download_map\\test.json");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qDebug() << "file error!";
    }
    file.write(j_map.toJson());
    file.close();   // 关闭file
}

void SendThread::upload_map()
{
    QFile file("C:\\WWCC\\实验室\\map读取\\maps\\777.smap");
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "open error" << file.fileName();

    }
    else
    {
        QJsonParseError jerr;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &jerr);
        QByteArray sendData = doc.toJson(QJsonDocument::Indented);
        write_data(4010,Config,sendData,0);
    }
}

QString SendThread::recv_data()
{
    config_tcp->waitForReadyRead();
    QByteArray message = config_tcp->readAll();
    int size = message.size();


    if(size > 0){
        char a0 = message.at(0);

        if (uint8_t(a0) == 0x5A){//检测第一位是否为0x5A.
            if (size >= 16) {//返回的数据最小长度为16位,如果大小小于16则数据不完整等待再次读取.
                XHeader* header = new XHeader;
                memcpy(header, message.data(), 16);

                uint32_t data_size;//返回数据区总长值.
                qToBigEndian(header->_length,(uint8_t*)&(data_size));
                delete header;

                uint32_t remaining_size = size - 16;//已读数据总长度 - 头部总长度16 = 现有数据区长度.
                //如果返回数据长度值 大于 已读取数据长度 表示数据还未读取完整，跳出循环等待再次读取..
               while (data_size > remaining_size) {
                    _lastMessage = message;
                    message.clear();
                    config_tcp->waitForReadyRead();
                    message = config_tcp->readAll();
                    remaining_size += message.size();
                    message = _lastMessage + message;

                }
                    //截取报头16位后面的数据区数据.
                    QByteArray json_data = message.mid(16,data_size);
                    //qDebug()<<"recv:"<<json_data;
                    _lastMessage.clear();

                    QString json_string = QString(json_data);
                    return json_string;

            } else{
                qDebug()<<"error!帧头不完整";
                return 0;
            }
        }else{
            //报头数据错误.
            qDebug()<<"error!帧首不对";
            return 0;
        }
    }
    qDebug()<<"error!没收到数据";
    return 0;
}

QString RecvThread::get_map()
{
    write_data(1300);
    QString map = recv_data();
    return map;
}

QString RecvThread::map_load_state()
{
    write_data(1022);
    QString state = recv_data();
    return state;
}




















