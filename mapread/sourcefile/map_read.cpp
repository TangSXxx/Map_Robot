#include "map_read.h"
#include <cmath>
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"
#include <rapidjson/writer.h>
#include <cstdio>
#include<QFile>
#include<QFileDialog>
#include <QTime>
#include <mutex>

#define file_topdir  "./"
#define FILENAME "..//mapfile//lxmap.json"

using namespace rapidjson;
std::mutex mtx1;
map_read::map_read()
{
    size_x=0;
    size_y=0;
    origin_x=-4.140558;
    origin_y=-11.01;
    cur_pose.x=0;
    cur_pose.y=0;
    x_left= -3;
    x_right = 5;
    y_left= -5;
    y_right = 5;
    map_move = false;
    //cJSON* m_cjsonStr=NULL;
    carimage.load("C:/WWCC/upper_computer/qt_mapread/mapread/car.png");
    carimage=carimage.scaled(40,40);
    car_matrix.rotate(90);
    carimage=carimage.transformed(car_matrix, Qt::SmoothTransformation);
    car_yaw=0;
}

void map_read::get_car(car_test* car){
    m_car = car;
}

map_read::~map_read()
{
    //cJSON_Delete(this->m_cjsonStr);
}

void map_read::get_size()
{
    QJsonObject rootObj = this->m_doc.object();
    QJsonValue headerValue = rootObj.value("header");
    // 判断是不是对象类型
    if (headerValue.type() == QJsonValue::Object) {
        // 转换成对象类型
        QJsonObject headerValueObj = headerValue.toObject();
        // 根据建获取值
        QJsonValue xyValue = headerValueObj.value("maxPos");
        // 判断是不是对象类型
        if (xyValue.type() == QJsonValue::Object) {
            // 转换成对象类型
            QJsonObject xyObj = xyValue.toObject();
            // 根据建获取值
            QJsonValue  xValue = xyObj.value("x");
            // 最后转换成对应类型就解析出来了！
            this->size_x=xValue.toInt()*0.02;
            QJsonValue yValue = xyObj.value("y");
            this->size_y=yValue.toInt()*0.02;
        }
    }

    this->origin_x=-4.140558;
    this->origin_y=-11.01;
}



void map_read::get_json()
{

    QFile file(FILENAME);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "can't open error!";
        return;
    }
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QString str = stream.readAll();
    file.close();
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
    if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
        qDebug() << "Json格式错误！" << jsonError.error;
        return;
    }
    this->m_doc = doc;
}

void map_read::get_map()
{
    if(!Mypoints.empty())
    {
        Mypoints.clear();
    }
    double v_double_x = 0.0;
    double v_double_y = 0.0;
    double x, y = 0;
    MyPoint mypoint;

    QJsonObject rootObj = this->m_doc.object();
    QJsonValue xyValue = rootObj.value("normalPosList");
    if (xyValue.type() == QJsonValue::Array) {
        // 转换成数组类型
        QJsonArray xyArray = xyValue.toArray();
        // 遍历数组
        for (int i = 0; i < xyArray.count(); i++) {
            // 获取数组的第一个元素，类型是QJsonValue
            QJsonValue xyValueChild = xyArray.at(i);
            // 判断是不是对象类型
            if (xyValueChild.type() == QJsonValue::Object) {
                // 转换成对象类型
                QJsonObject xyObj = xyValueChild.toObject();
                // 最后通过value函数就可以获取到值了，解析成功
                QJsonValue xValue = xyObj.value("x");
                QJsonValue yValue = xyObj.value("y");
                v_double_x = xValue.toDouble();
                x = v_double_x*0.02 + this->origin_x;
                v_double_y = yValue.toDouble();
                y = v_double_y*0.02 + this->origin_y;
                mypoint.x=x;
                mypoint.y=y;
                Mypoints.push_back(mypoint);
            }

        }
        int size=Mypoints.size();
        this->sum_plot=size;
        // printf("sum_size = %d\n", size);
    }
}

