#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include "api/myapp.h"
#include <QStringListModel>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdlib>
#include <cstdio>
#include <QFileDialog>
#include <QStringList>
#include <QtGui>
#include <QMouseEvent>
#include "showimage.h"
#include <QItemSelectionModel>
#include <QFile>
#include <QTextStream>
#include <QRegExp>
#include <QMenuBar>
#include <QMessageBox>


QStringList::Iterator j;
static int k = 0;
QString file1[1000] = {};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(myApp::SoftTitle);
    QTextCodec *codec = QTextCodec::codecForName("utf-8");

    ui->labWelcom->setText(QString(codec->toUnicode("欢迎使用%1")).arg(myApp::SoftTitle));

    ui->labLive->setText(QString(codec->toUnicode("已运行:0天0时0分0秒")));

    ui->labTime->setText(QDateTime::currentDateTime().toString(codec->toUnicode("当前时间:yyyy年MM月dd日 dddd HH:mm:ss")));

    timerDate=new QTimer(this);
    timerDate->setInterval(1000);
    connect(timerDate,SIGNAL(timeout()),this,SLOT(ShowDateTime()));
    timerDate->start();


    ///数据处理子进程
    cmdexeccode = new QProcess();
    cmdcpu = new QProcess();
    cmdsysio = new QProcess();
    cmdmemcheck = new QProcess();
    cmdgetpath = new QProcess();
    cmdsystime =new QProcess();
    cmdmem =new QProcess();
    cmdcopy =new QProcess();

    slider = new QSlider(Qt::Horizontal,this);//缩放滑动条


    label = new QLabel;

    showImage = new ShowImage();
    showImage->filename = tr("./Static_detection/getpath/control.dot.png");
    showImage->init_path(showImage->filename);

    connect(showImage, SIGNAL(turn2default(int)),//缩放比例
            slider, SLOT(setValue(int)));

    connect(slider,SIGNAL(valueChanged(int)),
            this,SLOT(changelabel(int)));
    connect(slider,SIGNAL(valueChanged(int)),
            this,SLOT(scalethepix(int)));

    QHBoxLayout *labelLayout = new QHBoxLayout;

    labelLayout->addWidget(slider);
    labelLayout->addWidget(label);//label显示百分之几
    label->setBuddy(slider);

    //设置纵向伸展因子
    ui->windowLayout->setColumnStretch(0,1);
    ui->windowLayout->setColumnStretch(1,2);
    ui->windowLayout->setColumnStretch(2,2);
    ui->windowLayout->setColumnStretch(3,2);
    ui->windowLayout->setColumnStretch(4,2);

    ui->windowLayout->addWidget(showImage, 0, 0, 1, 9);//放置在0行0列位置
    ui->windowLayout->setRowMinimumHeight(1,6);//在第1行设最小行距，单位为像素
    ui->windowLayout->addLayout(labelLayout, 2, 4, Qt::AlignRight);

    setLayout(ui->windowLayout);

    slider->setRange(0,1000);
    slider->setValue(100);


    label1 = new QLabel;
    slider1 = new QSlider(Qt::Horizontal,this);//缩放滑动条
    showImage1 = new ShowImage();
    showImage1->filename = tr("./test_report/tracemap_file");
    showImage1->init_path(showImage1->filename);

    connect(showImage1, SIGNAL(turn2default(int)),//缩放比例
            slider1, SLOT(setValue(int)));

    connect(slider1,SIGNAL(valueChanged(int)),
            this,SLOT(changelabel1(int)));
    connect(slider1,SIGNAL(valueChanged(int)),
            this,SLOT(scalethepix1(int)));


    QHBoxLayout *labelLayout1 = new QHBoxLayout;

    labelLayout1->addWidget(slider1);
    labelLayout1->addWidget(label1);//label显示百分之几
    label1->setBuddy(slider1);

    ui->windowLayout_2->setColumnStretch(0,1);
    ui->windowLayout_2->setColumnStretch(1,2);
    ui->windowLayout_2->setColumnStretch(2,2);
    ui->windowLayout_2->setColumnStretch(3,2);
    ui->windowLayout_2->setColumnStretch(4,2);

    ui->windowLayout_2->addWidget(showImage1, 0, 0, 1, 9);//放置在0行0列位置
    ui->windowLayout_2->setRowMinimumHeight(1,6);//在第1行设最小行距，单位为像素
    ui->windowLayout_2->addLayout(labelLayout1, 2, 4, Qt::AlignRight);


    setLayout(ui->windowLayout_2);

    slider1->setRange(0,1000);
    slider1->setValue(100);

    system("");

    setupModel();

    ui->tableWidget_case->setRowCount(100);


    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_case->setSelectionModel(selectionModel);

    ui->tableWidget_route_2->setRowCount(100);
    ui->tableWidget_route_2->setColumnCount(2);
    ui->tableWidget_route_2->setColumnWidth(0,1000);
    ui->tableWidget_route_2->setColumnWidth(1,1);



    QItemSelectionModel *selectionModel1=new QItemSelectionModel(model);
    ui->tableWidget_route_2->setSelectionModel(selectionModel1);

    /**信号槽连接函数（start）**/

    timecpu = new QTimer;
    connect(timecpu, SIGNAL(timeout()), this, SLOT(cpushowWork()));

    timecases = new QTimer;
    connect(timecases, SIGNAL(timeout()), this, SLOT(casesshowWork()));

    timemem = new QTimer;
    connect(timemem, SIGNAL(timeout()), this, SLOT(memshowWork()));

    manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(cpuReplyFinished(QNetworkReply*)));

    managercases = new QNetworkAccessManager(this);
    connect(managercases,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(casesReplyFinished(QNetworkReply*)));

    managerfile = new QNetworkAccessManager(this);
    connect(managerfile,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(filereplyFinished(QNetworkReply*)));

    managersysio = new QNetworkAccessManager(this);
    connect(managersysio,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(sysioReplyFinished(QNetworkReply*)));

    timesysio = new QTimer;
    connect(timesysio, SIGNAL(timeout()), this, SLOT(sysioshowWork()));

    managerresadd = new QNetworkAccessManager(this);
    connect(managerresadd,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(resaddReplyFinished(QNetworkReply*)));

    managerrestime = new QNetworkAccessManager(this);
    connect(managerrestime,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(restimeReplyFinished(QNetworkReply*)));

    managermemcheck = new QNetworkAccessManager(this);
    connect(managermemcheck,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(memcheckReplyFinished(QNetworkReply*)));

    managermemcheckres = new QNetworkAccessManager(this);
    connect(managermemcheckres,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(memcheckresReplyFinished(QNetworkReply*)));

    managercover = new QNetworkAccessManager(this);
    connect(managercover,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(coverresReplyFinished(QNetworkReply*)));

    /**信号槽连接函数（end）**/
    initData();


}

MainWindow::~MainWindow()
{
    delete ui;
    delete showImage;
    delete showImage1;

}

int day=0;
int hour=0;
int minute=0;
int second=0;
/**
 * 显示系统运行时间信息
 **/
void MainWindow::ShowDateTime()
{
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    second++;
    if (second==60){minute++;second=0;}
    if (minute==60){hour++;minute=0;}
    if (hour==24){day++;hour=0;}
    ui->labLive->setText(QString(codec->toUnicode("已运行:%1天%2时%3分%4秒")).arg(day).arg(hour).arg(minute).arg(second));
    ui->labTime->setText(QDateTime::currentDateTime().toString(codec->toUnicode("当前时间:yyyy年MM月dd日 dddd HH:mm:ss")));

}

/**
 * 自定义鼠标事件 paintEvent
 **/
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(m_pixmapBg.rect(), m_pixmapBg);
}

