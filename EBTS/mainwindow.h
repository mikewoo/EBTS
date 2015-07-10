#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
//#include <QTextCodec>
#include <QProcess>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QTimer>
#include <QPixmap>
#include <QLabel>
#include <QTextStream> //文件流
#include <QMessageBox> //出错窗口
#include <QtNetwork>
#include <QSplitter>
#include <QStandardItemModel>
#include <QTableView>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QSplitter>
#include <QDialog>

namespace Ui {
class MainWindow;
}

QT_BEGIN_NAMESPACE
class QPushButton;
class QCheckBox;
class QSlider;
class QLabel;
QT_END_NAMESPACE
class ShowImage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createAction();
    void createMenu();
    void setupModel();
    void setupView();
    void openFile();
    QString file_full, file_name, file_path;
    QFileInfo fi;
 protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void changeEvent(QEvent *);
    void wheelEvent(QWheelEvent *event);//鼠标滚轮移动

private slots:
    void ShowDateTime();            //动态显示在线时长及当前日期时间

    void on_menuBtn_clicked();

    void on_pushButton_clicked();   //系统主页按钮处理槽函数

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_minBtn_clicked();

    void on_closeBtn_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void scalethepix(int);

    void changelabel(int);

    void scalethepix1(int);

    void changelabel1(int);

    void on_pushButtoncpu_clicked();

    void on_pushButtonsysio_clicked();

    void on_pushButtonrealtime_clicked();

    void cpuReplyFinished(QNetworkReply *);

    void cpushowWork();

    void casesReplyFinished(QNetworkReply *);

    void casesshowWork();

    //void memReplyFinished(QNetworkReply *);

    void memshowWork();

    void sysioReplyFinished(QNetworkReply *);

    void sysioshowWork();

    void resaddReplyFinished(QNetworkReply *);

    void restimeReplyFinished(QNetworkReply *);

    void memcheckReplyFinished(QNetworkReply *);

    void memcheckresReplyFinished(QNetworkReply *);

    void coverresReplyFinished(QNetworkReply *);

    void on_pushButtonload_clicked();

    void filereplyFinished(QNetworkReply*);

    void on_pushButtonrestime_clicked();

    void on_pushButtonstack_clicked();

    void on_pushButtonmem_clicked();

    void on_pushButtonundef_clicked();

    void on_pushButtonint_clicked();

    void on_pushButtonred_clicked();

    void on_pushButtoncheck_clicked();

    void on_pushButtoncovercheck_clicked();

    void on_pushButtoncase_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButtonstack_2_clicked();

    void on_pushButtonmem_2_clicked();

    void on_pushButtonundef_2_clicked();

    void on_pushButtonint_2_clicked();

    void on_pushButtonred_2_clicked();

    void on_pushButtoncpu_2_clicked();

    void on_pushButtonsysio_2_clicked();

    void on_pushButtonrealtime_2_clicked();

    void on_pushButtonload_2_clicked();

private:
    Ui::MainWindow *ui;

    ///进程控制
    QProcess *cmdexeccode;                  //开辟新的进程获取执行代码信息
    QProcess *cmdcpu;                       //开辟新的进程显示处理器、内存利用率
    QProcess *cmdsysio;                     //开辟新的进程显示系统吞吐量
    QProcess *cmdrestime;                   //开辟新的进程显示指定代码响应时间
    QProcess *cmdmemcheck;                  //开辟新的进程完成内存相关的检测
    QProcess *cmdgetpath;                  //开辟新的进程完成内存相关的检测
    QProcess *cmdsystime;                  //开辟新的进程完成内存相关的检测
    QProcess *cmdcases;                       //开辟新的进程显示处理器、内存利用率

    QProcess *cmdmem;                       //开辟新的进程显示处理器、内存利用率
    QProcess *cmdcopy;                       //开辟新的进程显示处理器、内存利用率


    QPixmap m_pixmapBg;
    QAction *m_AactionAboutQt;
    QMenu *m_menu;

    QPoint m_pointStart;
    QPoint m_pointPress;

    QTimer *timer;
    QPixmap pix;
    QLabel *label;
    QImage image1;

    QSlider *slider;
    QSlider *slider1;

    QLabel *label2;

    ShowImage *showImage;
    ShowImage *showImage1;


    QLabel *label1;

    QMenu *fileMenu;
    QAction *openAct;

    QStandardItemModel *model;
    QTableView *table;
    QSplitter *splitter;

    ///布局容器
    QVector <QPushButton* > m_vecBtn;       //主界面布局
    QVector <QPushButton* > m_vecBtn2;      //界面2布局
    QVector <QPushButton* > m_vecBtn2_1_bak;//界面静态检测汇总布局
    QVector <QPushButton* > m_vecBtn2_1;    //界面2布局
    QVector <QPushButton* > m_vecBtn3;      //界面3布局
    QVector <QPushButton* > m_vecBtn4;      //界面4布局
    QVector <QPushButton* > m_vecBtn4_bak;      //界面4布局
    QVector <QPushButton* > m_vecBtn3_bak;      //界面3布局

    ///网络数据管理
    QNetworkAccessManager *manager;              //获取处理器利用率的网络数据
    QNetworkAccessManager *managerfile;          //上传文件的网络数据
    QNetworkAccessManager *managersysio;         //获取系统吞吐量的网络数据
    QNetworkAccessManager *managerresadd;        //获取指定代码响应时间的网络数据
    QNetworkAccessManager *managerrestime;       //获取指定代码响应时间的网络数据
    QNetworkAccessManager *managermemcheck;      //获取动态检测的网络数据
    QNetworkAccessManager *managermemcheckres;   //获取动态检测结果的网络数据
    QNetworkAccessManager *managercover;         //获取覆盖检测结果的网络数据

    QNetworkAccessManager *managercases;              //获取处理器利用率的网络数据

    QNetworkAccessManager *managermem;              //获取处理器利用率的网络数据


    ///定时器
    QTimer *timerDate;                      //计算在线时长和显示当前时间定时器对象
    QTimer *timecpu;                        //动态显示cpu利用率定时器
    QTimer *timesysio;                      //动态显示系统吞吐量定时器
    QTimer *timecases;                        //动态显示cpu利用率定时器

    QTimer *timemem;                        //动态显示cpu利用率定时器


    ///成员变量初始化；
    void initData();

    ///自定义窗口样式；
    void setNomalStyle();

    ///功能选择函数；
    void setCurrentWidget();

    ///界面2功能选择函数；
    void setCurrentWidget2();

    ///界面2_1功能选择函数；
    void setCurrentWidget2_1();

    ///界面静态汇总功能选择函数；
    void setCurrentWidget2_1_bak();

    ///界面3功能选择函数；
    void setCurrentWidget3();

    ///界面3功能选择函数；
    void setCurrentWidget3_bak();

    ///界面4功能选择函数；
    void setCurrentWidget4();

    void setCurrentWidget4_bak();
};

#endif // MAINWINDOW_H