void map_read::get_mark()
{
    if(!Mymarks.empty())
    {
        Mymarks.clear();
    }
    MyMark mymark;
    QJsonObject rootObj = this->m_doc.object();
    QJsonValue advancedPointListValue = rootObj.value("advancedPointList");
    if(advancedPointListValue.type() == QJsonValue::Array)
    {
        QJsonArray advancedPointListArray = advancedPointListValue.toArray();
        for (int i = 0; i < advancedPointListArray.count(); i++) {
            QJsonValue advancedPointListValueChild = advancedPointListArray.at(i);
            if (advancedPointListValueChild.type() == QJsonValue::Object)
            {
                QJsonObject advancedPointListObj = advancedPointListValueChild.toObject();
                QJsonValue instanceNameValue = advancedPointListObj.value("instanceName");
                //qDebug() << "instanceName = " << instanceNameValue.toString();
                mymark.instanceName = instanceNameValue.toString();
                QJsonValue poseValue = advancedPointListObj.value("pos");
                if (poseValue.type() == QJsonValue::Object)
                {
                    QJsonObject poseObj = poseValue.toObject();
                    QJsonValue xValue = poseObj.value("x");
                    mymark.x=xValue.toDouble();
                    //qDebug() << "x = " << xValue.toDouble();
                    QJsonValue yValue = poseObj.value("y");
                    mymark.y=yValue.toDouble();
                    //qDebug() << "y = " << yValue.toDouble();
                }
                Mymarks.push_back(mymark);
            }



        }
    }
}

void map_read::get_path()
{
    if(!Mypaths.empty())
    {
        Mypaths.clear();
    }
    MyPath mypath;
    QJsonObject rootObj = this->m_doc.object();
    QJsonValue advancedCurveListValue = rootObj.value("advancedCurveList");
    if (advancedCurveListValue.type() == QJsonValue::Array)
    {
        QJsonArray advancedCurveListArray = advancedCurveListValue.toArray();
        for (int i = 0; i < advancedCurveListArray.count(); i++)
        {
            QJsonValue advancedCurveListValueChild = advancedCurveListArray.at(i);
            if (advancedCurveListValueChild.type() == QJsonValue::Object)
            {

                QJsonObject advancedCurveListObj = advancedCurveListValueChild.toObject();
                QJsonValue classNameValue = advancedCurveListObj.value("className");
                if(classNameValue.toString()=="StraightPath")
                {
                     QJsonValue startPosValue = advancedCurveListObj.value("startPos");
                     QJsonValue endPosValue = advancedCurveListObj.value("endPos");

                     if (startPosValue.type() == QJsonValue::Object)
                     {
                         QJsonObject startPosObj = startPosValue.toObject();
                         QJsonValue instanceNameValue = startPosObj.value("instanceName");
                         mypath.startPos=instanceNameValue.toString();
                         QJsonValue PosValue = startPosObj.value("pos");
                         if (PosValue.type() == QJsonValue::Object)
                         {
                             QJsonObject startPosObj = PosValue.toObject();
                             QJsonValue xValue = startPosObj.value("x");
                             QJsonValue yValue = startPosObj.value("y");
                             mypath.start.x = xValue.toDouble();
                             mypath.start.y = yValue.toDouble();
                             //qDebug() << "startPos = " <<mypath.startPos;
                             //qDebug() << "startPos = " <<xValue.toDouble()<<" "<<yValue.toDouble();
                         }                        
                     }

                     if (endPosValue.type() == QJsonValue::Object)
                     {
                         QJsonObject endPosObj = endPosValue.toObject();
                         QJsonValue instanceNameValue = endPosObj.value("instanceName");
                         mypath.endPos=instanceNameValue.toString();
                         QJsonValue PosValue = endPosObj.value("pos");
                         if (PosValue.type() == QJsonValue::Object)
                         {
                             QJsonObject endPosObj = PosValue.toObject();
                             QJsonValue xValue = endPosObj.value("x");
                             QJsonValue yValue = endPosObj.value("y");
                             mypath.end.x = xValue.toDouble();
                             mypath.end.y = yValue.toDouble();
                         }
                     }

                     Mypaths.push_back(mypath);
                }
            }
        }
    }
}
//判断给的路径是否已经存在
bool map_read::find_path(QString start_mark,QString end_mark)
{
    int path_sum = Mypaths.size();
    int flag=0;
    for(int i=0;i<path_sum;i++)
    {
        if(Mypaths[i].startPos==start_mark&&Mypaths[i].endPos==end_mark)
        {
            flag++;
            //qDebug() << Mypaths[i].startPos <<"-----"<<Mypaths[i].endPos;
        }
    }
    if(flag==1)
    {
        return true;
    }
    else
    {
        //qDebug() <<"没有该路径"<<flag;
        return false;
    }
}
//提取给定路径起始站点的坐标信息
MyPath map_read::mark_path(QString start_mark,QString end_mark)
{
    MyPath mypath;
    MyPath false_mypath={0};
    int flag=0;
    if(!Mymarks.empty())
    {
        int sum = Mymarks.size();
        for(int i=0;i<sum;i++)
        {
            if(Mymarks[i].instanceName==start_mark)
            {
                mypath.startPos=start_mark;
                mypath.start.x=Mymarks[i].x;
                mypath.start.y=Mymarks[i].y;
                //qDebug() << mypath.startPos;
                flag++;
            }
            if(Mymarks[i].instanceName==end_mark)
            {
                mypath.endPos=end_mark;
                mypath.end.x=Mymarks[i].x;
                mypath.end.y=Mymarks[i].y;
                //qDebug() << mypath.end.x;
                flag++;
            }
        }
        if(flag==2)
        {

            return mypath;
        }
        else
        {
            qDebug() << "输入的点不正确" ;
            return false_mypath;
        }
    }
    else
    {
        qDebug() << "没有读取地图的站点信息" ;
        return false_mypath;
    }
}

