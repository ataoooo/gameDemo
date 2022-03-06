#include "enter.h"
Enter::Enter(QWidget *parent) : QMainWindow(parent)
{
    //配置场景
    this->setFixedSize(320,388);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("关卡选择");
    QMenuBar *bar=menuBar();
    setMenuBar(bar);
    QMenu *act=bar->addMenu("开始");
    QAction *a=act->addAction("关闭");
    connect(a,&QAction::triggered,[=](){
        this->close();
    });


    //设置音效
    sound=new QSound(":/res/TapButtonSound.wav");
    sound2=new QSound(":/res/BackButtonSound.wav");
    setButton();

    //中心关卡布局
    for(int i=0;i<20;++i)//二十个关卡按钮
    {
        MyPushButton *btn=new MyPushButton(":/res/LevelIcon.png");
        btn->setParent(this);
        btn->move(50+i%4*60,100+i/4*50);//布置按钮的位置
        //第一种设置标签方式
        QLabel *lab=new QLabel(btn);//用于放置按钮上的数字
        lab->setFixedSize(btn->width(),btn->height());//设置按钮大小
        lab->setText(QString::number(i+1));
        lab->setAlignment(Qt::AlignCenter);//设置字体居中

        connect(btn,&QPushButton::clicked,[=](){
            sound->play();
           QTimer::singleShot(100,this,[=](){
               this->hide();
               play=new PlayScene(i+1);//每按一次按钮就会新建一个窗口
               play->setGeometry(this->geometry());//设置矩形框使窗口不随意移动
               play->show();
               //设置接收到游戏界面返回信号后删除界面
               connect(play,&PlayScene::ReturnEnter,[=](){
                   this->setGeometry(play->geometry());//设置返回窗口的矩形框：使得窗口不到处移动
                   sound2->play();
                   delete play;//每返回一次就删除一次窗口，局部变量必须嵌套在这里
                   play=nullptr;
                   this->show();
               });
           });
        });


        //第二种设置标签的方式
//        QLabel *lab2=new QLabel(this);//不以按钮为父亲
//        lab2->setText(QString::number(i+1));//设置数字
//        lab2->setFixedSize(btn->size());//与按钮一样的大小
//        lab2->move(50+i%4*60,100+i/4*50);//移动标签的位置来覆盖按钮的位置
//        lab2->setAlignment(Qt::AlignCenter);//设置字体所在的位置：居中
//        lab2->setAttribute(Qt::WA_TransparentForMouseEvents);//设置让鼠标穿透,51属性
    }
}

//返回按钮设置
void Enter::setButton()
{
    //返回按钮
    MyPushButton * btn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    btn->setParent(this);
    btn->move(this->width()-btn->width(),this->height()-btn->height());
    //点击返回
    connect(btn,&QPushButton::clicked,[=](){
        QTimer::singleShot(200,this,[=](){
            this->ReturnMainScene();
        });
    });
}

void Enter::paintEvent(QPaintEvent *)
{
    //加载大背景
    QPainter p(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    pix=pix.scaled(pix.width()*0.85,pix.height()*0.85);
    p.drawPixmap(0,0,pix.width(),pix.height(),pix);

    //加载中心背景
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.8,pix.height()*0.8);
    p.drawPixmap((this->width()-pix.width())*0.5,30,pix);
}