/**
 * 自定义鼠标事件 mouseMoveEvent
 **/
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    this->move(e->globalPos() - m_pointStart);
}

/**
 * 自定义鼠标事件 mousePressEvent
 **/
void MainWindow::mousePressEvent(QMouseEvent *e)
{
    m_pointPress = e->globalPos();
    m_pointStart = m_pointPress - this->pos();

}

/**
 * 自定义鼠标事件 changeEvent
 **/
void MainWindow::changeEvent(QEvent* event){
    if(event->type()==QEvent::WindowStateChange){
        if(windowState() & Qt::WindowMinimized){
            QTimer::singleShot(0, this, SLOT(showMinimized()));
            this->show();
        }
        QMainWindow::changeEvent(event);
    }
}

/**
 *	设置窗口状态
 **/
void MainWindow::setNomalStyle()
{
    QFile styleSheet(":/res/qss/style_ebts.qss");
    if (!styleSheet.open(QIODevice::ReadOnly))
    {
        qWarning("Can't open the style sheet file.");
        return;
    }
    qApp->setStyleSheet(styleSheet.readAll());
}

/**
 *	初始化信息，加载界面
 **/
void MainWindow::initData()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    QTextCodec *codec = QTextCodec::codecForName("utf-8");

    m_menu = new QMenu();
    m_menu->addAction(codec->toUnicode("软件信息"));
    m_menu->addAction(codec->toUnicode("常用帮助"));
    m_menu->addSeparator();
    m_menu->addAction(codec->toUnicode("关于我们"));
    m_AactionAboutQt = new QAction(tr("&About Qt"), this);
    connect(m_AactionAboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    m_menu->addAction(m_AactionAboutQt);

    ///背景加载;
    m_pixmapBg.load(":/res/image/frame.png");

    ///主界面按钮布局
    m_vecBtn.push_back(ui->pushButton);
    m_vecBtn.push_back(ui->pushButton_2);
    m_vecBtn.push_back(ui->pushButton_3);
    m_vecBtn.push_back(ui->pushButton_4);
    m_vecBtn.push_back(ui->pushButton_5);
    m_vecBtn.push_back(ui->pushButton_6);
    m_vecBtn.push_back(ui->pushButton_7);

    ///界面2_1按钮布局
    m_vecBtn2_1.push_back(ui->pushButton_10);
    m_vecBtn2_1.push_back(ui->pushButton_11);
    m_vecBtn2_1.push_back(ui->pushButton_12);
    m_vecBtn2_1.push_back(ui->pushButton_13);
    m_vecBtn2_1.push_back(ui->pushButton_14);

    ///界面静态检测按钮布局
    m_vecBtn2_1_bak.push_back(ui->pushButton_15);
    m_vecBtn2_1_bak.push_back(ui->pushButton_16);
    m_vecBtn2_1_bak.push_back(ui->pushButton_17);
    m_vecBtn2_1_bak.push_back(ui->pushButton_18);
    m_vecBtn2_1_bak.push_back(ui->pushButton_19);

    ///界面3按钮布局
    m_vecBtn3.push_back(ui->pushButtoncpu);
    m_vecBtn3.push_back(ui->pushButtonsysio);
    m_vecBtn3.push_back(ui->pushButtonrealtime);

    ///界面3按钮布局
    m_vecBtn3_bak.push_back(ui->pushButtoncpu_2);
    m_vecBtn3_bak.push_back(ui->pushButtonsysio_2);
    m_vecBtn3_bak.push_back(ui->pushButtonrealtime_2);

    ///界面4按钮布局
    m_vecBtn4.push_back(ui->pushButtonstack);
    m_vecBtn4.push_back(ui->pushButtonmem);
    m_vecBtn4.push_back(ui->pushButtonundef);
    m_vecBtn4.push_back(ui->pushButtonint);
    m_vecBtn4.push_back(ui->pushButtonred);

    ///界面4按钮布局
    m_vecBtn4_bak.push_back(ui->pushButtonstack_2);
    m_vecBtn4_bak.push_back(ui->pushButtonmem_2);
    m_vecBtn4_bak.push_back(ui->pushButtonundef_2);
    m_vecBtn4_bak.push_back(ui->pushButtonint_2);
    m_vecBtn4_bak.push_back(ui->pushButtonred_2);



    for (int i = 0; i != m_vecBtn.size(); ++i)
    {
        ///功能选择键只有一个被选中;
        m_vecBtn[i]->setCheckable(true);
        m_vecBtn[i]->setAutoExclusive(true);
    }


    for (int i = 0; i != m_vecBtn2_1.size(); ++i)
    {
        ///功能选择键只有一个被选中;
        m_vecBtn2_1[i]->setCheckable(true);
        m_vecBtn2_1[i]->setAutoExclusive(true);
    }

    for (int i = 0; i != m_vecBtn2_1_bak.size(); ++i)
    {
        ///功能选择键只有一个被选中;
        m_vecBtn2_1_bak[i]->setCheckable(true);
        m_vecBtn2_1_bak[i]->setAutoExclusive(true);
    }

    for (int i = 0; i != m_vecBtn3.size(); ++i)
    {
        ///功能选择键只有一个被选中;
        m_vecBtn3[i]->setCheckable(true);
        m_vecBtn3[i]->setAutoExclusive(true);
    }

    for (int i = 0; i != m_vecBtn3_bak.size(); ++i)
    {
        ///功能选择键只有一个被选中;
        m_vecBtn3_bak[i]->setCheckable(true);
        m_vecBtn3_bak[i]->setAutoExclusive(true);
    }

    for (int i = 0; i != m_vecBtn4.size(); ++i)
    {
        ///功能选择键只有一个被选中;
        m_vecBtn4[i]->setCheckable(true);
        m_vecBtn4[i]->setAutoExclusive(true);
    }


    for (int i = 0; i != m_vecBtn4_bak.size(); ++i)
    {
        ///功能选择键只有一个被选中;
        m_vecBtn4_bak[i]->setCheckable(true);
        m_vecBtn4_bak[i]->setAutoExclusive(true);
    }

    setNomalStyle();
}



void MainWindow::on_menuBtn_clicked()
{
    m_menu->exec(this->mapToGlobal(QPoint(700, 20)));
}


void MainWindow::on_pushButton_clicked()
{
    setCurrentWidget();
}

/**
 * @brief 动态检测模块槽函数
 */
void MainWindow::on_pushButton_4_clicked()
{
    setCurrentWidget();
}

/**
 * @brief 性能检测模块槽函数
 */
void MainWindow::on_pushButton_3_clicked()
{
    setCurrentWidget();
}

/**
 * @brief 静态分析模块处理函数
 */