void map_read::add_path(QString start_mark,QString end_mark)
{
    MyPath path;
    get_mark();
    get_path();
    if(!find_path(start_mark,end_mark))
    {
        path=mark_path(start_mark,end_mark);
        QJsonObject rootObj = this->m_doc.object();
        QJsonValue advancedCurveListValue = rootObj.value("advancedCurveList");
        if (advancedCurveListValue.type() == QJsonValue::Array)
        {
            QJsonArray advancedCurveListArray = advancedCurveListValue.toArray();
            QJsonObject addObj;
            QJsonObject addspObj;
            QJsonObject addspxyObj;
            QJsonObject addepObj;
            QJsonObject addepxyObj;

            addObj.insert("className", "StraightPath");
            QString tem;
            tem=start_mark+"-"+end_mark;
            addObj.insert("instanceName", tem);


            addspObj.insert("instanceName",path.startPos);
            addspxyObj.insert("x",path.start.x);
            addspxyObj.insert("y",path.start.y);
            addspObj.insert("pos",addspxyObj);
            addObj.insert("startPos",addspObj);

            addepObj.insert("instanceName",path.endPos);
            addepxyObj.insert("x", path.end.x);
            addepxyObj.insert("y", path.end.y);
            addepObj.insert("pos",addepxyObj);
            addObj.insert("endPos",addepObj);

            QJsonArray propertyArray;
            QJsonObject Object1;
            Object1.insert("key", "direction");
            Object1.insert("type", "int");
            Object1.insert("value", "MA==");
            Object1.insert("int32Value", 0);
            QJsonObject Object2;
            Object2.insert("key", "movestyle");
            Object2.insert("type", "int");
            Object2.insert("value", "MA==");
            Object1.insert("int32Value", 0);
            propertyArray.append(Object1);
            propertyArray.append(Object2);
            addObj.insert("property",propertyArray);

            advancedCurveListArray.push_back(addObj);
            rootObj["advancedCurveList"] = advancedCurveListArray;

            m_doc.setObject(rootObj);
            QFile file(FILENAME);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                qDebug() << "can't open error!";
                return;
                }
            QTextStream stream(&file);
            stream.setCodec("UTF-8");		// 设置写入编码是UTF8
            stream << m_doc.toJson();
            file.close();
            Mypaths.push_back(path);
            //qDebug() << "写入了吧";
        }

    }
    else
    {
        qDebug() << "输入的路径已经存在了" ;
    }
}




