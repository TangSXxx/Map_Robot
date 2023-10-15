#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map_read.h"
#include "qcustomplot.h"
#include <iostream>
#include <sstream>
#include <QDebug>
#include <mutex>
#include <windows.h>
std::mutex mtx;
QCPGraph * curGraph;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->tab->setStyleSheet("QWidget#tab{"
                           "background-color:#e6e6e6;"
                           "border:1px solid #eeeeee;}");

    ui->widget->setInteraction(QCP::iRangeDrag, true); //鼠标单击拖动
    ui->widget->setInteraction(QCP::iRangeZoom, true); //滚轮滑动缩放
    //ui->widget->setSelectionRectMode(QCP::srmSelect);
    ui->widget->setSelectionRectMode(QCP::SelectionRectMode::srmSelect);
    ui->widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));
    ui->widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));
    paintmap();
    startTimer(50);

    connect(ui->widget,SIGNAL(mousePress(QMouseEvent*)),
                    this, SLOT(on_mousePressEvent(QMouseEvent*)));

   //设置鼠标悬停时的显示的文本
    ui->ip_button->setToolTip("连接端口");
    ui->move_map->setToolTip("设置地图可移动");
    ui->add->setToolTip("增加");
    ui->del->setToolTip("删除");
    ui->clamp->setToolTip("抓取");
    ui->nav->setToolTip("导航");

    //设置鼠标悬停时状态栏显示的信息
    ui->ip_button->setStatusTip("点击跳转新建端口连接窗口");
    ui->move_map->setStatusTip("点击跳转设置地图可移动窗口");
    ui->add->setStatusTip("点击跳转增加站点、路径等信息的窗口");
    ui->del->setStatusTip("点击跳转删除窗口");
    ui->clamp->setStatusTip("点击跳转抓取窗口");
    ui->nav->setStatusTip("点击跳转导航窗口");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_mousePressEvent(QMouseEvent *event)
{//鼠标单击事件
   qDebug()<<"1234";
}



void MainWindow::on_pushButton_clicked()
{
        QString mark = ui->lineEdit->text();
        map.get_json();
        map.get_size();
        map.get_mark();
        map.get_path();
        map.Remove_mark(mark);
        paintmap();

}

void MainWindow::paintmap(){
    ui->widget->clearGraphs();
    ui->widget->clearItems();
    map.get_json();
    map.get_size();
    map.get_map();
    map.get_mark();
    map.get_path();
    QVector<double> x(map.sum_plot),y(map.sum_plot);
    for(int i=0;i<map.sum_plot;i++){
        x[i]=map.Mypoints.back().x;
        y[i]=-map.Mypoints.back().y-2.8;
        map.Mypoints.pop_back();
    }
    QPen mypen;
    mypen.setWidth(3);
    mypen.setColor(Qt::black);

    curGraph = ui->widget->addGraph();
    ui->widget->graph(0)->setPen(mypen);
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssSquare, 0.4));
    ui->widget->graph(0)->addData(x,y);
    ui->widget->graph(0)->setAdaptiveSampling(true);
    int mark_num=map.Mymarks.size();
    for(int i=0;i<mark_num;i++)
    {
        QCPItemText *textLabel = new QCPItemText(ui->widget);//在QCustomplot中新建文字框
        textLabel->setPositionAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//文字布局：顶、左对齐
        textLabel->position->setType(QCPItemPosition::ptPlotCoords);//位置类型（当前轴范围的比例为单位/实际坐标为单位）
        textLabel->position->setCoords(map.Mymarks[i].x, map.Mymarks[i].y); //把文字框放在X轴的中间，Y轴的最顶部
        textLabel->setText(map.Mymarks[i].instanceName);
        textLabel->setFont(QFont("Microsoft YaHei", 10, QFont::Bold)); //字体大小
        textLabel->setPen(QPen(Qt::green,1,Qt::DashDotDotLine)); //边框颜色
        textLabel->setPadding(QMargins(12,12,12,12));//文字距离边框几个像素

        textLabel->setSelectable(true);
        //qDebug() << "instanceName = " <<map.Mymarks[i].instanceName ;
        //qDebug() << " x = " <<map.Mymarks[i].x/map.size_x<<" y = "<<map.Mymarks[i].y/map.size_y;
    }
    int path_sum=map.Mypaths.size();
    for(int i=0;i<path_sum;i++)
    {

        QCPItemLine *pathline = new QCPItemLine(ui->widget);
        pathline->start->setCoords(map.Mypaths[i].start.x,map.Mypaths[i].start.y);
        pathline->end->setCoords(map.Mypaths[i].end.x,map.Mypaths[i].end.y);
        pathline->setHead(QCPLineEnding::esSpikeArrow);
        pathline->setPen(QPen(Qt::blue, 0.5, Qt::DotLine)); //字体颜色

    }



    ui->widget->legend->setBrush(QColor(255,255,255,0));//设置图例背景
    ui->widget->xAxis->setLabel("x(m)");
    ui->widget->yAxis->setLabel("y(m)");
    ui->widget->xAxis->setRange(map.x_left,map.x_right);
    ui->widget->yAxis->setRange(map.y_left,map.y_right);

    ui->widget->xAxis->grid()->setSubGridVisible(true);     // 显示子网格线
    ui->widget->yAxis->grid()->setSubGridVisible(true);

    ui->widget->replot(ui->widget->rpQueuedReplot);
    //ui->widget->rescaleAxes();
    //ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}

