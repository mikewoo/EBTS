#ifndef SHOWIMAGE_H
#define SHOWIMAGE_H

#include <QPixmap>
#include <QWidget>
#include <QStringList>

class ShowImage : public QWidget
{
    Q_OBJECT

public:
    ShowImage(QWidget *parent = 0);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;
    QString filename;

signals:
    void get2end(bool);
    void get2beg(bool);
    void turn2default(int);//缩放比例

public slots:
    void init_path(QString);
    void arise_scale(int);//图片缩放


protected:
    void paintEvent(QPaintEvent *event);//利用QPainter绘图
    void mouseMoveEvent(QMouseEvent *);

private:
    QStringList::const_iterator iterator;//常量迭代器
    QStringList list;
    QPixmap pixmap;//“绘图设备”
    double wscale;
    double hscale;
    volatile int x;
    volatile int y;
    bool FirstTimeShowFlag;
};

#endif // SHOWIMAGE_H
