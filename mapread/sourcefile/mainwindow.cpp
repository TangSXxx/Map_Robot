#include "mainwindow.h"

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
    ui->widget->setInteraction(QCP::iSelectPlottables,true);
    ui->widget->setInteraction(QCP::iSelectItems ,true);
    ui->widget->setSelectionRectMode(QCP::SelectionRectMode::srmSelect);
    ui->widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));
    ui->widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));

    paintmap();
    startTimer(100);

    /*connect(ui->widget,SIGNAL(mousePress(QMouseEvent*)),
                    this, SLOT(on_mousePressEvent(QMouseEvent*)));*/
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

    cartomap = new car_tcp(&map);
    tcp_thread = new QThread;
    cartomap->moveToThread(tcp_thread);
    qDebug()<<"主线程:"<<QThread::currentThreadId();
    qRegisterMetaType<uint16_t>("uint16_t");

    tcp_thread->start();
    connect(ui->NewIPButton,&QPushButton::clicked,cartomap,&car_tcp::start_listen);
    connect(this,&MainWindow::send_tcp,cartomap,&car_tcp::send_message);
    connect(ui->widget, &QCustomPlot::mouseMove, this, &MainWindow::on_mouseMoveEvent);
    connect(ui->widget, &QCustomPlot::mousePress, this, &MainWindow::on_mousePressEvent);
    connect(ui->widget, &QCustomPlot::mouseRelease, this, &MainWindow::on_mouseRealseEvent);



    //std::thread paint_thread = std::thread(std::mem_fn(MainWindow::time_paint),this);
    //paint_thread.detach();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_mousePressEvent(QMouseEvent *event)
{

    // 获取鼠标点击的坐标（相对于界面）
       QPoint mousePressPos = event->pos();

       // 将界面坐标转换为图表坐标
       double xValue = ui->widget->xAxis->pixelToCoord(mousePressPos.x());
       double yValue = ui->widget->yAxis->pixelToCoord(mousePressPos.y());

       // 获取点击位置下的图形元素
       QCPAbstractItem *item = ui->widget->itemAt(mousePressPos);


       if (item)
       {

           // 在这里执行与获取到的 item 有关的逻辑
           qDebug() << "Mouse pressed at" << mousePressPos << "on item";

           // 获取公共信息
           qDebug() << "Item coordinates: (" << xValue << "," << yValue << ")";

           // 如果是 QCPItemText
           if (QCPItemText *textItem = qobject_cast<QCPItemText*>(item))
           {
               QString text = textItem->text();
               cpot = text;
               qDebug() << "Item text:" << text;
               QPointF actualItemCoords = textItem->position->coords();
               QString x = QString("%1").arg(actualItemCoords.x());
               QString y = QString("%1").arg(actualItemCoords.y());
                ui->PotNameEdit->setText(text);
                ui->XposEdit->setText(x);
                ui->YposEdit->setText(y);
               qDebug() << "Actual item coordinates: (" << actualItemCoords.x() << "," << actualItemCoords.y() << ")";

           }
           // 如果是 QCPItemLine
           else if (QCPItemLine *lineItem = qobject_cast<QCPItemLine*>(item))
           {
               // 获取线的两个端点坐标
               QPointF startPoint = lineItem->start->coords();
               QPointF endPoint = lineItem->end->coords();
               QString sx = QString("(%1, %2)").arg(startPoint.x()).arg(startPoint.y());
               QString sy = QString("(%1, %2)").arg(endPoint.x()).arg(endPoint.y());
               ui->LineStartEdit->setText(sx);
               ui->LineEndEdit->setText(sy);
               qDebug() << "Line start point: (" << startPoint.x() << "," << startPoint.y() << ")";
               qDebug() << "Line end point: (" << endPoint.x() << "," << endPoint.y() << ")";
           }

           // 执行其他处理逻辑...
       }
       else
       {
           qDebug() << "Mouse pressed at" << mousePressPos << "on no item";
       }

}

