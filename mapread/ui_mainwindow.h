/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QCustomPlot *widget;
    QStackedWidget *interaction;
    QWidget *page;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QPushButton *pushButton_4;
    QWidget *page_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_10;
    QLineEdit *lineEdit_11;
    QLineEdit *lineEdit_12;
    QPushButton *pushButton_5;
    QWidget *page_3;
    QLineEdit *clamp_angle;
    QLineEdit *clamp_distance;
    QLineEdit *clamp_height;
    QPushButton *clamp_control;
    QWidget *page_4;
    QPushButton *pushButton_7;
    QLineEdit *lineEdit_13;
    QLineEdit *lineEdit_14;
    QLineEdit *lineEdit_15;
    QLineEdit *lineEdit_16;
    QLineEdit *lineEdit_17;
    QLineEdit *lineEdit_18;
    QLineEdit *lineEdit_19;
    QPushButton *pushButton_8;
    QWidget *page_5;
    QLineEdit *IP;
    QLineEdit *PORT;
    QPushButton *connect;
    QPushButton *test;
    QGroupBox *groupBox;
    QPushButton *move_map;
    QPushButton *add;
    QPushButton *del;
    QPushButton *clamp;
    QPushButton *nav;
    QPushButton *ip_button;
    QWidget *tab_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1767, 1294);
        QIcon icon;
        icon.addFile(QStringLiteral(":/robot.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setAutoFillBackground(true);
        tabWidget->setStyleSheet(QString::fromUtf8("QTabBar::tab{width:200}\n"
"QTabBar::tab{height:40}\n"
"QTabBar::tab{font: 75 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\"}\n"
"QTabBar::tab:selected{font: 14pt \"\345\215\216\346\226\207\350\241\214\346\245\267\";color:#55aaff}\n"
"\n"
"\n"
"\n"
"\n"
""));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setIconSize(QSize(16, 16));
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        widget = new QCustomPlot(tab);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 1721, 1101));
        widget->setStyleSheet(QStringLiteral(""));
        interaction = new QStackedWidget(widget);
        interaction->setObjectName(QStringLiteral("interaction"));
        interaction->setGeometry(QRect(1320, 10, 391, 141));
        interaction->setStyleSheet(QString::fromUtf8("QStackedWidget{\n"
"border-radius:12px;\n"
"border: 2px solid  rgb(118, 238, 176);\n"
"background-color: rgb(255, 255, 255);\n"
"}\n"
"QPushButton{\n"
"color: rgb(255, 255, 255);\n"
"font: 75 12pt \"\347\255\211\347\272\277\";\n"
"background-color:  rgb(118, 238, 176);\n"
"border-radius:8px !important;\n"
"}\n"
"QLineEdit{\n"
"border: 1px solid rgb(118, 238, 176);\n"
"border-radius: 5px !important;\n"
"background-color: rgb(255, 255, 255);\n"
"}\n"
"QLineEdit::placeholder {\n"
"    color: red;\n"
"    font-style: italic;\n"
"}\n"
"\n"
"\n"
"\n"
"\n"
""));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        lineEdit = new QLineEdit(page);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(30, 10, 131, 31));
        pushButton = new QPushButton(page);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(190, 10, 111, 31));
        lineEdit_7 = new QLineEdit(page);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(30, 50, 61, 31));
        lineEdit_8 = new QLineEdit(page);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(100, 50, 61, 31));
        pushButton_4 = new QPushButton(page);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(190, 50, 111, 31));
        interaction->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        verticalLayout = new QVBoxLayout(page_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit_2 = new QLineEdit(page_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy);
        lineEdit_2->setStyleSheet(QStringLiteral(""));
        lineEdit_2->setCursorMoveStyle(Qt::LogicalMoveStyle);

        horizontalLayout->addWidget(lineEdit_2);

        lineEdit_3 = new QLineEdit(page_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        sizePolicy.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy);
        lineEdit_3->setStyleSheet(QLatin1String("placeholderText{\n"
"fontFamily: 12 italic 17pt \"Cascadia Code ExtraLight\";\n"
"background-color: rgb(170, 170, 255);\n"
"}"));

        horizontalLayout->addWidget(lineEdit_3);

        lineEdit_4 = new QLineEdit(page_2);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        sizePolicy.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEdit_4);

        pushButton_2 = new QPushButton(page_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEdit_5 = new QLineEdit(page_2);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        sizePolicy.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy);
        lineEdit_5->setToolTipDuration(-5);

        horizontalLayout_2->addWidget(lineEdit_5);

        lineEdit_6 = new QLineEdit(page_2);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        sizePolicy.setHeightForWidth(lineEdit_6->sizePolicy().hasHeightForWidth());
        lineEdit_6->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lineEdit_6);

        pushButton_3 = new QPushButton(page_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(pushButton_3);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lineEdit_9 = new QLineEdit(page_2);
        lineEdit_9->setObjectName(QStringLiteral("lineEdit_9"));
        sizePolicy.setHeightForWidth(lineEdit_9->sizePolicy().hasHeightForWidth());
        lineEdit_9->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(lineEdit_9);

        lineEdit_10 = new QLineEdit(page_2);
        lineEdit_10->setObjectName(QStringLiteral("lineEdit_10"));
        sizePolicy.setHeightForWidth(lineEdit_10->sizePolicy().hasHeightForWidth());
        lineEdit_10->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(lineEdit_10);

        lineEdit_11 = new QLineEdit(page_2);
        lineEdit_11->setObjectName(QStringLiteral("lineEdit_11"));
        sizePolicy.setHeightForWidth(lineEdit_11->sizePolicy().hasHeightForWidth());
        lineEdit_11->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(lineEdit_11);

        lineEdit_12 = new QLineEdit(page_2);
        lineEdit_12->setObjectName(QStringLiteral("lineEdit_12"));
        sizePolicy.setHeightForWidth(lineEdit_12->sizePolicy().hasHeightForWidth());
        lineEdit_12->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(lineEdit_12);

        pushButton_5 = new QPushButton(page_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        sizePolicy1.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(pushButton_5);


        verticalLayout->addLayout(horizontalLayout_3);

        interaction->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        clamp_angle = new QLineEdit(page_3);
        clamp_angle->setObjectName(QStringLiteral("clamp_angle"));
        clamp_angle->setGeometry(QRect(20, 20, 61, 41));
        clamp_distance = new QLineEdit(page_3);
        clamp_distance->setObjectName(QStringLiteral("clamp_distance"));
        clamp_distance->setGeometry(QRect(100, 20, 71, 41));
        clamp_height = new QLineEdit(page_3);
        clamp_height->setObjectName(QStringLiteral("clamp_height"));
        clamp_height->setGeometry(QRect(190, 20, 71, 41));
        clamp_control = new QPushButton(page_3);
        clamp_control->setObjectName(QStringLiteral("clamp_control"));
        clamp_control->setGeometry(QRect(280, 20, 80, 41));
        interaction->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        pushButton_7 = new QPushButton(page_4);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(260, 10, 101, 31));
        lineEdit_13 = new QLineEdit(page_4);
        lineEdit_13->setObjectName(QStringLiteral("lineEdit_13"));
        lineEdit_13->setGeometry(QRect(30, 10, 51, 31));
        lineEdit_14 = new QLineEdit(page_4);
        lineEdit_14->setObjectName(QStringLiteral("lineEdit_14"));
        lineEdit_14->setGeometry(QRect(110, 10, 51, 31));
        lineEdit_15 = new QLineEdit(page_4);
        lineEdit_15->setObjectName(QStringLiteral("lineEdit_15"));
        lineEdit_15->setGeometry(QRect(190, 10, 51, 31));
        lineEdit_16 = new QLineEdit(page_4);
        lineEdit_16->setObjectName(QStringLiteral("lineEdit_16"));
        lineEdit_16->setGeometry(QRect(10, 50, 51, 31));
        lineEdit_17 = new QLineEdit(page_4);
        lineEdit_17->setObjectName(QStringLiteral("lineEdit_17"));
        lineEdit_17->setGeometry(QRect(70, 50, 51, 31));
        lineEdit_18 = new QLineEdit(page_4);
        lineEdit_18->setObjectName(QStringLiteral("lineEdit_18"));
        lineEdit_18->setGeometry(QRect(130, 50, 51, 31));
        lineEdit_19 = new QLineEdit(page_4);
        lineEdit_19->setObjectName(QStringLiteral("lineEdit_19"));
        lineEdit_19->setGeometry(QRect(190, 50, 51, 31));
        pushButton_8 = new QPushButton(page_4);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(260, 50, 101, 31));
        interaction->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        IP = new QLineEdit(page_5);
        IP->setObjectName(QStringLiteral("IP"));
        IP->setGeometry(QRect(20, 10, 191, 31));
        PORT = new QLineEdit(page_5);
        PORT->setObjectName(QStringLiteral("PORT"));
        PORT->setGeometry(QRect(20, 50, 191, 31));
        connect = new QPushButton(page_5);
        connect->setObjectName(QStringLiteral("connect"));
        connect->setGeometry(QRect(230, 30, 111, 31));
        interaction->addWidget(page_5);
        test = new QPushButton(widget);
        test->setObjectName(QStringLiteral("test"));
        test->setGeometry(QRect(1570, 820, 111, 41));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 1090, 1721, 81));
        groupBox->setStyleSheet(QLatin1String("QGroupBox\n"
"{\n"
"border: 2px solid green;\n"
"border-radius:8px;\n"
"margin-top:2ex;\n"
"font:bold 22px \"Segoe Print\";\n"
"}\n"
"QGroupBox::title\n"
"{\n"
"subcontrol-origin:margin;\n"
"subcontrol-position:top center;\n"
"padding:0 3px;\n"
"}\n"
"QPushButton{\n"
"background-color:transparent;\n"
"color:white;\n"
"border-radus:10px;\n"
"border-style:outset;\n"
"}\n"
"QPushButton:hover {\n"
"background-color: rgb(100, 100, 100);\n"
"}\n"
"\n"
""));
        move_map = new QPushButton(groupBox);
        move_map->setObjectName(QStringLiteral("move_map"));
        move_map->setGeometry(QRect(830, 40, 41, 29));
        move_map->setMaximumSize(QSize(91, 16777215));
        move_map->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/mapmove.png"), QSize(), QIcon::Normal, QIcon::Off);
        move_map->setIcon(icon1);
        move_map->setIconSize(QSize(29, 29));
        move_map->setAutoDefault(false);
        move_map->setFlat(false);
        add = new QPushButton(groupBox);
        add->setObjectName(QStringLiteral("add"));
        add->setGeometry(QRect(890, 40, 41, 31));
        add->setStyleSheet(QStringLiteral(""));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        add->setIcon(icon2);
        add->setIconSize(QSize(32, 31));
        add->setCheckable(false);
        add->setAutoExclusive(false);
        del = new QPushButton(groupBox);
        del->setObjectName(QStringLiteral("del"));
        del->setGeometry(QRect(950, 40, 41, 31));
        del->setStyleSheet(QStringLiteral(""));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/res/del.png"), QSize(), QIcon::Normal, QIcon::Off);
        del->setIcon(icon3);
        del->setIconSize(QSize(38, 38));
        clamp = new QPushButton(groupBox);
        clamp->setObjectName(QStringLiteral("clamp"));
        clamp->setGeometry(QRect(1010, 39, 41, 31));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/res/clamp.png"), QSize(), QIcon::Normal, QIcon::Off);
        clamp->setIcon(icon4);
        clamp->setIconSize(QSize(40, 40));
        nav = new QPushButton(groupBox);
        nav->setObjectName(QStringLiteral("nav"));
        nav->setGeometry(QRect(1070, 39, 41, 31));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/res/nav.png"), QSize(), QIcon::Normal, QIcon::Off);
        nav->setIcon(icon5);
        nav->setIconSize(QSize(40, 40));
        ip_button = new QPushButton(groupBox);
        ip_button->setObjectName(QStringLiteral("ip_button"));
        ip_button->setGeometry(QRect(770, 40, 41, 31));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/res/ip.png"), QSize(), QIcon::Normal, QIcon::Off);
        ip_button->setIcon(icon6);
        ip_button->setIconSize(QSize(38, 38));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1767, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        interaction->setCurrentIndex(0);
        move_map->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "robotshop", Q_NULLPTR));
        lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "markname", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\347\253\231\347\202\271", Q_NULLPTR));
        lineEdit_7->setPlaceholderText(QApplication::translate("MainWindow", "markstart", Q_NULLPTR));
        lineEdit_8->setPlaceholderText(QApplication::translate("MainWindow", "markend", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\350\267\257\345\276\204", Q_NULLPTR));
        lineEdit_2->setText(QString());
        lineEdit_2->setPlaceholderText(QApplication::translate("MainWindow", "name", Q_NULLPTR));
        lineEdit_3->setText(QString());
        lineEdit_3->setPlaceholderText(QApplication::translate("MainWindow", "x", Q_NULLPTR));
        lineEdit_4->setText(QString());
        lineEdit_4->setPlaceholderText(QApplication::translate("MainWindow", "y", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\347\253\231\347\202\271", Q_NULLPTR));
        lineEdit_5->setPlaceholderText(QApplication::translate("MainWindow", "markstart", Q_NULLPTR));
        lineEdit_6->setPlaceholderText(QApplication::translate("MainWindow", "markend", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\350\267\257\345\276\204", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\351\232\234\347\242\215\347\211\251", Q_NULLPTR));
        clamp_control->setText(QApplication::translate("MainWindow", "\346\212\223\345\217\226", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("MainWindow", "\345\257\274\350\210\252", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("MainWindow", "\347\253\231\347\202\271\345\257\274\350\210\252", Q_NULLPTR));
        IP->setText(QApplication::translate("MainWindow", "127.0.0.1", Q_NULLPTR));
        IP->setPlaceholderText(QApplication::translate("MainWindow", "IP\345\234\260\345\235\200", Q_NULLPTR));
        PORT->setText(QApplication::translate("MainWindow", "8888", Q_NULLPTR));
        PORT->setPlaceholderText(QApplication::translate("MainWindow", "\347\253\257\345\217\243\345\217\267", Q_NULLPTR));
        connect->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245", Q_NULLPTR));
        test->setText(QApplication::translate("MainWindow", "test", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Map toolbox", Q_NULLPTR));
        move_map->setText(QString());
        add->setText(QString());
        del->setText(QString());
        clamp->setText(QString());
        nav->setText(QString());
        ip_button->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "   \345\234\260\345\233\276\344\270\216\346\216\247\345\210\266   ", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\346\250\241\345\236\213\346\226\207\344\273\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