void MainWindow::on_pushButton_2_clicked()
{
    if(!ui->lineEdit_2->text().isEmpty()&&!ui->lineEdit_3->text().isEmpty()&&!ui->lineEdit_4->text().isEmpty())
    {
        QString mark=ui->lineEdit_2->text();
        float x=ui->lineEdit_3->text().toFloat();
        float y=ui->lineEdit_4->text().toFloat();
        map.get_json();
        map.get_size();
        map.get_mark();
        map.get_path();
        map.add_mark(mark,x,y);
        paintmap();
    }
    else
    {
        qDebug() <<"输入为空";
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString mark1=ui->lineEdit_5->text();
    QString mark2=ui->lineEdit_6->text();
    map.get_json();
    map.get_size();
    map.get_mark();
    map.add_path(mark1,mark2);
    paintmap();
}

void MainWindow::on_pushButton_4_clicked()
{
    QString mark1=ui->lineEdit_7->text();
    QString mark2=ui->lineEdit_8->text();
    map.get_json();
    map.get_size();
    map.get_mark();
    map.get_path();
    map.Remove_path(mark1,mark2);
    paintmap();
}

void MainWindow::on_pushButton_5_clicked()
{

    double x1=ui->lineEdit_9->text().toDouble();
    double y1=ui->lineEdit_10->text().toDouble();
    double x2=ui->lineEdit_11->text().toDouble();
    double y2=ui->lineEdit_12->text().toDouble();
    map.get_json();
    map.get_size();
    map.get_mark();
    map.Remove_obstacles(x1,y1,x2,y2);
    paintmap();
}

/*void MainWindow::on_pushButton_6_clicked()
{
    qDebug()<<" test "<<endl;
}*/





void MainWindow::timerEvent(QTimerEvent *event)
{
    if(map.online)
    {
        mtx.lock();
        map.get_json();
        map.car_pose();

        /*QCPItemEllipse *carpose= new QCPItemEllipse(ui->widget);
        QPen pen(Qt::red, 0.8, Qt::SolidLine, Qt::RoundCap);
        carpose->setPen(pen);
        double r =0.1;
        carpose->topLeft->setCoords(map.cur_pose.x-r, map.cur_pose.y+r);      //左上角位置 tL
        carpose->bottomRight->setCoords(map.cur_pose.x+r, map.cur_pose.y-r);*/


        map.car_matrix.rotate(map.car_yaw/3.1415926*180+90);
        map.carimage=map.carimage.transformed(map.car_matrix, Qt::SmoothTransformation);
        QCPItemPixmap *carimage = new QCPItemPixmap(ui->widget);
        carimage->setPixmap(map.carimage);
        carimage->topLeft->setCoords(map.cur_pose.x-0.1,map.cur_pose.y+0.2);


        QVector<double> x(map.v_point.size()),y(map.v_point.size());

        for(int i=0;i<map.v_point.size();i++){
            x[i]=map.v_point[i].x+map.cur_pose.x;
            y[i]=map.v_point[i].y+map.cur_pose.y;
        }

        QVector<double> z(map.path_point.size()),w(map.path_point.size());
        for(int i=0;i<map.path_point.size();i++){
            z[i]=map.path_point[i].x;
            w[i]=map.path_point[i].y;
            //qDebug() << "path_point.x"<<z[i]<<"path_point.y"<<w[i];
        }

        QPen mypen1;
        mypen1.setWidth(1);
        mypen1.setColor(Qt::green);
        QPen mypen2;
        mypen2.setWidth(1);
        mypen2.setColor(Qt::blue);

        ui->widget->addGraph();
        ui->widget->graph(1)->setPen(mypen1);
        ui->widget->graph(1)->setLineStyle(QCPGraph::lsNone);
        ui->widget->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssSquare, 0.6));
        ui->widget->graph(1)->addData(x,y);
        ui->widget->graph(1)->setAdaptiveSampling(true);

        ui->widget->addGraph();
        if(qAbs(map.nav_endpose.x - map.cur_pose.x) > 0.3 && qAbs(map.nav_endpose.y - map.cur_pose.y) > 0.3)
        {
            ui->widget->graph(2)->setPen(mypen2);
            ui->widget->graph(2)->setLineStyle(QCPGraph::lsNone);
            ui->widget->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssSquare, 2));
            ui->widget->graph(2)->addData(w,z);
            ui->widget->graph(2)->setAdaptiveSampling(true);
        }

        ui->widget->replot();
        ui->widget->removeGraph(1);
        ui->widget->removeGraph(2);
        ui->widget->removeItem(carimage);
        ui->widget->legend->setVisible(false);
        mtx.unlock();
    }

}