void MainWindow::on_mouseRealseEvent(QMouseEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        qDebug() << "Ctrl key is pressed";
    }
    else
    {
    QList<QCPAbstractItem*> selectedItem = ui->widget->selectedItems();
    // 获取鼠标点击的坐标（相对于界面）
       QPoint mousePressPos = event->pos();
        qDebug()<<"鼠标松下";
       // 将界面坐标转换为图表坐标
       double xValue = ui->widget->xAxis->pixelToCoord(mousePressPos.x());
       double yValue = ui->widget->yAxis->pixelToCoord(mousePressPos.y());
    if(!selectedItem.isEmpty())
          {

                 foreach(QCPAbstractItem* item, selectedItem) {
                 if(QCPItemText* textItem = qobject_cast<QCPItemText*>(item))
                 {
                 textItem->position->setCoords(xValue,yValue);
                 QString mark = textItem->text();
                 cpot = mark;
                 map.get_json();
                 map.get_size();
                 map.get_mark();
                 map.get_path();
                 map.Remove_mark(mark);
                 map.add_mark(mark,xValue,yValue);
                 paintmap();
                 qDebug()<<"移动控件中"<<xValue<<yValue;
                 ui->widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));
                 ui->widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));
                 }
         }
    }
    }

}

void MainWindow::on_mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        QList<QCPAbstractItem*> selectedItem = ui->widget->selectedItems();
        // 获取鼠标点击的坐标（相对于界面）
           QPoint mousePressPos = event->pos();

           // 将界面坐标转换为图表坐标
           double xValue = ui->widget->xAxis->pixelToCoord(mousePressPos.x());
           double yValue = ui->widget->yAxis->pixelToCoord(mousePressPos.y());
        if(!selectedItem.isEmpty())
        {
                    ui->widget->selectionRect()->setPen(Qt::NoPen);
                    ui->widget->selectionRect()->setBrush(Qt::NoBrush);
                     foreach(QCPAbstractItem* item, selectedItem) {
                     if(QCPItemText* textItem = qobject_cast<QCPItemText*>(item))
                     {
                     textItem->position->setCoords(xValue,yValue);
                     qDebug()<<"移动控件中"<<xValue<<yValue;
                     }
                     }
        }
         ui->widget->replot();
      }
    // 检测 Ctrl 键是否按下
           if (event->modifiers() & Qt::ControlModifier) {
               qDebug() << "Ctrl key is pressed";
           }



}



void MainWindow::on_pushButton_clicked()
{
      QList<QCPAbstractItem*> selectedItem = ui->widget->selectedItems();
      if(!ui->lineEdit->text().isEmpty())
      {
          QString mark = ui->lineEdit->text();
          map.Remove_mark(mark);
          paintmap();
      }
      else if(!selectedItem.isEmpty())
      {

             foreach(QCPAbstractItem* item, selectedItem) {
             QCPItemText* textItem = qobject_cast<QCPItemText*>(item);
             QString name = textItem->text();
             map.Remove_mark(name);
          }
          paintmap();
      }
      else
      {
          qDebug()<<"没有输入";
      }


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
    ui->listWidget->clear();
    curGraph = ui->widget->addGraph();
    ui->widget->graph(0)->setPen(mypen);
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssSquare, 0.4));
    ui->widget->graph(0)->addData(x,y);
    ui->widget->graph(0)->setAdaptiveSampling(true);
    ui->widget->graph(0)->setSelectable(QCP::stMultipleDataRanges);
    int mark_num=map.Mymarks.size();
    for(int i=0;i<mark_num;i++)
    {
        QCPItemText *textLabel = new QCPItemText(ui->widget);//在QCustomplot中新建文字框
        textLabel->setBrush(QBrush(QColor(0, 188, 212))); // 将背景颜色设置为 RGB (0, 188, 212)
        textLabel->setColor(QColor(255, 255, 255)); // 将文字颜色设置为红色 (RGB: 255, 0, 0)
        textLabel->setPositionAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//文字布局：顶、左对齐
        textLabel->position->setType(QCPItemPosition::ptPlotCoords);//位置类型（当前轴范围的比例为单位/实际坐标为单位）
        textLabel->position->setCoords(map.Mymarks[i].x, map.Mymarks[i].y); //把文字框放在X轴的中间，Y轴的最顶部
        qDebug()<<"站点坐标"<<map.Mymarks[i].x<<map.Mymarks[i].y;
        textLabel->setText(map.Mymarks[i].instanceName);
        textLabel->setFont(QFont("Microsoft YaHei", 10, QFont::Bold)); //字体大小
        textLabel->setPen(QPen(Qt::green,1,Qt::DashDotDotLine)); //边框颜色
        textLabel->setPadding(QMargins(12,12,12,12));//文字距离边框几个像素
        textLabel->setSelectedPen(QPen(Qt::blue, 2)); // 选中时的边框颜色为蓝色，线宽为2像素
        textLabel->setSelectedFont(QFont("Microsoft YaHei", 10, QFont::Bold)); //字体大小
        textLabel->setSelectedColor(QColor(255, 255, 255)); // 将文字颜色设置为红色 (RGB: 255, 0, 0)
        textLabel->setSelectedBrush(QBrush(QColor(0, 200, 250))); // 将背景颜色设置为 RGB (0, 188, 212)
        textLabel->setSelectable(true);
        ui->listWidget->addItem(map.Mymarks[i].instanceName);
        seqNum = map.Mymarks[i].instanceName.mid(2).toInt();
        QString prefix = map.Mymarks[i].instanceName.left(2);

        if(prefix == "LM" && seqNum > potnum)
        {
           potnum = seqNum;
        }

        Site site1 = {map.Mymarks[i].instanceName ,map.Mymarks[i].x , map.Mymarks[i].y,0};
        siteMap[map.Mymarks[i].instanceName] = site1;
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
    map.add_path(mark1,mark2);
    paintmap();
}

