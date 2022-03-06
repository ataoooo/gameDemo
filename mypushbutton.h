#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QString>
#include <QPainter>
#include <QMessageBox>
#include <QPropertyAnimation>//用作动画特效
class MyPushButton : public QPushButton
{
    Q_OBJECT
    //保存图片路径
    QString nomalPath;
    QString pressPath;
public:
    explicit MyPushButton(QWidget *parent = nullptr);
    MyPushButton(QString nomal,QString press="");
    void Special1();//弹跳特效向上跳
    void Special2();//向下跳
    //对按下和释放操作重载
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:

};
#endif // MYPUSHBUTTON_H