void map_read::Remove_path(QString start_mark, QString end_mark)
{
    QString start,end;
    if(find_path(start_mark,end_mark))
    {
        QJsonObject rootObj = this->m_doc.object();
        QJsonValue advancedCurveListValue = rootObj.value("advancedCurveList");
        if (advancedCurveListValue.type() == QJsonValue::Array)
        {

            QJsonArray advancedCurveListArray = advancedCurveListValue.toArray();
            for (int i = 0; i < advancedCurveListArray.count(); i++)
            {
                QJsonValue advancedCurveListValueChild = advancedCurveListArray.at(i);
                if (advancedCurveListValueChild.type() == QJsonValue::Object)
                {

                    QJsonObject advancedCurveListObj = advancedCurveListValueChild.toObject();
                    QJsonValue classNameValue = advancedCurveListObj.value("className");
                    if(classNameValue.toString()=="StraightPath")
                    {
                         QJsonValue startPosValue = advancedCurveListObj.value("startPos");
                         QJsonValue endPosValue = advancedCurveListObj.value("endPos");

                         if (startPosValue.type() == QJsonValue::Object)
                         {
                             QJsonObject startPosObj = startPosValue.toObject();
                             QJsonValue instanceNameValue = startPosObj.value("instanceName");
                             start=instanceNameValue.toString();

                         }

                         if (endPosValue.type() == QJsonValue::Object)
                         {
                             QJsonObject endPosObj = endPosValue.toObject();
                             QJsonValue instanceNameValue = endPosObj.value("instanceName");
                             end=instanceNameValue.toString();
                         }

                    }
                }
                if(start==start_mark&&end==end_mark)
                {
                    advancedCurveListArray.removeAt(i);
                    rootObj["advancedCurveList"] = advancedCurveListArray;
                    m_doc.setObject(rootObj);
                    QFile writeFile(FILENAME);
                    if (!writeFile.open(QFile::WriteOnly | QFile::Truncate)) {
                        qDebug() << "can't open error!";
                        return;
                    }
                    // 将修改后的内容写入文件
                    QTextStream wirteStream(&writeFile);
                    wirteStream.setCodec("UTF-8");		// 设置读取编码是UTF8
                    wirteStream << m_doc.toJson();		// 写入文件
                    writeFile.close();					// 关闭文件
                    qDebug() << "成功删除路径";
                    break;
                }

            }
        }
    }
    else
    {
         qDebug() << "删除的路径并不存在";
    }
}

void map_read::add_mark(QString Mark,float x,float y)
{
    MyMark mark;
    int Mymarks_size=Mymarks.size();
    int flag = 0;
    for(int i=0;i < Mymarks_size;i++)
    {
        if(Mark==Mymarks[i].instanceName)
        {
            qDebug() << "该站点已经存在，请删除后再进行增加";
            flag++;
        }
    }
    if(flag==0)
    {
        QJsonObject rootObj = this->m_doc.object();
        QJsonValue advancedPointListValue = rootObj.value("advancedPointList");
        if(advancedPointListValue.type() == QJsonValue::Array)
        {
            QJsonArray advancedPointListArray = advancedPointListValue.toArray();
            QJsonObject addObj;
            addObj.insert("className", "LocationdMark");
            addObj.insert("instanceName", Mark);
            QJsonObject addxyObj;
            addxyObj.insert("x", x);
            addxyObj.insert("y", y);
            addObj.insert("pos",addxyObj);
            advancedPointListArray.push_back(addObj);
            rootObj["advancedPointList"] = advancedPointListArray;
            mark.x=x;
            mark.y=y;
            mark.instanceName=Mark;
            Mymarks.push_back(mark);
            qDebug() << "成功写入站点："<< Mark;
            m_doc.setObject(rootObj);
            QFile file(FILENAME);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                qDebug() << "can't open error!";
                return;
                }
            QTextStream stream(&file);
            stream.setCodec("UTF-8");		// 设置写入编码是UTF8
            stream << m_doc.toJson();
            file.close();
        }
    }
}

