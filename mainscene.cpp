#include "mainscene.h"
#include "ui_mainscene.h"

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    //设置音效
    sound=new QSound(":/res/TapButtonSound.wav",this);
    sound2=new QSound(":/res/BackButtonSound.wav",this);

    ui->setupUi(this);
    //配置主场景
    this->setFixedSize(320,388);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币小游戏");
    //退出按钮的连接
    connect(ui->actionquit,&QAction::triggered,this,&QWidget::close);

    //设置开始按钮
    MyPushButton *startbutton=new MyPushButton(":/res/MenuSceneStartButton.png");
    startbutton->setParent(this);
    startbutton->move(this->width()*0.5-startbutton->width()*0.5,this->height()-startbutton->height());

    //设置进入的场景
    enterscene=new Enter;
    //监听按下开始按钮后的信号
    connect(startbutton,&MyPushButton::clicked,[=](){
        enterscene->setGeometry(this->geometry());//使新窗口的矩形框一致
        sound->play();//开始音效
        //弹跳特效
        startbutton->Special1();//先上
        startbutton->Special2();//后下

        //延时进入到选择关卡中
        //参数1：延时多少毫秒；参数2：谁；参数3：触发什么函数
        QTimer::singleShot(300,this,[=](){
            //进入到选择关卡的场景中
            //隐藏自身
            this->hide();
            //展现新场景
            enterscene->show();
        });
    });
    connect(enterscene,&Enter::ReturnMainScene,[=](){
        this->setGeometry(enterscene->geometry());
        sound2->play();
        enterscene->hide();//隐藏选择场景
        this->show();//展示当前场景
    });
}


//设置背景
void MainScene::paintEvent(QPaintEvent *)
{
    //加上窗口左上小标
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/res/PlayLevelSceneBg.png");
    pixmap=pixmap.scaled(pixmap.width()*0.9,pixmap.height()*0.9);
    painter.drawPixmap(0,0,pixmap);

    //加上背景上的图标
    pixmap.load(":/res/Title.png");
    //调整比列
    pixmap=pixmap.scaled(pixmap.width()*0.5,pixmap.height()*0.5);
    painter.drawPixmap(10,30,pixmap);
}
MainScene::~MainScene()
{
    delete ui;
}

