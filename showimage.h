#ifndef SHOWIMAGE_H
#define SHOWIMAGE_H

#include <QPixmap>
#include <QWidget>
#include <QStringList>
#include <QDir>

class ShowImage : public QWidget
{
    Q_OBJECT

public:
    ShowImage(QWidget *parent = 0);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

signals:
    void get2end(bool);
    void get2beg(bool);
    void turn2default(int);//缩放比例

public slots:
    void init_path(QDir,QString);
    void show_next(void);//查看下一张
    void show_prev(void);//查看上一张
    void arise_scale(int);//图片缩放

protected:
    void paintEvent(QPaintEvent *event);//利用QPainter绘图
//    void wheelEvent(QWheelEvent *event);//鼠标滚轮移动
    void mouseMoveEvent(QMouseEvent *);

private:
    QStringList::const_iterator iterator;//常量迭代器
    QStringList list;
    QDir filepath;
    QPixmap pixmap;//“绘图设备”
    double wscale;
    double hscale;
    volatile int x;
    volatile int y;
    bool FirstTimeShowFlag;
};

#endif // SHOWIMAGE_H
