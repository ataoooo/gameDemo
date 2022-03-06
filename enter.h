#ifndef ENTER_H
#define ENTER_H

#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QLabel>
#include <QString>
#include <QDebug>
#include <QSound>
#include "mypushbutton.h"
#include "playscene.h"
class Enter : public QMainWindow
{
    Q_OBJECT
    PlayScene * play=nullptr;
    void setButton();
    QSound *sound;
    QSound *sound2;
public:
    explicit Enter(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *);
signals:
    void ReturnMainScene();//返回主场景的信号

};

#endif // ENTER_H
