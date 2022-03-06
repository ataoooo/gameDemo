#include "gamebutton.h"

GameButton::GameButton(QWidget *parent) : QPushButton(parent)
{
    time=new QTimer(this);
}

GameButton::GameButton(QString btnpath):min(1),max(8),doing(false)
{
    time=new QTimer(this);
    QPixmap pix;
    bool flag=pix.load(btnpath);
    if(!flag)
    {
        QMessageBox::critical(this,"错误","加载图片失败！");
        return;
    }
    this->setFixedSize(pix.size());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(pix.size());

    //设置信号槽
    connect(time,&QTimer::timeout,[=](){
        if(this->face)//表示从反面翻到正面
        {
            QString s=QString(":/res/Coin000%1.png").arg(max--);
            QPixmap cpix;
            cpix.load(s);
            //覆盖图案
            this->setIcon(cpix);
            this->setIconSize(cpix.size());
            if(max<min)//翻转到头就停止
            {
                max=8;
                doing=false;//过程结束
                this->time->stop();
            }
        }
        else//表示从正面翻到反面
        {
            QString s=QString(":/res/Coin000%1.png").arg(min++);
            QPixmap cpix;
            cpix.load(s);
            this->setIcon(cpix);
            this->setIconSize(cpix.size());
            if(max<min)//翻转到头就停止
            {
                min=1;
                doing=false;//过程结束
                this->time->stop();
            }
        }
    });
}

void GameButton::ChangeStatus()
{
    if(doing) return;
    //变化状态
    doing=true;
    if(this->face)  this->face=false;
    else this->face=true;

    time->start(30);//30秒触发一次
}
