#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QSound>
#include "mypushbutton.h"
#include "enter.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT
    QTimer *time;
    Enter *enterscene;//进入的场景
    QSound *sound;
    QSound *sound2;
public:
    MainScene(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *);
    ~MainScene();
private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