void MainWindow::on_pushButton_4_clicked()
{
    QString mark1=ui->lineEdit_7->text();
    QString mark2=ui->lineEdit_8->text();
    map.Remove_path(mark1,mark2);
    paintmap();
}

void MainWindow::on_pushButton_5_clicked()
{         

    if(!ui->lineEdit_9->text().isEmpty()&&!ui->lineEdit_10->text().isEmpty()&&!ui->lineEdit_11->text().isEmpty()&&!ui->lineEdit_12->text().isEmpty())
    {
        double x1=ui->lineEdit_9->text().toDouble();
        double y1=ui->lineEdit_10->text().toDouble();
        double x2=ui->lineEdit_11->text().toDouble();
        double y2=ui->lineEdit_12->text().toDouble();
        map.Remove_obstacles(x1,y1,x2,y2);
        paintmap();
    }
    else if(ui->widget->graph(0)->selected())
    {
        QCPDataSelection selection = ui->widget->graph(0)->selection();
        double minX ;
        double minY ;
        double maxX ;
        double maxY ;
        bool first =true;
        for(int j=0;j<selection.dataRangeCount();j++)
        {
            QCPDataRange dataRange = selection.dataRange(j);

            for(int k=dataRange.begin();k<dataRange.end();k++)
            {
               double x = ui->widget->graph(0)->data()->at(k)->key;
               double y = ui->widget->graph(0)->data()->at(k)->value;
               if(first)
               {
                    minX = x;
                    minY = y;
                    maxX = x;
                    maxY = y;
                    first = false;
               }
               else
               {
                   if (x < minX) {
                       minX = x;
                   }
                   if (y < minY) {
                       minY = y;
                   }
                   if (x > maxX) {
                       maxX = x;
                   }
                   if (y > maxY) {
                       maxY = y;
                   }

               }

            }
        }
        qDebug()<<"minX"<<minX<<"minY"<<minY<<"maxX"<<maxX<<"maxY"<<maxY<<endl;
        map.Remove_obstacles(minX-0.1,minY-0.1,maxX+0.1,maxY+0.1);
        paintmap();
    }
    else
    {
        qDebug()<<"输入为空"<<endl;
    }

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

        map.car_pose();

        QCPItemPixmap *carimage = new QCPItemPixmap(ui->widget);
        carimage->setPixmap(map.carimage);
        carimage->topLeft->setCoords(map.cur_pose.x-0.1,map.cur_pose.y+0.2);
        //qDebug() <<"map.cur_pose.x"<<map.cur_pose.x;

        QString sx = QString::number(map.cur_pose.x);
        QString sy = QString::number(map.cur_pose.y);

        ui->XpositionLable->setText(sx);
        ui->YpositionLable->setText(sy);
        QVector<double> x(map.v_point.size()),y(map.v_point.size());

        for(int i=0;i<map.v_point.size();i++){
            x[i]=map.v_point[i].x+map.cur_pose.x;
            y[i]=map.v_point[i].y+map.cur_pose.y;
            //qDebug() <<"map.v_point[i].x"<<map.v_point[i].x;
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



        ui->widget->replot();
        ui->widget->removeGraph(1);
        ui->widget->removeItem(carimage);
        ui->widget->legend->setVisible(false);


            QCPItemText *AMR1 = new QCPItemText(ui->widget);//在QCustomplot中新建文字框
            AMR1->setBrush(QBrush(QColor(131, 255, 235))); // 将背景颜色设置为 RGB (0, 188, 212)
            AMR1->setColor(QColor(255, 255, 255)); // 将文字颜色设置为红色 (RGB: 255, 0, 0)
            AMR1->setPositionAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//文字布局：顶、左对齐
            AMR1->position->setType(QCPItemPosition::ptPlotCoords);//位置类型（当前轴范围的比例为单位/实际坐标为单位）
            AMR1->setText("AMR1->");
            AMR1->setFont(QFont("Microsoft YaHei", 10, QFont::Bold)); //字体大小
            AMR1->setPen(QPen(Qt::green,1,Qt::DashDotDotLine)); //边框颜色
            AMR1->setPadding(QMargins(12,12,12,12));//文字距离边框几个像素

            //double degrees = radians * 180.0 / M_PI;
            AMR1->position->setCoords(map.cur_pose.x,map.cur_pose.y);
            AMR1->setRotation(0);
            qDebug()<<"执行坐标更新";
            qDebug()<<"1234";


            // 刷新图形
            ui->widget->replot();
            ui->widget->removeGraph(1);
            ui->widget->removeItem(AMR1);
            ui->widget->legend->setVisible(false);


        mtx.unlock();
    }


}