void MainWindow::on_pushButton_2_clicked()
{
    setCurrentWidget();
    cmdexeccode->start("sh execcode.sh");
    qApp->processEvents();
    setupModel();

    ui->tableWidget_2->setRowCount(100);
    ui->tableWidget_2->setColumnCount(4);
    ui->tableWidget_2->setColumnWidth(0,150);
    ui->tableWidget_2->setColumnWidth(1,150);
    ui->tableWidget_2->setColumnWidth(2,150);
    ui->tableWidget_2->setColumnWidth(3,150);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);

    ui->tableWidget_2->setSelectionModel(selectionModel);

    ui->tableWidget_route->setRowCount(300);
    ui->tableWidget_route->setColumnCount(2);
    ui->tableWidget_route->setColumnWidth(0,3500);
    ui->tableWidget_route->setColumnWidth(1,1);

    QItemSelectionModel *selectionModel1=new QItemSelectionModel(model);
    ui->tableWidget_route->setSelectionModel(selectionModel1);

    system("");

    ///提取敏感区域检测信息
    file_full = tr("./Static_detection/Sensitive_Area_File");
    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    QTextStream stream(&file);
    QString line;

    model->removeRows(0,model->rowCount(QModelIndex()),QModelIndex());
    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            line.replace(QRegExp(":"), "");
            line.replace(QRegExp("                  "), "    ");
            QStringList pieces=line.split(" ",QString::SkipEmptyParts);
            ui->tableWidget_2->setItem( row, 0, new QTableWidgetItem( pieces.value(0)));
            ui->tableWidget_2->setItem( row, 1, new QTableWidgetItem( pieces.value(1)));
            ui->tableWidget_2->setItem( row, 2, new QTableWidgetItem( pieces.value(2)));
            ui->tableWidget_2->setItem( row, 3, new QTableWidgetItem( pieces.value(3)));
            row++;
        }
    }while (!line.isEmpty());
    file.close();

    file_full = tr("./Static_detection/getpath/get_path_File");
    QFile filepath(file_full);
    if (!filepath.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }

    QTextStream streampath(&filepath);
    QString linepath;

    int rowpath = 0;
    do
    {
        linepath = streampath.readLine();
        if (!linepath.isEmpty())
        {
            ui->tableWidget_route->setItem( rowpath, 0, new QTableWidgetItem(linepath));
            row1++;
        }
    }while (!linepath.isEmpty());
    update();
    filepath.close();



}

/**
 * @brief 帮助信息模块槽函数
 */
void MainWindow::on_pushButton_6_clicked()
{
    setCurrentWidget();
}

/**
 * @brief 用力生成模块槽函数
 */
void MainWindow::on_pushButton_5_clicked()
{
    setCurrentWidget();
}

void MainWindow::setCurrentWidget()
{
    for (int i = 0; i != m_vecBtn.size(); ++i)
    {
        if ( m_vecBtn[i]->isChecked() )
        {
            ui->stackedWidget->setCurrentIndex(i);
        }
    }
}

///界面2按钮与widget布局
void MainWindow::setCurrentWidget2()
{
    for (int i = 0; i != m_vecBtn2.size(); ++i)
    {
        if ( m_vecBtn2[i]->isChecked() )
        {
            ui->stackedWidget_2->setCurrentIndex(i);
        }
    }
}

///界面2_1按钮与widget布局
void MainWindow::setCurrentWidget2_1()
{
    for (int i = 0; i != m_vecBtn2_1.size(); ++i)
    {
        if ( m_vecBtn2_1[i]->isChecked() )
        {
            ui->stackedWidget_3->setCurrentIndex(i);
        }
    }
}

///界面2_1按钮与widget布局
void MainWindow::setCurrentWidget2_1_bak()
{
    for (int i = 0; i != m_vecBtn2_1_bak.size(); ++i)
    {
        if ( m_vecBtn2_1_bak[i]->isChecked() )
        {
            ui->stackedWidget_7->setCurrentIndex(i);
        }
    }
}

///界面3按钮与widget布局
void MainWindow::setCurrentWidget3()
{
    for (int i = 0; i != m_vecBtn3.size(); ++i)
    {
        if ( m_vecBtn3[i]->isChecked() )
        {
            ui->stackedWidget_4->setCurrentIndex(i);
        }
    }
}

///界面3按钮与widget布局
void MainWindow::setCurrentWidget3_bak()
{
    for (int i = 0; i != m_vecBtn3_bak.size(); ++i)
    {
        if ( m_vecBtn3_bak[i]->isChecked() )
        {
            ui->stackedWidget_9->setCurrentIndex(i);
        }
    }
}

///界面4按钮与widget布局
void MainWindow::setCurrentWidget4()
{
    for (int i = 0; i != m_vecBtn4.size(); ++i)
    {
        if ( m_vecBtn4[i]->isChecked() )
        {
            ui->stackedWidget_5->setCurrentIndex(i);
        }
    }
}

///界面4按钮与widget布局
void MainWindow::setCurrentWidget4_bak()
{
    for (int i = 0; i != m_vecBtn4_bak.size(); ++i)
    {
        if ( m_vecBtn4_bak[i]->isChecked() )
        {
            ui->stackedWidget_8->setCurrentIndex(i);
        }
    }
}

void MainWindow::setupModel()
{
    model = new QStandardItemModel(0,2);

    model->setHeaderData(0,Qt::Horizontal,tr("Dep"));
    model->setHeaderData(1,Qt::Horizontal,tr("Data"));
}


void MainWindow::setupView()
{

    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,300);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);

    ui->tableWidget->setSelectionModel(selectionModel);


}

/**
 * @brief 最小化窗口
 */
void MainWindow::on_minBtn_clicked()
{
    QTimer::singleShot(0, this, SLOT(showMinimized()));
}

void MainWindow::on_closeBtn_clicked()
{
    this->close();
}


/**
 * @brief 提取文件头信息
 */
void MainWindow::on_pushButton_10_clicked()
{
    setCurrentWidget2_1();
    setupModel();
    ui->tableWidget->setRowCount(18);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,400);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget->setSelectionModel(selectionModel);
    system("");

    ///显示文件头信息
    file_full = tr("./Static_detection/ELF_Header_File");
    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            line.replace(QRegExp(":"), "");
            line.replace(QRegExp("                  "), "    ");
            QStringList pieces=line.split("    ",QString::SkipEmptyParts);
            ui->tableWidget->setItem( row, 0, new QTableWidgetItem( pieces.value(0)));
            ui->tableWidget->setItem( row, 1, new QTableWidgetItem( pieces.value(1)));
            row++;
        }
    }while (!line.isEmpty());
    file.close();

}

/**
 * @brief 提取段表信息模块
 */
void MainWindow::on_pushButton_11_clicked()
{
    setCurrentWidget2_1();

    setupModel();
    ui->tableWidget_sec->setRowCount(100);
    ui->tableWidget_sec->setColumnCount(11);
    ui->tableWidget_sec->setColumnWidth(0,60);
    ui->tableWidget_sec->setColumnWidth(1,90);
    ui->tableWidget_sec->setColumnWidth(2,80);
    ui->tableWidget_sec->setColumnWidth(3,80);
    ui->tableWidget_sec->setColumnWidth(4,70);
    ui->tableWidget_sec->setColumnWidth(5,70);
    ui->tableWidget_sec->setColumnWidth(6,40);
    ui->tableWidget_sec->setColumnWidth(7,40);
    ui->tableWidget_sec->setColumnWidth(8,40);
    ui->tableWidget_sec->setColumnWidth(9,40);
    ui->tableWidget_sec->setColumnWidth(10,40);


    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_sec->setSelectionModel(selectionModel);
    system("");

    ///显示段表信息
    file_full = tr("./Static_detection/Section_Headers_File");
    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }


    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            line.replace(QRegExp("             "), "        ");
            line.replace(QRegExp("        "), " ");
            QStringList pieces=line.split(" ",QString::SkipEmptyParts);
            ui->tableWidget_sec->setItem( row, 0, new QTableWidgetItem( pieces.value(0)));
            ui->tableWidget_sec->setItem( row, 1, new QTableWidgetItem( pieces.value(1)));
            ui->tableWidget_sec->setItem( row, 2, new QTableWidgetItem( pieces.value(2)));
            ui->tableWidget_sec->setItem( row, 3, new QTableWidgetItem( pieces.value(3)));
            ui->tableWidget_sec->setItem( row, 4, new QTableWidgetItem( pieces.value(4)));
            ui->tableWidget_sec->setItem( row, 5, new QTableWidgetItem( pieces.value(5)));
            ui->tableWidget_sec->setItem( row, 6, new QTableWidgetItem( pieces.value(6)));
            ui->tableWidget_sec->setItem( row, 7, new QTableWidgetItem( pieces.value(7)));
            ui->tableWidget_sec->setItem( row, 8, new QTableWidgetItem( pieces.value(8)));
            ui->tableWidget_sec->setItem( row, 9, new QTableWidgetItem( pieces.value(9)));
            ui->tableWidget_sec->setItem( row, 10, new QTableWidgetItem( pieces.value(10)));

            row++;
        }
    }while (!line.isEmpty());
    file.close();

}