void map_read::Remove_mark(QString Mark)
{
    int flag = 0;
    get_mark();
    int path_size=Mypaths.size();
    for(int i=0;i<path_size;i++)
    {
        if(Mypaths[i].startPos==Mark||Mypaths[i].endPos==Mark)
        {
            qDebug() << "start: "<<Mypaths[i].startPos<<"end: "<<Mypaths[i].endPos;
            Remove_path(Mypaths[i].startPos,Mypaths[i].endPos);

        }
        path_size=Mypaths.size();
    }
    QJsonObject rootObj = this->m_doc.object();
    QJsonValue advancedPointListValue = rootObj.value("advancedPointList");
    if(advancedPointListValue.type() == QJsonValue::Array)
    {
        QJsonArray advancedPointListArray = advancedPointListValue.toArray();
        for (int i = 0; i < advancedPointListArray.count(); i++) {
            QJsonValue advancedPointListValueChild = advancedPointListArray.at(i);
            if (advancedPointListValueChild.type() == QJsonValue::Object)
            {
                QJsonObject advancedPointListObj = advancedPointListValueChild.toObject();
                QJsonValue instanceNameValue = advancedPointListObj.value("instanceName");
                if(instanceNameValue.toString() == Mark)
                {
                    advancedPointListArray.removeAt(i);
                    rootObj["advancedPointList"] = advancedPointListArray;
                    flag++;

                    m_doc.setObject(rootObj);
                    QFile writeFile(FILENAME);
                    if (!writeFile.open(QFile::WriteOnly | QFile::Truncate)) {
                        qDebug() << "can't open error!";
                        return;
                    }
                    // 将修改后的内容写入文件
                    QTextStream wirteStream(&writeFile);
                    wirteStream.setCodec("UTF-8");		// 设置读取编码是UTF8
                    wirteStream << m_doc.toJson();		// 写入文件
                    writeFile.close();					// 关闭文件
                    get_mark();
                }
            }
        }
    }


    if(flag==0)
    {
       qDebug() << "输入站点不存在" << Mark;
    }
    else if(flag == 1)
    {
        qDebug() << "成功删除站点" << Mark;
    }
    else
    {
        qDebug() << "程序写的有问题" ;
    }
}



void map_read::Remove_obstacles(double x1, double y1,double x2,double y2)
{
    x1=x1-origin_x;
    x2=x2-origin_x;
    y1=-(y1+2.8)-origin_y;
    y2=-(y2+2.8)-origin_y;
    x1=int(x1/0.02);
    x2=int(x2/0.02);
    y1=int(y1/0.02);
    y2=int(y2/0.02);
    qDebug() << x1<< y1<<x2<<y2;
    if(x2>x1 && y2>y1 &&x1>=0 && y1>=0 && x2<=this->size_x/0.02 && y2<=this->size_y/0.02)
    {
        double v_double_x = 0.0;
        double v_double_y = 0.0;
        int x, y = 0;
        int flag=1;
        while(flag!=0)
        {
            qDebug() << "进入循环";
            QJsonObject rootObj = this->m_doc.object();
            QJsonValue xyValue = rootObj.value("normalPosList");
            flag = 0;
            if (xyValue.type() == QJsonValue::Array) {
                QJsonArray xyArray = xyValue.toArray();
                for (int i = 0; i < xyArray.count(); i++) {
                    QJsonValue xyValueChild = xyArray.at(i);
                    if (xyValueChild.type() == QJsonValue::Object) {
                        QJsonObject xyObj = xyValueChild.toObject();
                        QJsonValue xValue = xyObj.value("x");
                        QJsonValue yValue = xyObj.value("y");
                        v_double_x = xValue.toDouble();
                        x = v_double_x;

                        v_double_y = yValue.toDouble();
                        y = v_double_y;
                        if(x>=x1&&x<=x2&&y>=y1&&y<=y2)
                        {
                            flag++;
                            xyArray.removeAt(i);
                        }
                    }
                }
                qDebug() << "第一次找点"<<"flag = "<<flag;
                rootObj["normalPosList"]=xyArray;
                qDebug() << "修改"<<flag;
                m_doc.setObject(rootObj);
                QFile writeFile(FILENAME);
                if (!writeFile.open(QFile::WriteOnly | QFile::Truncate)) {
                    qDebug() << "can't open error!";
                    return;
                }
                QTextStream wirteStream(&writeFile);
                wirteStream.setCodec("UTF-8");
                wirteStream << m_doc.toJson();
                writeFile.close();
                qDebug() << "写入"<<flag;
            }
     }
       qDebug() << "flag = "<< flag ;
    }
    else
    {
       qDebug() << "请输入正确的坐标 " ;
    }
    get_map();
    get_size();
}