void MainWindow::on_pushButton_7_clicked()
{

    QString x=ui->lineEdit_13->text();
    QString y=ui->lineEdit_14->text();
    QString yaw=ui->lineEdit_15->text();
    QDateTime time = QDateTime::currentDateTime();
    QString time_s =time .toString("hh:mm:ss.zzz");
    QString msg = QString("pose %1 %2 %3 %4").arg(x).arg(y).arg(yaw).arg(time_s);
    QByteArray str= msg.toUtf8();
    emit send_tcp(str,1);
    //cartomap->send_message(str,1);
}

void MainWindow::on_pushButton_8_clicked()
{
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
        QDateTime time = QDateTime::currentDateTime();
        QString time_s =time .toString("hh:mm:ss.zzz");
        //out<< "jz" << " " << "angle" << " " << angle <<" "<<"distance"<<" "<<distance<<" "<<"height"<<" "<<height<<" "<<time_s;
        QString msg = QString("jz angle %1 distance %2 height %3 %4").arg("0").arg("0").arg("0").arg(time_s);
        QByteArray str= msg.toUtf8();
        emit send_tcp(str,1);
    }
    else
    {
        qDebug() <<"输入为空";
    }
}

void MainWindow::on_clamp_clicked()
{
    ui->interaction->setCurrentIndex(2);
    //ui->interaction->setFixedSize(375, 100);
}

void MainWindow::on_nav_clicked()
{
    ui->interaction->setCurrentIndex(3);
    //ui->interaction->setFixedSize(380, 145);
}

void MainWindow::on_ip_button_clicked()
{
    ui->interaction->setCurrentIndex(4);
   // ui->interaction->setFixedSize(375, 400);
}

/*void MainWindow::on_test_clicked()
{
   QList<QCPAbstractItem*> selectedItem = ui->widget->selectedItems(); // 获取已选择的图形项
   foreach (QCPAbstractItem* item, selectedItem) {
      QCPItemText* textItem = qobject_cast<QCPItemText*>(item);
      QString name = textItem->text();
     qDebug()<<"name"<<name;
   }
}*/