void MainWindow::on_pushButton_7_clicked()
{
    map.get_json();
    double x=ui->lineEdit_13->text().toFloat();
    double y=ui->lineEdit_14->text().toFloat();
    double yaw=ui->lineEdit_15->text().toFloat();
    if(!map.pose_nav(x,y,yaw))
    {
        qDebug() << "nav error!";
    }
}

void MainWindow::on_pushButton_8_clicked()
{
    map.get_json();
    QString mark1=ui->lineEdit_16->text();
    QString mark2=ui->lineEdit_17->text();
    double yaw1=ui->lineEdit_18->text().toFloat();
    double yaw2=ui->lineEdit_18->text().toFloat();
    if(!map.mark_nav(mark1,mark2,yaw1,yaw2))
    {
        qDebug() << "nav error!";
    }
}


void MainWindow::on_testplus_clicked()
{
    qDebug() << " error!";
}


void MainWindow::on_move_map_clicked()
{
    if(map.map_move)
    {
        map.map_move = false;
        ui->widget->setSelectionRectMode(QCP::SelectionRectMode::srmSelect);
        ui->move_map->setStyleSheet ("background-color: transparent;");
    }
    else
    {
        map.map_move = true;
        ui->widget->setSelectionRectMode(QCP::SelectionRectMode::srmNone);
        ui->move_map->setStyleSheet ("background-color: rgb(255, 255, 127);");
    }
}

void MainWindow::on_add_clicked()
{
    ui->interaction->setCurrentIndex(1);

}
void MainWindow::on_del_clicked()
{
    ui->interaction->setCurrentIndex(0);
}

void MainWindow::on_clamp_control_clicked()
{
    if(!ui->clamp_angle->text().isEmpty()&&!ui->clamp_distance->text().isEmpty()&&!ui->clamp_height->text().isEmpty())
    {
        float angle=ui->clamp_angle->text().toFloat();
        float distance=ui->clamp_distance->text().toFloat();
        float height = ui->clamp_height->text().toFloat();

        QFile file("C:\\dhblab_meta_socket\\storage\\devices\\_2.txt");
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            qDebug() << "can't open error!";
            return ;
        }
        QTextStream out(&file);
        QDateTime time = QDateTime::currentDateTime();
        QString time_s =time .toString("hh:mm:ss.zzz");
        out<< "jz" << " " << "angle" << " " << angle <<" "<<"distance"<<" "<<distance<<" "<<"height"<<" "<<height<<" "<<time_s;
    }
    else
    {
        qDebug() <<"输入为空";
    }
}

void MainWindow::on_clamp_clicked()
{
    ui->interaction->setCurrentIndex(2);
}

void MainWindow::on_nav_clicked()
{
    ui->interaction->setCurrentIndex(3);
}

void MainWindow::on_ip_button_clicked()
{
    ui->interaction->setCurrentIndex(4);
}
