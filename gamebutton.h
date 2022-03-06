#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H
#include<QDebug>
#include <QPushButton>
#include <QPixmap>
#include <QMessageBox>
#include <QTimer>
class GameButton : public QPushButton
{
    Q_OBJECT
public:
    explicit GameButton(QWidget *parent = nullptr);
    GameButton(QString btnpath);
    int pos_x;
    int pos_y;
    bool face;

    //改变状态
    void ChangeStatus();

    //定时器
    QTimer *time;

    //开始和最终状态
    int min;
    int max;

    bool doing;//记录是否在翻转

signals:

};

#endif // GAMEBUTTON_H