void MainWindow::on_map_clicked()
{
    QWidget *new_map = new QWidget();
    new_map->setWindowTitle("地图管理");
    new_map->setWindowIcon(QIcon(":/res/map.png"));
    new_map->setWindowModality(Qt::ApplicationModal);
    QListWidget *list_widget = new QListWidget(new_map);
    /*获得文件路径*/
    QString folderPath = QCoreApplication::applicationDirPath();
    folderPath.chop(4);
    folderPath=folderPath+ "/mapfile";
    qDebug() << folderPath;
    QDir dir(folderPath);
    if (!dir.exists()) {
        qDebug() << "文件夹不存在";
        return;
    }
    QStringList fileList = dir.entryList(QDir::Files);
    qDebug() << "文件夹中的文件列表:";
    foreach (QString file, fileList) {
        QListWidgetItem *map_item = new QListWidgetItem();

        map_item->setIcon(QIcon(":/res/map.png"));
        map_item->setText(file);
        list_widget->addItem(map_item);
        qDebug() << file;
    }
    list_widget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(list_widget,&QListWidget::customContextMenuRequested,[=](const QPoint& pos)
    {

        QMenu *pMenu = new QMenu;
        QAction *pDelete = new QAction("删除地图", pMenu);
        QAction *pUse = new QAction("使用该地图", pMenu);
        QAction *pDownload = new QAction("下载", pMenu);
        QAction *pRename = new QAction("重命名", pMenu);
        QAction *pCollect = new QAction("收藏", pMenu);
        QAction *pCreateDir = new QAction(QIcon(":/map/createdir.png"),"新建文件夹", pMenu);
        QAction *pUpload = new QAction(QIcon(":/map/upload.png"),"上传文件", pMenu);
        QAction *pFlush = new QAction(QIcon(":/map/flush_black.png"),"刷新页面", pMenu);
        /*connect(pDelete,SIGNAL(triggered(bool)),this,SLOT(delRegFile()));
        connect(pDownload,SIGNAL(triggered(bool)),this,SLOT(downloadFile()));
        connect(pRename,SIGNAL(triggered(bool)),this,SLOT(reNameFile()));
        connect(pCreateDir,SIGNAL(triggered(bool)),this,SLOT(createDir()));
        connect(pUpload,SIGNAL(triggered(bool)),this,SLOT(uploadFile()));
        connect(pFlush,SIGNAL(triggered(bool)),this,SLOT(flushFile()));*/
        connect(pUse,&QAction::triggered,this,[=](){
            QString change_Path = QCoreApplication::applicationDirPath();
            change_Path.chop(4);
            change_Path=change_Path+ "/mapfile/"+list_widget->itemAt(pos)->text();
            qDebug() << change_Path;
            this->map.change_map(change_Path);
            this->paintmap();
        });
        //当ListWidgetitem不为空时显示菜单
        if(list_widget->itemAt(/*mapFromGlobal(QCursor::pos())*/pos)!=NULL)
        {
            pMenu->addAction(pUse);
            pMenu->addAction(pDelete);
            pMenu->addAction(pDownload);
            pMenu->addAction(pRename);
            pMenu->addAction(pCollect);

        }
        else
        {
            pMenu->addAction(pCreateDir);
            pMenu->addSeparator(); //添加分隔符
            pMenu->addAction(pUpload);
            pMenu->addSeparator();
            pMenu->addAction(pFlush);
        }
        //在鼠标位置显示菜单
        pMenu->exec(QCursor::pos());

        delete pMenu;
    });


    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(list_widget);
    new_map->setLayout(layout);
    list_widget->setFixedWidth(new_map->width());
    list_widget->setFixedHeight(new_map->height());
    list_widget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    new_map->setFixedWidth(new_map->width()+25);
    new_map->setFixedHeight(new_map->height()+25);
    new_map->show();
}

void MainWindow::on_nav_stop_clicked()
{
    QDateTime time = QDateTime::currentDateTime();
    QString time_s =time .toString("hh:mm:ss.zzz");
    QString msg = QString("pause %1").arg(time_s);
    QByteArray str= msg.toUtf8();
    emit send_tcp(str,1);
    //cartomap->send_message(str,1);

}

void MainWindow::on_nav_start_clicked()
{

    QDateTime time = QDateTime::currentDateTime();
    QString time_s =time .toString("hh:mm:ss.zzz");
    QString msg = QString("start %1").arg(time_s);
    QByteArray str= msg.toUtf8();
    emit send_tcp(str,1);

}

