#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QString>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QLabel>
#include <QFont>
#include <QSound>
#include "dataconfig.h"
#include "mypushbutton.h"
#include "gamebutton.h"
#include <QPropertyAnimation>
class PlayScene : public QMainWindow
{
    Q_OBJECT
    int level;
    int gamearry[4][4];
    dataConfig data;
    QString path;
    GameButton* btnarry[4][4];//存放金币按钮
    void changearry(GameButton* &btn);//触发其他按钮的变化以及状态的改变
    bool isSuccess();//判断胜利
    void GetSuccess();//获得胜利后的反映
    QLabel *slabel;
    void setButton();
    bool success=false;
    bool donot=false;
    QSound *sound1;
    QSound *sound2;
public:
    explicit PlayScene(QWidget *parent = nullptr);
    PlayScene(int i);
    virtual void paintEvent(QPaintEvent *);
signals:
    void ReturnEnter();//返回的信号
};

#endif // PLAYSCENE_H