/**
 * @brief 提取符号表信息模块
 */
void MainWindow::on_pushButton_12_clicked()
{
    setCurrentWidget2_1();
    setupModel();
    ui->tableWidget_symbol->setRowCount(200);
    ui->tableWidget_symbol->setColumnCount(7);
    ui->tableWidget_symbol->setColumnWidth(1,90);
    ui->tableWidget_symbol->setColumnWidth(2,70);
    ui->tableWidget_symbol->setColumnWidth(3,80);
    ui->tableWidget_symbol->setColumnWidth(4,80);
    ui->tableWidget_symbol->setColumnWidth(5,90);
    ui->tableWidget_symbol->setColumnWidth(6,100);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_symbol->setSelectionModel(selectionModel);
    system("");

    ///显示符号表信息
    file_full = tr("./Static_detection/Symbol_Table_File");
    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }

    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            line.replace(QRegExp(":"), " ");
            QStringList pieces=line.split(" ",QString::SkipEmptyParts);
            ui->tableWidget_symbol->setItem( row, 0, new QTableWidgetItem(pieces.value(0)));
            ui->tableWidget_symbol->setItem( row, 1, new QTableWidgetItem(pieces.value(1)));
            ui->tableWidget_symbol->setItem( row, 2, new QTableWidgetItem(pieces.value(2)));
            ui->tableWidget_symbol->setItem( row, 3, new QTableWidgetItem(pieces.value(3)));
            ui->tableWidget_symbol->setItem( row, 4, new QTableWidgetItem(pieces.value(4)));
            ui->tableWidget_symbol->setItem( row, 5, new QTableWidgetItem(pieces.value(5)));
            ui->tableWidget_symbol->setItem( row, 6, new QTableWidgetItem(pieces.value(6)));

            row++;
        }
    }while (!line.isEmpty());
    file.close();

}

/**
 * @brief 提取重定位段信息模块
 */
void MainWindow::on_pushButton_13_clicked()
{
    setCurrentWidget2_1();

    setupModel();
    ui->tableWidget_rels->setRowCount(100);
    ui->tableWidget_rels->setColumnCount(5);
    ui->tableWidget_rels->setColumnWidth(0,80);
    ui->tableWidget_rels->setColumnWidth(1,80);
    ui->tableWidget_rels->setColumnWidth(2,150);
    ui->tableWidget_rels->setColumnWidth(3,100);
    ui->tableWidget_rels->setColumnWidth(4,200);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_rels->setSelectionModel(selectionModel);
    system("");

    ///显示重定位表信息
    file_full = tr("./Static_detection/Relocation_Section_File");
    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }

    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            QStringList pieces=line.split(" ",QString::SkipEmptyParts);
            ui->tableWidget_rels->setItem( row, 0, new QTableWidgetItem(pieces.value(0)));
            ui->tableWidget_rels->setItem( row, 1, new QTableWidgetItem(pieces.value(1)));
            ui->tableWidget_rels->setItem( row, 2, new QTableWidgetItem(pieces.value(2)));
            ui->tableWidget_rels->setItem( row, 3, new QTableWidgetItem(pieces.value(3)));
            ui->tableWidget_rels->setItem( row, 4, new QTableWidgetItem(pieces.value(4)));

            row++;
        }
    }while (!line.isEmpty());
    file.close();
}

/**
 * @brief 提取调试信息模块
 */
void MainWindow::on_pushButton_14_clicked()
{
    setCurrentWidget2_1();

    setupModel();
    ui->tableWidget_debug->setRowCount(100);
    ui->tableWidget_debug->setColumnCount(1);
    ui->tableWidget_debug->setColumnWidth(0,650);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_debug->setSelectionModel(selectionModel);
    system("");

    ///显示调试信息信息
    file_full = tr("./Static_detection/Debug_Info_File");
    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }

    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            ui->tableWidget_debug->setItem( row, 0, new QTableWidgetItem(line));
            row++;
        }
    }while (!line.isEmpty());
    file.close();

}


void MainWindow::cpushowWork()
{

    QString cmd = "";
    QString all = "";
    QString url = "http://127.0.0.1:8888/get?cmd=";
    cmd = "top -b -n 1";
    all = url + cmd;
    manager->get(QNetworkRequest(QUrl(all)));
}

void MainWindow::casesshowWork()
{

    QString all = "";
    QString url = "http://127.0.0.1:5566/get?cmd=";
    QString cmd = "sh ~/getout.sh";
    all = url + cmd;
    managercases->get(QNetworkRequest(QUrl(all)));
}

void MainWindow::memshowWork()
{
    cmdmem->start("python ./Dynamic_detection/file.py");

    system("");

    file_full = tr("./Dynamic_detection/log.log");


    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    ui->textBrowser_mem->setPlainText(in.readAll());
    file.close();
}

void MainWindow::cpuReplyFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf-8");

    QString all = codec->toUnicode(reply->readAll());
    QFile outFile("Tr_CPU_Output_File");
    outFile.open(QIODevice::WriteOnly);
    QTextStream out(&outFile);
    out<<all;
    outFile.close();

    cmdcpu->start("sh trance1.sh");

    system("");

    file_full = tr("Tr_CPU_Output_File");


    setupModel();
    ui->tableWidget_cpu->setRowCount(4);
    ui->tableWidget_cpu->setColumnCount(5);
    ui->tableWidget_cpu->setColumnWidth(1,110);
    ui->tableWidget_cpu->setColumnWidth(2,110);
    ui->tableWidget_cpu->setColumnWidth(3,110);
    ui->tableWidget_cpu->setColumnWidth(4,208);
    ui->tableWidget_cpu->setColumnWidth(0,100);
    ui->tableWidget_cpu->setRowHeight(1,30);
    ui->tableWidget_cpu->setRowHeight(2,30);
    ui->tableWidget_cpu->setRowHeight(3,30);
    ui->tableWidget_cpu->setRowHeight(0,30);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget->setSelectionModel(selectionModel);
    system("");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }

    QTextStream stream(&file);
    QString line;

    model->removeRows(0,model->rowCount(QModelIndex()),QModelIndex());
    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            line.replace(QRegExp(": "), ", ");
            line.replace(QRegExp(",        "), ", ");
            line.replace(QRegExp(",    "), ", ");
            line.replace(QRegExp(",   "), ", ");
            line.replace(QRegExp(",  "), ", ");

            QStringList pieces=line.split(",",QString::SkipEmptyParts);
            ui->tableWidget_cpu->setItem( row, 0, new QTableWidgetItem( pieces.value(0) + ":"));
            ui->tableWidget_cpu->setItem( row, 1, new QTableWidgetItem( pieces.value(1)));
            ui->tableWidget_cpu->setItem( row, 2, new QTableWidgetItem( pieces.value(2)));
            ui->tableWidget_cpu->setItem( row, 3, new QTableWidgetItem( pieces.value(3)));
            ui->tableWidget_cpu->setItem( row, 4, new QTableWidgetItem( pieces.value(4)));
            row++;
        }
    }while (!line.isEmpty());
    file.close();
    reply->deleteLater();
}

void MainWindow::casesReplyFinished(QNetworkReply *reply)
{

    system("");

    file_full = tr("./Case_generation/getout_File");


    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }

    QTextStream in(&file);
    ui->textBrowser_out->setPlainText(in.readAll());
    file.close();

    reply->deleteLater();
}