void MainWindow::on_qr_code_clicked()
{

    QDateTime time = QDateTime::currentDateTime();
    QString time_s =time .toString("hh:mm:ss.zzz");
    QString msg = QString("camera %1 %2").arg("1").arg(time_s);
    QByteArray str= msg.toUtf8();
   emit send_tcp(str,1);

}

void MainWindow::on_setNewItem_clicked()
{
    qDebug()<<"现存站点数："<<potnum;
    QString Potstr = "LM" + QString::number(++potnum);
    int x =0; // Generates numbers in the range [7, 13)

       // Generate a random number between 10 and 15
    int y = 0; // Generates numbers in the range [10, 16)
    map.get_json();
    map.get_size();
    map.get_mark();
    map.get_path();
    map.add_mark(Potstr,x,y);
    paintmap();
}

void MainWindow::on_NavcontinueButton_clicked()
{
    QDateTime time = QDateTime::currentDateTime();
    QString time_s =time .toString("hh:mm:ss.zzz");
    QString msg = QString("start %1").arg(time_s);
    QByteArray str= msg.toUtf8();
    cartomap->send_message(str,1);
}

void MainWindow::on_NavstopButton_clicked()
{
    QDateTime time = QDateTime::currentDateTime();
    QString time_s =time .toString("hh:mm:ss.zzz");
    QString msg = QString("pause %1").arg(time_s);
    QByteArray str= msg.toUtf8();
    //cartomap->send_message(str,1);
}

void MainWindow::on_XposEdit_textChanged(const QString &arg1)
{




}

void MainWindow::on_PositionButton_clicked()
{
    qDebug()<<"SS"<<cpot;
    if( cpot != NULL)
    {
                float x = ui->XposEdit->text().toFloat();
                float y = ui->YposEdit->text().toFloat();
                 map.get_json();
                 map.get_size();
                 map.get_mark();
                 map.get_path();
                 map.Remove_mark(cpot);
                 map.add_mark(cpot,x,y);
                 paintmap();
                 qDebug()<<"更改坐标值："<<cpot<<y;
    }
}

void MainWindow::on_LineButton_clicked()
{

}

void MainWindow::on_SDeIeteButton_clicked()
{
    QList<QCPAbstractItem*> selectedItem = ui->widget->selectedItems();

    if(!selectedItem.isEmpty())
    {

           foreach(QCPAbstractItem* item, selectedItem) {
           QCPItemText* textItem = qobject_cast<QCPItemText*>(item);
           QString name = textItem->text();
           map.Remove_mark(name);
        }
        paintmap();
    }
    else
    {
        qDebug()<<"没有输入";
    }
}


void MainWindow::on_NewIPButton_clicked()
{
   /*QList<QCPAbstractItem*> selectedItem = ui->widget->selectedItems(); // 获取已选择的图形项
   foreach (QCPAbstractItem* item, selectedItem) {
      QCPItemText* textItem = qobject_cast<QCPItemText*>(item);
      QString name = textItem->text();
     qDebug()<<"name"<<name;
   }*/
}




void MainWindow::on_listWidget_itemPressed(QListWidgetItem *item)
{
    qDebug()<<"item"<<item->text();

    QMenu *pMenu = new QMenu;
    QAction *Nav = new QAction("导航至该站点", pMenu);
    pMenu->addAction(Nav);

    connect(Nav,&QAction::triggered,this,[=](){
       qDebug()<<"导航成功"<<item->text();
       QString Dp = item->text();

         if (siteMap.find(Dp) != siteMap.end()) {
             Site targetSite = siteMap[Dp];
             qDebug() << "Site Name: " << targetSite.name << ", X: " << targetSite.x << ", Y: " << targetSite.y;
             QDateTime time = QDateTime::currentDateTime();
             QString time_s =time .toString("hh:mm:ss.zzz");
             QString msg = QString("pose %1 %2 %3 %4").arg(targetSite.x).arg(targetSite.y).arg(targetSite.yaw).arg(time_s);
             QByteArray str= msg.toUtf8();
             emit send_tcp(str,1);

         } else {
            // qDebug() << "Site with name " << targetSiteName << " not found." << std::endl;
         }


    });

    //在鼠标位置显示菜单
    pMenu->exec(QCursor::pos());
    delete pMenu;
}
