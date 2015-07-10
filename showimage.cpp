#include <QtGui>
#include <QMouseEvent>
//#include <QDebug>
//#include <QString>
//#include <QWheelEvent>
//#include <QKeyEvent>
//#include <QResizeEvent>
#include "showimage.h"

ShowImage::ShowImage(QWidget *parent)
    :QWidget(parent),wscale(1.0),hscale(1.0)
{
    init_path(QDir("C:/"),0);
//    setBackgroundRole(QPalette::Window);
//    setBackgroundRole(QPalette::WindowText);//黑色背景
//    setBackgroundRole(QPalette::Foreground);//黑色背景
//    setBackgroundRole(QPalette::Base);//白色背景
    setBackgroundRole(QPalette::Background);//系统背景

    setAutoFillBackground(true);//自动填充背景
    FirstTimeShowFlag = true;
}

QSize ShowImage::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize ShowImage::sizeHint() const
{
    return QSize(640, 480);
}

void ShowImage::init_path(QDir newdir, QString file)
{
    filepath = QDir(newdir);
    //filepath = "D:\testsrc\day0812\build-AnImageBrowser-桌面-Debug";
    QStringList filters;
    filters<<"*.jpg";
    filepath.setNameFilters(filters);//文件类型过滤

    //设置过滤器
    filepath.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    filepath.setSorting(QDir::Size | QDir::Reversed);//设置排序顺序:按大小，反向排序
    list = filepath.entryList();//返回一个列表目录中的所有文件和目录的名称

    if (!list.empty())
    {
        emit get2beg(false);
        emit get2end(false);
    }
    else//列表不为空，开始显示
    {
        emit get2beg(true);
        emit get2end(true);
    }
    //file = "D:\testsrc\day0812\build-AnImageBrowser-桌面-Debug\0a4cd7.jpg";
    pixmap = QPixmap(file);
    QStringList::const_iterator itmp = list.begin();
    for (; itmp != list.end(); ++itmp)
        if (filepath.absoluteFilePath((*itmp)) == file)
        {//absoluteFilePath函数,返回目录中的文件的绝对路径名
            iterator = itmp;
            break;
        }
    FirstTimeShowFlag = true;
    update();//重绘图形
}

void ShowImage::show_next()
{
    ++iterator;
    if(iterator+1 > list.end())
        iterator = list.begin();
    pixmap = QPixmap(filepath.absoluteFilePath((*iterator)));
    wscale = 1.0;
    hscale = 1.0;
    emit turn2default(100);
    FirstTimeShowFlag = true;
    update();//重绘图形
}

void ShowImage::show_prev()
{
    if(iterator == list.begin())
        iterator = list.end();
    --iterator;
    pixmap = QPixmap(filepath.absoluteFilePath((*iterator)));
    wscale = 1.0;
    hscale = 1.0;
    emit turn2default(100);
    FirstTimeShowFlag = true;
    update();//重绘图形
}

//图片缩放
void ShowImage::arise_scale(int rate)
{
    wscale = static_cast<double>(rate)/100.0;
    hscale = wscale;
    update();//重绘图形
}


//利用QPainter绘图
void ShowImage::paintEvent(QPaintEvent * /*event*/)
{
    double pixwidth = static_cast<double>(pixmap.width());
    double pixheight = static_cast<double>(pixmap.height());
    double showwidth = static_cast<double>(width());
    double showheight = static_cast<double>(height());

    double Wscalerate = pixwidth / showwidth;
    double Hscalerate = pixheight / showheight;
    double compare = (Wscalerate > Hscalerate ? Wscalerate : Hscalerate);

    //定义平面矩形QRect ( int x, int y, int width, int height )
    QRect rect(showwidth/2.0 - pixwidth/compare/2.0,
               showheight/2.0 - pixheight/compare/2.0,
               pixwidth/compare,
               pixheight/compare);
    QRect midrect(
          (showwidth/2.0-pixwidth/2.0),
          (showheight/2.0-pixheight/2.0),
          pixwidth,
          pixheight);
    QPainter painter(this);

    painter.save();

    if(true == FirstTimeShowFlag)
    {//初次显示，坐标系统原点在图片中心点
        painter.translate(showwidth/2.0, (showheight/2.0));
        //转换坐标系统，通过给定的偏移，即给定的偏移量添加点
        painter.scale(wscale, hscale);
        painter.translate(-(showwidth/2), -(showheight/2.0));
    }
    else
    {//鼠标抓取移动后，坐标系统原点在鼠标位置
        painter.translate(x,y);
        painter.scale(wscale, hscale);
        painter.translate(-x,-y);
    }

//    //例
//    QRectF target(10.0, 20.0, 80.0, 60.0);
//    QRectF source(0.0, 0.0, 70.0, 40.0);
//    QPixmap pixmap(":myPixmap.png");
//    QPainter(this);
//    painter.drawPixmap(target, image, source);

    if (compare < 1.0)
        painter.drawPixmap(midrect, pixmap);
    else
        painter.drawPixmap(rect, pixmap);
    painter.restore();
    //恢复当前的画家状态（从栈中弹出一个保存状态）
}

void ShowImage::mouseMoveEvent(QMouseEvent *event)
{
    x = event->x();
    y = event->y();
    FirstTimeShowFlag = false;
    update();//重绘图形
}

//void ShowImage::wheelEvent(QWheelEvent *event)
//{
//    QString str;
//    switch(event->orientation())//返回滚轮方向:水平或垂直
//    {
//    case Qt::Horizontal:
//        str = "Horizontal Whell Move";
//        break;
//    case Qt::Vertical:
//        str = "Vertical Whell Move";
//        break;
//    default:
//        break;
//    }
//    str += "\n";
//    str += "    ";
//    if(event->delta()>0)//返回滚动距离
//        str += "go ahead";
//    else
//        str += "go back";
//    qDebug()<<str;
//}