void map_read::txt_to_vectordouble1(QString pathname)
{
    v_point.clear();
    path_point.clear();

    QStringList user_data1;
    QStringList user_data2;
    QString in;
    MyPoint z;

    if(online)
    {
        QString str=m_car->map_str;
        QJsonParseError jsonError;
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8(), &jsonError);
        if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
            qDebug() << "Json格式错误！" << jsonError.error;
            return;
        }
        QJsonObject rootObj = doc.object();
        QJsonValue messageValue = rootObj.value("message");
            in=messageValue.toString();
            int path_place = in.indexOf(" path");
            int x_place = in.indexOf("x");
            int y_place = in.indexOf("y");
            int laser_place = in.indexOf("laser");
            qDebug()<<"x_place: "<<x_place<<"laser_place: "<<laser_place<<"path_place: "<<path_place;
            if(path_place!=-1 && x_place!=-1 && y_place!=-1 && laser_place!=-1)
            {
                user_data1=in.left(path_place).split(" ");
                for(int i=0;i<user_data1.size();i++)
                {
                        if(i==0||i==2||i==4)
                        {
                            continue;
                        }
                        if(i==1)
                        {
                            cur_pose.x=user_data1[1].toDouble();
                            qDebug() << "cur_pose.x"<<user_data1[0].toDouble();
                        }
                        else if(i==3)
                        {
                            cur_pose.y=user_data1[3].toDouble();
                            qDebug() << "cur_pose.y"<<user_data1[1].toDouble();

                        }
                        else if(i==5)
                        {
                            car_yaw=user_data1[5].toDouble();
                            qDebug() << "car_yaw"<<car_yaw;
                            i++;
                        }
                        else
                        {
                            if(i%2==1)
                            {
                                z.x=user_data1[i].toDouble();
                            }
                            else
                            {
                                z.y=user_data1[i].toDouble();
                                v_point.push_back(z);
                                //qDebug() << "z.x"<<z.x<<"z.y"<<z.y;
                            }
                        }
                 }

                if(path_place!=0)
                {
                    user_data2=in.right(in.size()-path_place-5).split(" ");
                    qDebug()<<in.right(in.size()-path_place-5);
                    for(int i=1;i<user_data2.size();i++)
                    {
                                if(i%2!=1)
                                {
                                    z.x=user_data2[i].toDouble();
                                }
                                else
                                {
                                    z.y=user_data2[i].toDouble();
                                    path_point.push_back(z);
                                    //qDebug() << "path_point.x"<<z.x<<"path_point.y"<<z.y;
                                }

                     }
                }

            }
            else{
                qDebug() << "错误的";
            }
    }
}



void map_read::car_pose()
{
    txt_to_vectordouble1("C:\\dhblab_meta_socket\\storage\\devices\\_3.txt");
}

bool map_read::pose_nav(double x,double y,double yaw)
{
    //QFile file("C:\\dhblab_meta_socket\\storage\\devices\\_2.txt");
    QFile file("C:\\dhblab_meta_socket\\storage\\devices\\unicast_3.txt");
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "can't open error!";
        return false;
    }
    QTextStream out(&file);
    QDateTime time = QDateTime::currentDateTime();
    QString time_s =time .toString("hh:mm:ss.zzz");
    nav_endpose.x = x;
    nav_endpose.y = y;
    out<<"pose"<<" "<<x<<" "<<y<<" "<<yaw<<" "<<time_s;
    return true;
}
bool map_read::pose_nav(double x1,double y1,double yaw1,double x2,double y2,double yaw2)
{
    QFile file("C:\\dhblab_meta_socket\\storage\\devices\\_3.txt");
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "can't open error!";
        return false;
    }
    QTextStream out(&file);
    QDateTime time = QDateTime::currentDateTime();
    QString time_s =time .toString("hh:mm:ss.zzz");
    out<<"mark"<<" "<<x1<<" "<<y1<<" "<<yaw1<<" "<<x2<<" "<<y2<<" "<<yaw2<<" "<<time_s;
    return true;
}

bool map_read::mark_nav(QString mark_s,QString mark_e,double yaw1,double yaw2)
{
    get_json();
    get_size();
    get_mark();
    get_path();
    if(!find_path(mark_s,mark_e))
    {
       qDebug() << "no path error!";
       return false;
    }
    MyPath path;
    path=mark_path(mark_s,mark_e);
    if(pose_nav(path.start.x,path.start.y,yaw1,path.end.x,path.end.y,yaw2))
    {
        return true;
    }
    else
    {
        return false;
    }
}




