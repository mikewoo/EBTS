#include <QtGui>
//#include <QDebug>
//#include <QWheelEvent>
#include "widget.h"
#include "showimage.h"

Widget::Widget()
{
    prevButton = new QPushButton(tr("&Previous"));
    nextButton = new QPushButton(tr("&Next"));
    indexButton = new QPushButton(tr("&Choose Path"));//图片路径选择按钮
    checkBox = new QCheckBox(tr("幻灯片播放"));
    fileDialog = new QFileDialog(this,tr("Select the image"),tr("E:/images"),
                                 tr("Images (*.jpg *.png *.bmp *.gif)"));
    slider = new QSlider(Qt::Horizontal,this);//缩放滑动条
    label = new QLabel;
    showImage = new ShowImage;
    connect(showImage, SIGNAL(get2beg(bool)),
            prevButton, SLOT(setDisabled(bool)));
    connect(showImage, SIGNAL(get2end(bool)),
            nextButton, SLOT(setDisabled(bool)));
    connect(showImage, SIGNAL(get2beg(bool)),
            checkBox, SLOT(setDisabled(bool)));
    connect(showImage, SIGNAL(turn2default(int)),//缩放比例
            slider, SLOT(setValue(int)));

    connect(slider,SIGNAL(valueChanged(int)),
            this,SLOT(changelabel(int)));
    connect(slider,SIGNAL(valueChanged(int)),
            this,SLOT(scalethepix(int)));
    connect(indexButton,SIGNAL(clicked()),
            fileDialog,SLOT(show()));
    connect(fileDialog,SIGNAL(fileSelected(QString)),
            this,SLOT(dirChanged(QString)));
    connect(prevButton,SIGNAL(clicked()),
            this,SLOT(turn2prev()));
    connect(nextButton,SIGNAL(clicked()),
            this,SLOT(turn2next()));
    connect(checkBox,SIGNAL(toggled(bool)),
            this,SLOT(ChangeAutoPlayFlag(bool)));

    //set layout
    QGridLayout *windowLayout = new QGridLayout;
    QHBoxLayout *labelLayout = new QHBoxLayout;

    labelLayout->addWidget(slider);
    labelLayout->addWidget(label);//label显示百分之几
    label->setBuddy(slider);

    //设置纵向伸展因子
    windowLayout->setColumnStretch(0,1);
    windowLayout->setColumnStretch(1,2);
    windowLayout->setColumnStretch(2,2);
    windowLayout->setColumnStretch(3,2);
    windowLayout->setColumnStretch(4,2);

    //windowLayout->addWidget();
    windowLayout->addWidget(showImage, 0, 0, 1, 9);//放置在0行0列位置
    windowLayout->setRowMinimumHeight(1,6);//在第1行设最小行距，单位为像素
    windowLayout->addWidget(indexButton, 2, 0, Qt::AlignLeft);
    windowLayout->addWidget(prevButton,2,2,Qt::AlignRight);//放置在2行1列位置，右对齐
    windowLayout->addWidget(nextButton, 2, 3, Qt::AlignLeft);
    windowLayout->addLayout(labelLayout, 2, 4, Qt::AlignRight);
    windowLayout->addWidget(checkBox, 2, 1, Qt::AlignLeft);
//    label1 = new QLabel;
//    label1->setText(tr("Read"));
//    windowLayout->addWidget(label1, 2, 5, Qt::AlignLeft);

    setLayout(windowLayout);

    fileDialog->resize(450,300);//设置对话框大小

    //set the Tab order
    setTabOrder(nextButton,prevButton);
    nextButton->setDefault(true);

    prevButton->setShortcut(QKeySequence(Qt::Key_Left));//设置快捷键
    nextButton->setShortcut(QKeySequence(Qt::Key_Right));

    slider->setRange(0,500);
    slider->setValue(100);
    prevButton->setDisabled(true);
    nextButton->setDisabled(true);
    checkBox->setDisabled(true);

    //set window name
    setWindowTitle(tr("图片浏览器"));//可执行程序标题
    setWindowIcon(QIcon(":/icons/qt-logo.png"));//可执行程序图标

    AutoPlayFlag = false;
    QTimer *timer = new QTimer(this);//新建定时器
    connect(timer,SIGNAL(timeout()),this,SLOT(AutoPlay()));
    //关联定时器计满信号和相应的槽函数
    timer->start(5000);//定时器开始计时，1秒

//    this->setMouseTracking(true);//启用widget的鼠标跟踪
}

Widget::~Widget()
{
    delete showImage;
}

void Widget::turn2next()
{
    showImage->show_next();
}

void Widget::turn2prev()
{
    showImage->show_prev();;
}

void Widget::dirChanged(QString newfile)
{
    showImage->init_path((fileDialog->directory()), newfile);
}

void Widget::scalethepix(int scale)
{
    showImage->arise_scale(scale);
}

//跟随缩放滑动条显示百分之几
void Widget::changelabel(int val)
{
    QString tmp;
    tmp.setNum(val);
    tmp += "%";
    label->setText(tmp);
}

void Widget::AutoPlay()
{
    if(AutoPlayFlag == true)
        showImage->show_next();
}

void Widget::ChangeAutoPlayFlag(bool flag)
{
    AutoPlayFlag = flag;
}

void Widget::wheelEvent(QWheelEvent *event)
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
    int numSteps = numDegrees / 15;//1度
    int value = slider->value();
    slider->setValue(value+numDegrees);

}
