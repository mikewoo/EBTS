#include <QtGui>
#include <QMouseEvent>
#include "showimage.h"

ShowImage::ShowImage(QWidget *parent)
    :QWidget(parent),wscale(1.0),hscale(1.0)
{
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

void ShowImage::init_path(QString file)
{
    //file = "./kg.png";

    pixmap = QPixmap(file);

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