/**
 * @brief 提取系统利用率信息模块槽函数
 */
void MainWindow::on_pushButtoncpu_clicked()
{
    setCurrentWidget3();

    timecpu->start(2000);
}


void MainWindow::sysioshowWork()
{
    QString cmd = "";
    QString all = "";
    QString url = "http://127.0.0.1:8888/get?cmd=";

    cmd = "iostat -dkx 1 1";
    all = url + cmd;
    managersysio->get(QNetworkRequest(QUrl(all)));
}

void MainWindow::sysioReplyFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf-8");

    QString all = codec->toUnicode(reply->readAll());
    QFile outFile("SYSIO_Output_File");
    outFile.open(QIODevice::WriteOnly);
    QTextStream out(&outFile);
    out<<all;
    outFile.close();

    cmdsysio->start("sh trancesysio.sh");

    setupModel();
    ui->tableWidget_sysio->setRowCount(14);
    ui->tableWidget_sysio->setColumnCount(2);
    ui->tableWidget_sysio->setColumnWidth(0,300);
    ui->tableWidget_sysio->setColumnWidth(1,200);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);

    ui->tableWidget->setSelectionModel(selectionModel);
    system("");

    file_full = tr("Tr_SYSIO_Output_File");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }

    QTextStream stream(&file);
    QString line;

    model->removeRows(0,model->rowCount(QModelIndex()),QModelIndex());
    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            line.replace(QRegExp(":"), "");
            line.replace(QRegExp("		"), "   ");
            QStringList pieces=line.split("   ",QString::SkipEmptyParts);
            ui->tableWidget_sysio->setItem( row, 0, new QTableWidgetItem( pieces.value(0)));
            ui->tableWidget_sysio->setItem( row, 1, new QTableWidgetItem( pieces.value(1)));
            row++;
        }
    }while (!line.isEmpty());
    file.close();
    reply->deleteLater();
}

/**
 * @brief 提取系统吞吐量信息模块槽函数
 */
void MainWindow::on_pushButtonsysio_clicked()
{
    setCurrentWidget3();

    timecpu->stop();

    timesysio->start(2000);
}

void MainWindow::resaddReplyFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf-8");

    ui->textBrowseradd->setPlainText(codec->toUnicode(reply->readAll()));
    reply->deleteLater();
}

/**
 * @brief 获取指定代码响应时间模块槽函数
 */
void MainWindow::on_pushButtonrealtime_clicked()
{
    setCurrentWidget3();

    timesysio->stop();

    managerresadd->get(QNetworkRequest(QUrl("http://127.0.0.1:5555/get?cmd=objdump -d /home/wei/workspace/mystrace_new/test")));

}

void MainWindow::filereplyFinished(QNetworkReply *reply)
{
    reply->deleteLater();
}

/**
 * @brief 导入数据到虚拟仿真环境模块槽函数
 */
void MainWindow::on_pushButtonload_clicked()
{
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QStringList filelist;
    filelist = QFileDialog::getOpenFileNames(this, codec->toUnicode("导入到服务器"), "./binarycode", "*");
    QString all = "";
    QString url = "http://127.0.0.1:5555/get?cmd=";
    QString src = "gmm@10.0.2.2:";
    for (j = filelist.begin(); j < filelist.end(); j++)
    {
        file1[k] = *j;
        all = url + "scp " + src + file1[k] + " " + "/home/wei/";
        managerfile->get(QNetworkRequest(QUrl(all)));
        system("");
        k++;
    }
}

void MainWindow::restimeReplyFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf-8");

    QString all = codec->toUnicode(reply->readAll());
    QFile outFile("SYS_time_File");
    outFile.open(QIODevice::WriteOnly);
    QTextStream out(&outFile);
    out<<all;
    outFile.close();

    cmdsystime->start("sh tracesystime.sh");

    system("");

    file_full = tr("./test_report/SYS_time_File");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    ui->textBrowserrestime->setPlainText(codec->toUnicode(file.readAll()));
    file.close();
    reply->deleteLater();
}

/**
 * @brief 获取指定代码响应时间功能模块
 */
void MainWindow::on_pushButtonrestime_clicked()
{
    QString cmd1 = ui->lineEditbeg->text();
    QString cmd2 = ui->lineEditend->text();
    QString all = "";
    QString url = "http://127.0.0.1:8888/get?cmd=";
    all = url + "/home/wei/workspace/mystrace_new/mystrace -p 0x" + cmd1 + " -e 0x" + cmd2 + " /home/wei/workspace/mystrace_new/test";
    managerrestime->get(QNetworkRequest(QUrl(all)));

}
/**
 * @brief 布局4变换按钮
 */

void MainWindow::memcheckresReplyFinished(QNetworkReply *reply)
{

    //cmdmemcheck->start("sh memcheck.sh");

    setupModel();
    ui->tableWidget_stack->setRowCount(1000);
    ui->tableWidget_stack->setColumnCount(1);
    ui->tableWidget_stack->setColumnWidth(0,730);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_stack->setSelectionModel(selectionModel);
    system("");

    file_full = tr("./Dynamic_detection/log_stack_File");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            ui->tableWidget_stack->setItem( row, 0, new QTableWidgetItem(line));
            row++;
        }
    }while (!line.isEmpty());
    file.close();
    reply->deleteLater();
}

/**
 * @brief 提取堆栈溢出信息功能模块槽函数
 */
void MainWindow::on_pushButtonstack_clicked()
{
    setCurrentWidget4();


    ui->textBrowser_mem->setHidden(true);
    timemem->stop();

    cmdmemcheck->start("sh memcheck.sh");
    setupModel();
    ui->tableWidget_stack->setRowCount(1000);
    ui->tableWidget_stack->setColumnCount(1);
    ui->tableWidget_stack->setColumnWidth(0,730);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_stack->setSelectionModel(selectionModel);
    system("");

    file_full = tr("./Dynamic_detection/log_stack_File");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            ui->tableWidget_stack->setItem( row, 0, new QTableWidgetItem(line));
            row++;
        }
    }while (!line.isEmpty());
    file.close();

}

/**
 * @brief 提取内存泄露检测信息槽函数
 */
void MainWindow::on_pushButtonmem_clicked()
{
    setCurrentWidget4();

    setupModel();
    ui->tableWidget_mem->setRowCount(1000);
    ui->tableWidget_mem->setColumnCount(1);
    ui->tableWidget_mem->setColumnWidth(0,730);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_mem->setSelectionModel(selectionModel);
    system("");
    file_full = tr("./Dynamic_detection/log_leak_File");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            ui->tableWidget_mem->setItem( row, 0, new QTableWidgetItem(line));
            row++;
        }
    }while (!line.isEmpty());
    file.close();
}

/**
 * @brief 提取未初始化检测信息模块槽函数
 */
void MainWindow::on_pushButtonundef_clicked()
{
    setCurrentWidget4();

    setupModel();
    ui->tableWidget_undef->setRowCount(1000);
    ui->tableWidget_undef->setColumnCount(1);
    ui->tableWidget_undef->setColumnWidth(0,730);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_undef->setSelectionModel(selectionModel);
    system("");

    file_full = tr("./Dynamic_detection/log_uninit_File");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            ui->tableWidget_undef->setItem( row, 0, new QTableWidgetItem(line));
            row++;
        }
    }while (!line.isEmpty());
    file.close();
}

/**
 * @brief 提取整数溢出检测信息模块槽函数
 */
