#include "mypushbutton.h"

MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent){}

//nomal为无操作时的状态，press为按下时的状态
MyPushButton::MyPushButton(QString nomal,QString press):nomalPath(nomal),pressPath(press)
{
    QPixmap pix;
    bool flag=pix.load(nomal);
    if(!flag)
    {
        QMessageBox::critical(this,"错误","图片加载失败！");
        return;
    }
    //重置图片的大小
    pix=pix.scaled(pix.width()*0.8,pix.height()*0.8);
    //设置按钮的大小
    this->setFixedSize(pix.width(),pix.height());

    //不规则图片的样式,将边框设为0像素，即淡化按钮的样式，使它能应藏在图案下
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标就是按钮上的图案
    this->setIcon(pix);

    //设置图案置于按钮上的大小（即要把图案覆盖到按钮上）
    this->setIconSize(QSize(pix.width(),pix.height()));
}

void MyPushButton::Special1()
{
    //设置特效，参数1：为什么设置特效（当前对象）2.设置什么样的特效，可查询
    QPropertyAnimation *an=new QPropertyAnimation(this,"geometry");
    //设置动画的时间间隔，单位毫秒
    an->setDuration(200);
    //起始位置
    an->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置,需要向下挪动10
    an->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置弹跳曲线，可查询
    an->setEasingCurve(QEasingCurve::OutBounce);
    //执行动画
    an->start();
}

void MyPushButton::Special2()
{
    QPropertyAnimation *an=new QPropertyAnimation(this,"geometry");
    an->setDuration(200);
    an->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    an->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    an->setEasingCurve(QEasingCurve::OutBounce);
    an->start();
}

void MyPushButton::mousePressEvent(QMouseEvent *event)
{
    if(this->pressPath!="")//按下时传了图案
    {
        QPixmap pix;
        bool flag=pix.load(this->pressPath);
        if(!flag)
        {
            QMessageBox::critical(this,"错误","图片加载失败");
            return;
        }
        pix.scaled(pix.width()*0.8,pix.height()*0.8);
        this->setFixedSize(pix.size());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(pix.size());
    }
    return QPushButton::mousePressEvent(event);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(this->pressPath!="")
    {
        QPixmap pix;
        bool flag=pix.load(this->nomalPath);
        if(!flag)
        {
            QMessageBox::critical(this,"错误","图片加载失败!");
            return;
        }
        pix.scaled(pix.width()*0.8,pix.height()*0.8);
        this->setFixedSize(pix.size());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(pix.size());
    }
    return QPushButton::mouseReleaseEvent(event);
}
