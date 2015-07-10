#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QWidget>
#include <QString>

QT_BEGIN_NAMESPACE
class QPushButton;
class QCheckBox;
class QFileDialog;
class QSlider;
class QLabel;
QT_END_NAMESPACE
class ShowImage;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget();
    ~Widget();

private:
    QPushButton *prevButton;
    QPushButton *nextButton;
    QPushButton *indexButton;//Í¼Æ¬Â·¾¶Ñ¡Ôñ°´Å¥
    QCheckBox *checkBox;
    QFileDialog *fileDialog;
    QSlider *slider;
    QLabel *label;

    ShowImage *showImage;
    bool AutoPlayFlag;

    QLabel *label1;

private slots:
    void turn2next();
    void turn2prev();
    void dirChanged(QString);
    void scalethepix(int);
    void changelabel(int);
    void AutoPlay();
    void ChangeAutoPlayFlag(bool);

protected:
    void wheelEvent(QWheelEvent *event);//Êó±ê¹öÂÖÒÆ¶¯
};

#endif // WIDGET_H