void MainWindow::on_pushButtonint_clicked()
{
    setCurrentWidget4();
    setupModel();
    ui->tableWidget_unsc->setRowCount(1000);
    ui->tableWidget_unsc->setColumnCount(1);
    ui->tableWidget_unsc->setColumnWidth(0,730);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_unsc->setSelectionModel(selectionModel);
    system("");

    file_full = tr("./Dynamic_detection/log_sc_File");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            ui->tableWidget_unsc->setItem( row, 0, new QTableWidgetItem(line));
            row++;
        }
    }while (!line.isEmpty());
    file.close();
}

/**
 * @brief 提取冗余代码检测信息模块槽函数
 */
void MainWindow::on_pushButtonred_clicked()
{
    setCurrentWidget4();

    setupModel();
    ui->tableWidget_rongyu->setColumnCount(3);
    ui->tableWidget_rongyu->setRowCount(14);
    ui->tableWidget_rongyu->setColumnWidth(0,150);
    ui->tableWidget_rongyu->setColumnWidth(1,150);
    ui->tableWidget_rongyu->setColumnWidth(2,400);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_rongyu->setSelectionModel(selectionModel);
    system("");

    file_full = tr("rongYu_File");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    QTextStream stream(&file);
    QString line;

    model->removeRows(0,model->rowCount(QModelIndex()),QModelIndex());
    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            line.replace(QRegExp(":"), "");
            line.replace(QRegExp("              "), "    ");
            QStringList pieces=line.split(" ",QString::SkipEmptyParts);
            ui->tableWidget_rongyu->setItem( row, 0, new QTableWidgetItem( pieces.value(0)));
            ui->tableWidget_rongyu->setItem( row, 1, new QTableWidgetItem( pieces.value(1)));
            ui->tableWidget_rongyu->setItem( row, 2, new QTableWidgetItem( pieces.value(2)));
            row++;
        }
    }while (!line.isEmpty());
    file.close();

}

/**
 * @brief 动态检测返回信息处理模块
 * @param reply
 */
void MainWindow::memcheckReplyFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf-8");

    if (reply->readAll() != NULL)
    {
        timemem->stop();

        QMessageBox::information(this,codec->toUnicode("检测提示信息框"),
                                     codec->toUnicode("动态检测已完成，请查看检测结果！！！"));
                return;
    }
    reply->deleteLater();
}

/**
 * @brief 动态检测功能槽函数
 */
void MainWindow::on_pushButtoncheck_clicked()
{
    timecases->stop();
    QString cmd = "";
    QString all = "";
    QString url = "http://127.0.0.1:5555/get?cmd=";
    cmd = "sh memchecktestnew.sh";
    all = url + cmd;
    ui->textBrowser_mem->setHidden(false);
    timemem->start(32000);
    managermemcheck->get(QNetworkRequest(QUrl(all)));
}

void MainWindow::coverresReplyFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf-8");

    if (reply->readAll() != NULL)
    {
        timecases->stop();
        QMessageBox::information(this,codec->toUnicode("检测提示信息框"),
                                     codec->toUnicode("测试用例已生成，请查看用例信息！！！"));
                return;
    }
    reply->deleteLater();
}

/**
 * @brief 测试用例生成功能命令模块
 */
void MainWindow::on_pushButtoncovercheck_clicked()
{
    QString all = "";
    QString url = "http://127.0.0.1:5555/get?cmd=";
    QString cmd = "sh ~/testcases.sh";
    all = url + cmd;
    ui->textBrowser_out->setHidden(false);
    timecases->start(32000);
    managercover->get(QNetworkRequest(QUrl(all)));
}


/**
 * @brief 显示测试用例信息功能模块
 */
void MainWindow::on_pushButtoncase_clicked()
{
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    ui->textBrowser_out->setHidden(true);
    cmdgetpath->start("sh gettrace.sh");
    qApp->processEvents();
    update();
    system("");

    int kongge = 100;
    file_full = tr("./test_report/testcases_File");



    ui->tableWidget_case->setColumnCount(20);
    ui->tableWidget_case->setRowCount(1000);
    ui->tableWidget_route_2->setRowCount(1000);

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }

    QTextStream stream(&file);
    QString line;

    int row = 0;
    int col = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            QStringList pieces=line.split(" ",QString::SkipEmptyParts);
            for (col = 0; col < kongge; col++)
            {
                ui->tableWidget_case->setItem( row, col, new QTableWidgetItem(pieces.value(col)));
            }
            row++;
        }
    }while (!line.isEmpty());
    file.close();

    system("");

    file_full = tr("./test_report/get_trace_File");
    QFile file1(file_full);
    if (!file1.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }

    QTextStream stream1(&file1);
    QString line1;

    int row1 = 0;
    do
    {
        line1 = stream1.readLine();
        if (!line1.isEmpty())
        {
            ui->tableWidget_route_2->setItem( row1, 0, new QTableWidgetItem(line1));
            row1++;
        }
    }while (!line1.isEmpty());
    ui->label_fugai->setText(QString::number(row) + codec->toUnicode(" 条"));
    file1.close();

}

void MainWindow::scalethepix(int scale)
{
    showImage->arise_scale(scale);
}

void MainWindow::scalethepix1(int scale)
{
    showImage1->arise_scale(scale);
}

/**
 * @brief 跟随缩放滑动条显示百分之几
 * @param val
 */
void MainWindow::changelabel(int val)
{
    QString tmp;
    tmp.setNum(val);
    tmp += "%";
    label->setText(tmp);
}


/**
 * @brief 跟随缩放滑动条显示百分之几
 * @param val
 */
void MainWindow::changelabel1(int val)
{
    QString tmp;
    tmp.setNum(val);
    tmp += "%";
    label1->setText(tmp);
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    QString str;
    switch(event->orientation())//返回滚轮方向:水平或垂直
    {
    case Qt::Horizontal:
        str = "Horizontal Whell Move";
        break;
    case Qt::Vertical:
        str = "Vertical Whell Move";
        break;
    default:
        break;
    }
    str += "\n";
    str += "    ";
    if(event->delta()>0)//返回滚动距离
        str += "go ahead";
    else
        str += "go back";
    qDebug()<<str;
    int numDegrees = event->delta() / 8;//15度
    int value = slider->value();
    int value1 = slider->value();

    slider->setValue(value+numDegrees);
    slider1->setValue(value1+numDegrees);


}

/**
 * @brief 生成测试报告模块槽函数
 */
void MainWindow::on_pushButton_7_clicked()
{
    setCurrentWidget();

    setupModel();
    ui->tableWidget_case_2->setRowCount(1000);
    ui->tableWidget_case_2->setColumnCount(20);


    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_case_2->setSelectionModel(selectionModel);
    system("");

    ///显示文件头信息
    file_full = tr("./test_report/testcases_File");
    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    QTextStream stream1(&file);
    QString line1;


    int row1 = 0;
    int col1 = 0;
    do
    {
        line1 = stream1.readLine();
        if (!line1.isEmpty())
        {
            QStringList pieces1=line1.split(" ",QString::SkipEmptyParts);
            for (col1 = 0; col1 < 100; col1++)
            {
                ui->tableWidget_case_2->setItem( row1, col1, new QTableWidgetItem(pieces1.value(col1)));
            }
            row1++;
        }
    }while (!line1.isEmpty());
    file.close();

}

void MainWindow::on_pushButton_15_clicked()
{
    setCurrentWidget2_1_bak();
    setupModel();
    ui->tableWidget_3->setRowCount(18);
    ui->tableWidget_3->setColumnCount(2);
    ui->tableWidget_3->setColumnWidth(0,150);
    ui->tableWidget_3->setColumnWidth(1,400);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_3->setSelectionModel(selectionModel);
    system("");

    ///显示文件头信息
    file_full = tr("./test_report/ELF_Header_File");
    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            line.replace(QRegExp(":"), "");
            line.replace(QRegExp("                  "), "    ");
            QStringList pieces=line.split("    ",QString::SkipEmptyParts);
            ui->tableWidget_3->setItem( row, 0, new QTableWidgetItem( pieces.value(0)));
            ui->tableWidget_3->setItem( row, 1, new QTableWidgetItem( pieces.value(1)));
            row++;
        }
    }while (!line.isEmpty());
    file.close();

}

void MainWindow::on_pushButton_16_clicked()
{
    setCurrentWidget2_1_bak();
    setupModel();
    ui->tableWidget_sec_2->setRowCount(200);
    ui->tableWidget_sec_2->setColumnCount(11);
    ui->tableWidget_sec_2->setColumnWidth(0,60);
    ui->tableWidget_sec_2->setColumnWidth(1,90);
    ui->tableWidget_sec_2->setColumnWidth(2,80);
    ui->tableWidget_sec_2->setColumnWidth(3,80);
    ui->tableWidget_sec_2->setColumnWidth(4,70);
    ui->tableWidget_sec_2->setColumnWidth(5,70);
    ui->tableWidget_sec_2->setColumnWidth(6,40);
    ui->tableWidget_sec_2->setColumnWidth(7,40);
    ui->tableWidget_sec_2->setColumnWidth(8,40);
    ui->tableWidget_sec_2->setColumnWidth(9,40);
    ui->tableWidget_sec_2->setColumnWidth(10,40);


    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_sec_2->setSelectionModel(selectionModel);
    system("");

    ///显示段表信息
    file_full = tr("./test_report/Section_Headers_File");
    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }


    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            line.replace(QRegExp("             "), "        ");
            line.replace(QRegExp("        "), " ");
            QStringList pieces=line.split(" ",QString::SkipEmptyParts);
            ui->tableWidget_sec_2->setItem( row, 0, new QTableWidgetItem( pieces.value(0)));
            ui->tableWidget_sec_2->setItem( row, 1, new QTableWidgetItem( pieces.value(1)));
            ui->tableWidget_sec_2->setItem( row, 2, new QTableWidgetItem( pieces.value(2)));
            ui->tableWidget_sec_2->setItem( row, 3, new QTableWidgetItem( pieces.value(3)));
            ui->tableWidget_sec_2->setItem( row, 4, new QTableWidgetItem( pieces.value(4)));
            ui->tableWidget_sec_2->setItem( row, 5, new QTableWidgetItem( pieces.value(5)));
            ui->tableWidget_sec_2->setItem( row, 6, new QTableWidgetItem( pieces.value(6)));
            ui->tableWidget_sec_2->setItem( row, 7, new QTableWidgetItem( pieces.value(7)));
            ui->tableWidget_sec_2->setItem( row, 8, new QTableWidgetItem( pieces.value(8)));
            ui->tableWidget_sec_2->setItem( row, 9, new QTableWidgetItem( pieces.value(9)));
            ui->tableWidget_sec_2->setItem( row, 10, new QTableWidgetItem( pieces.value(10)));

            row++;
        }
    }while (!line.isEmpty());
    file.close();
}

void MainWindow::on_pushButton_17_clicked()
{
    setCurrentWidget2_1_bak();

    setupModel();
    ui->tableWidget_symbol_2->setRowCount(200);
    ui->tableWidget_symbol_2->setColumnCount(7);
    ui->tableWidget_symbol_2->setColumnWidth(1,90);
    ui->tableWidget_symbol_2->setColumnWidth(2,70);
    ui->tableWidget_symbol_2->setColumnWidth(3,80);
    ui->tableWidget_symbol_2->setColumnWidth(4,80);
    ui->tableWidget_symbol_2->setColumnWidth(5,90);
    ui->tableWidget_symbol_2->setColumnWidth(6,100);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_symbol_2->setSelectionModel(selectionModel);
    system("");

    ///显示符号表信息
    file_full = tr("./test_report/Symbol_Table_File");
    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }

    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            line.replace(QRegExp(":"), " ");
            //line.replace(QRegExp("                  "), "    ");
            QStringList pieces=line.split(" ",QString::SkipEmptyParts);
            ui->tableWidget_symbol_2->setItem( row, 0, new QTableWidgetItem(pieces.value(0)));
            ui->tableWidget_symbol_2->setItem( row, 1, new QTableWidgetItem(pieces.value(1)));
            ui->tableWidget_symbol_2->setItem( row, 2, new QTableWidgetItem(pieces.value(2)));
            ui->tableWidget_symbol_2->setItem( row, 3, new QTableWidgetItem(pieces.value(3)));
            ui->tableWidget_symbol_2->setItem( row, 4, new QTableWidgetItem(pieces.value(4)));
            ui->tableWidget_symbol_2->setItem( row, 5, new QTableWidgetItem(pieces.value(5)));
            ui->tableWidget_symbol_2->setItem( row, 6, new QTableWidgetItem(pieces.value(6)));

            row++;
        }
    }while (!line.isEmpty());
    file.close();
}

void MainWindow::on_pushButton_18_clicked()
{
    setCurrentWidget2_1_bak();

    setupModel();
    ui->tableWidget_rels_2->setRowCount(200);
    ui->tableWidget_rels_2->setColumnCount(5);
    ui->tableWidget_rels_2->setColumnWidth(0,80);
    ui->tableWidget_rels_2->setColumnWidth(1,80);
    ui->tableWidget_rels_2->setColumnWidth(2,150);
    ui->tableWidget_rels_2->setColumnWidth(3,100);
    ui->tableWidget_rels_2->setColumnWidth(4,200);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_rels_2->setSelectionModel(selectionModel);
    system("");

    ///显示重定位表信息
    file_full = tr("./test_report/Relocation_Section_File");
    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }

    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            QStringList pieces=line.split(" ",QString::SkipEmptyParts);
            ui->tableWidget_rels_2->setItem( row, 0, new QTableWidgetItem(pieces.value(0)));
            ui->tableWidget_rels_2->setItem( row, 1, new QTableWidgetItem(pieces.value(1)));
            ui->tableWidget_rels_2->setItem( row, 2, new QTableWidgetItem(pieces.value(2)));
            ui->tableWidget_rels_2->setItem( row, 3, new QTableWidgetItem(pieces.value(3)));
            ui->tableWidget_rels_2->setItem( row, 4, new QTableWidgetItem(pieces.value(4)));

            row++;
        }
    }while (!line.isEmpty());
    file.close();
}

void MainWindow::on_pushButton_19_clicked()
{
    setCurrentWidget2_1_bak();

    setupModel();
    ui->tableWidget_debug_2->setRowCount(200);
    ui->tableWidget_debug_2->setColumnCount(1);
    ui->tableWidget_debug_2->setColumnWidth(0,650);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_debug_2->setSelectionModel(selectionModel);
    system("");

    ///显示调试信息信息
    file_full = tr("./test_report/Debug_Info_File");
    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }

    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            ui->tableWidget_debug_2->setItem( row, 0, new QTableWidgetItem(line));
            row++;
        }
    }while (!line.isEmpty());
    file.close();

}

void MainWindow::on_pushButtonstack_2_clicked()
{
    setCurrentWidget4_bak();

    setupModel();
    ui->tableWidget_stack_2->setRowCount(1000);
    ui->tableWidget_stack_2->setColumnCount(1);
    ui->tableWidget_stack_2->setColumnWidth(0,730);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_stack_2->setSelectionModel(selectionModel);
    system("");

    file_full = tr("./test_report/log_stack_File");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            ui->tableWidget_stack_2->setItem( row, 0, new QTableWidgetItem(line));
            row++;
        }
    }while (!line.isEmpty());
    file.close();
}

void MainWindow::on_pushButtonmem_2_clicked()
{
    setCurrentWidget4_bak();

    setupModel();
    ui->tableWidget_mem_2->setRowCount(1000);
    ui->tableWidget_mem_2->setColumnCount(1);
    ui->tableWidget_mem_2->setColumnWidth(0,730);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_mem_2->setSelectionModel(selectionModel);
    system("");
    file_full = tr("./test_report/log_leak_File");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            ui->tableWidget_mem_2->setItem( row, 0, new QTableWidgetItem(line));
            row++;
        }
    }while (!line.isEmpty());
    file.close();
}

void MainWindow::on_pushButtonundef_2_clicked()
{
    setCurrentWidget4_bak();
    setupModel();
    ui->tableWidget_undef_2->setRowCount(1000);
    ui->tableWidget_undef_2->setColumnCount(1);
    ui->tableWidget_undef_2->setColumnWidth(0,730);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_undef_2->setSelectionModel(selectionModel);
    system("");

    file_full = tr("./test_report/log_uninit_File");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            ui->tableWidget_undef_2->setItem( row, 0, new QTableWidgetItem(line));
            row++;
        }
    }while (!line.isEmpty());
    file.close();
}

void MainWindow::on_pushButtonint_2_clicked()
{
    setCurrentWidget4_bak();
    setupModel();
    ui->tableWidget_unsc_2->setRowCount(1000);
    ui->tableWidget_unsc_2->setColumnCount(1);
    ui->tableWidget_unsc_2->setColumnWidth(0,730);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_unsc_2->setSelectionModel(selectionModel);
    system("");

    file_full = tr("./test_report/log_sc_File");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    QTextStream stream(&file);
    QString line;

    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            ui->tableWidget_unsc_2->setItem( row, 0, new QTableWidgetItem(line));
            row++;
        }
    }while (!line.isEmpty());
    file.close();
}

void MainWindow::on_pushButtonred_2_clicked()
{
    setCurrentWidget4_bak();

    setupModel();
    ui->tableWidget_rongyu_2->setColumnCount(3);
    ui->tableWidget_rongyu_2->setRowCount(14);
    ui->tableWidget_rongyu_2->setColumnWidth(0,150);
    ui->tableWidget_rongyu_2->setColumnWidth(1,150);
    ui->tableWidget_rongyu_2->setColumnWidth(2,400);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget_rongyu_2->setSelectionModel(selectionModel);
    system("");

    file_full = tr("./test_report/rongYu_File");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    QTextStream stream(&file);
    QString line;

    model->removeRows(0,model->rowCount(QModelIndex()),QModelIndex());
    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            line.replace(QRegExp(":"), "");
            line.replace(QRegExp("              "), "    ");
            QStringList pieces=line.split(" ",QString::SkipEmptyParts);
            ui->tableWidget_rongyu_2->setItem( row, 0, new QTableWidgetItem( pieces.value(0)));
            ui->tableWidget_rongyu_2->setItem( row, 1, new QTableWidgetItem( pieces.value(1)));
            ui->tableWidget_rongyu_2->setItem( row, 2, new QTableWidgetItem( pieces.value(2)));
            row++;
        }
    }while (!line.isEmpty());
    file.close();
}

void MainWindow::on_pushButtoncpu_2_clicked()
{
    setCurrentWidget3_bak();

    system("");

    file_full = tr("./test_report/Tr_CPU_Output_File");
    setupModel();
    ui->tableWidget_cpu_2->setRowCount(4);
    ui->tableWidget_cpu_2->setColumnCount(5);
    ui->tableWidget_cpu_2->setColumnWidth(1,110);
    ui->tableWidget_cpu_2->setColumnWidth(2,110);
    ui->tableWidget_cpu_2->setColumnWidth(3,110);
    ui->tableWidget_cpu_2->setColumnWidth(4,208);
    ui->tableWidget_cpu_2->setColumnWidth(0,100);
    ui->tableWidget_cpu_2->setRowHeight(1,30);
    ui->tableWidget_cpu_2->setRowHeight(2,30);
    ui->tableWidget_cpu_2->setRowHeight(3,30);
    ui->tableWidget_cpu_2->setRowHeight(0,30);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget->setSelectionModel(selectionModel);
    system("");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }

    QTextStream stream(&file);
    QString line;

    model->removeRows(0,model->rowCount(QModelIndex()),QModelIndex());
    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            line.replace(QRegExp(": "), ", ");
            line.replace(QRegExp(",        "), ", ");
            line.replace(QRegExp(",    "), ", ");
            line.replace(QRegExp(",   "), ", ");
            line.replace(QRegExp(",  "), ", ");

            QStringList pieces=line.split(",",QString::SkipEmptyParts);
            ui->tableWidget_cpu_2->setItem( row, 0, new QTableWidgetItem( pieces.value(0) + ":"));
            ui->tableWidget_cpu_2->setItem( row, 1, new QTableWidgetItem( pieces.value(1)));
            ui->tableWidget_cpu_2->setItem( row, 2, new QTableWidgetItem( pieces.value(2)));
            ui->tableWidget_cpu_2->setItem( row, 3, new QTableWidgetItem( pieces.value(3)));
            ui->tableWidget_cpu_2->setItem( row, 4, new QTableWidgetItem( pieces.value(4)));

            row++;
        }
    }while (!line.isEmpty());
    file.close();
}

void MainWindow::on_pushButtonsysio_2_clicked()
{
    setCurrentWidget3_bak();
    setupModel();
    ui->tableWidget_sysio_2->setRowCount(14);
    ui->tableWidget_sysio_2->setColumnCount(2);
    ui->tableWidget_sysio_2->setColumnWidth(0,300);
    ui->tableWidget_sysio_2->setColumnWidth(1,200);

    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    ui->tableWidget->setSelectionModel(selectionModel);
    system("");

    file_full = tr("./test_report/Tr_SYSIO_Output_File");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }

    QTextStream stream(&file);
    QString line;

    model->removeRows(0,model->rowCount(QModelIndex()),QModelIndex());
    int row = 0;
    do
    {
        line = stream.readLine();
        if (!line.isEmpty())
        {
            line.replace(QRegExp(":"), "");
            line.replace(QRegExp("		"), "   ");
            //model->insertRows(row, 1, QModelIndex());
            QStringList pieces=line.split("   ",QString::SkipEmptyParts);
            //model->setData(model->index(row, 0, QModelIndex()),pieces.value(0));
            ui->tableWidget_sysio_2->setItem( row, 0, new QTableWidgetItem( pieces.value(0)));
            ui->tableWidget_sysio_2->setItem( row, 1, new QTableWidgetItem( pieces.value(1)));
            //model->setData(model->index(row, 1, QModelIndex()),pieces.value(1));
            row++;
        }
    }while (!line.isEmpty());
    file.close();
}

void MainWindow::on_pushButtonrealtime_2_clicked()
{
    setCurrentWidget3_bak();
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    system("");

    file_full = tr("./test_report/SYS_time_File");

    QFile file(file_full);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file_full)
                             .arg(file.errorString()));
        return;
    }
    ui->textBrowser_7->setPlainText(codec->toUnicode(file.readAll()));

    file.close();
}

/**
 * @brief 导入数据到客户机模块槽函数
 */
void MainWindow::on_pushButtonload_2_clicked()
{
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QStringList filelist;
    filelist = QFileDialog::getOpenFileNames(this, codec->toUnicode("导入到客户端"), "./binarycode", "*");
    QString all = "";
    QString src = "gmm@127.0.0.1:";
    for (j = filelist.begin(); j < filelist.end(); j++)
    {
        file1[k] = *j;

        all = "sh /home/gmm/Documents/EBTS/build-EBTS-Result/copy.sh " + src + file1[k] + " /home/gmm/Documents/EBTS/build-EBTS-Result/";
        cmdcopy->start(all);
        system("");
        k++;
    }
}
