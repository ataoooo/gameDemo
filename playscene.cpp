#include "playscene.h"

PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent){}
PlayScene::PlayScene(int i)//i从1开始
{
    level=i;
    //布置场景
    QString s=QString("第%1关").arg(i);
    //设置标题
    this->setWindowTitle(s);
    //设置图标
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置大小
    this->setFixedSize(320,388);

    setButton();//返回按钮

    sound1=new QSound(":/res/ConFlipSound.wav",this);//翻金币音效
    sound2=new QSound(":/res/LevelWinSound.wav",this);//胜利的音效

    //sound1->setLoops(n);循环的次数，-1为无限循环

    //设置菜单栏即退出效果
    QMenuBar *bar=menuBar();
    QMenu *menu=bar->addMenu("开始");
    QAction *action=menu->addAction("退出");
    connect(action,&QAction::triggered,this,&QWidget::close);

    //显示当前关卡数
    QLabel * label = new QLabel(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1 = QString("Level: %1").arg(i);
    //将字体设置到标签控件中
    label->setFont(font);//设置字体
    label->setText( str1);//写字
    label->setGeometry(30, this->height() - 50,120, 50);//一个矩形框

    //初始化游戏数组
    for(int r=0;r<4;++r)
    {
        for(int c=0;c<4;++c)
        {
            gamearry[r][c]=data.mData[i][r][c];
        }
    }
    //设置游戏场景
    for(int i=0;i<4;++i)
    {
        for(int j=0;j<4;++j)
        {
            //判断图片为金币还是银币
            if(gamearry[i][j]==1)
                path=QString(":/res/Coin0001.png");
            else
                path=QString(":/res/Coin0008.png");
            QPixmap pix(":/res/BoardNode.png");
            QLabel *lab=new QLabel;
            lab->setParent(this);
            lab->setGeometry(0,0,pix.width(),pix.height());
            lab->setPixmap(pix);
            lab->move(70+i*50,100+j*50);

            GameButton *gbtn=new GameButton(path);
            gbtn->setParent(this);
            gbtn->move(72.5+i*50,102.5+j*50);

            //设置金币按钮属性
            gbtn->pos_x=i;
            gbtn->pos_y=j;
            gbtn->face=gamearry[i][j];

            btnarry[i][j]=gbtn;//存储按钮

            //设置胜利的图标
            QPixmap mp(":/res/LevelCompletedDialogBg.png");
            slabel=new QLabel(this);
            slabel->setFixedSize(mp.size());
            slabel->setPixmap(mp);
            //隐藏起来胜利图标
            slabel->move((this->width()-mp.width())*0.5,-mp.height());

            connect(gbtn,&QPushButton::clicked,[=](){
                if(success||donot) return;
                donot=true;//能够设置到其他按钮禁用
                gbtn->ChangeStatus();
                sound1->play();
                //周围的要延时翻转
                QTimer::singleShot(300,this,[=](){
                    this->gamearry[gbtn->pos_x][gbtn->pos_y]=!this->gamearry[i][j];
                    if(gbtn->pos_x+1<4) changearry(btnarry[gbtn->pos_x+1][gbtn->pos_y]);
                    if(gbtn->pos_y+1<4) changearry(btnarry[gbtn->pos_x][gbtn->pos_y+1]);
                    if(gbtn->pos_x-1>=0) changearry(btnarry[gbtn->pos_x-1][gbtn->pos_y]);
                    if(gbtn->pos_y-1>=0) changearry(btnarry[gbtn->pos_x][gbtn->pos_y-1]);
                    isSuccess();//需要再次判断是否成功引起success的变化
                    if(success)
                    {
                        sound2->play();
                        GetSuccess();
                    }
                });
                QTimer::singleShot(800,this,[=](){//延时，可以等到全部金币反转过后再置false
                    donot=false;
                });
            });
        }
    }
}

void PlayScene::setButton()
{
    //设置返回按钮
    MyPushButton *btn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    btn->setParent(this);
    btn->move(this->width()-btn->width(),this->height()-btn->height());
    connect(btn,&MyPushButton::clicked,[=](){
            this->ReturnEnter();//发出返回信号
    });
}

bool PlayScene::isSuccess()
{
    for(int i=0;i<4;++i)
    {
        for(int j=0;j<4;++j)
        {
            if(!gamearry[i][j]) return false;
        }
    }
    success=true;
    return true;
}

void PlayScene::changearry(GameButton* &btn)
{
    btn->ChangeStatus();
    //改变状态
    gamearry[btn->pos_x][btn->pos_y]=!gamearry[btn->pos_x][btn->pos_y];
}

//布置背景
void PlayScene::paintEvent(QPaintEvent *)
{
    //大背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,pix);

    //小装饰
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix);
 }

//胜利图标展示
void PlayScene::GetSuccess()
{
    QPropertyAnimation *admi=new QPropertyAnimation(slabel,"geometry",this);
    //设置时间间隔1s
    admi->setDuration(1000);
    //设置开始位置
    admi->setStartValue(QRect(slabel->x(),slabel->y(),slabel->width(),slabel->height()));
    //设置结束为止
    admi->setEndValue(QRect(slabel->x(),slabel->y()+250,slabel->width(),slabel->height()));
    //设置运动曲线
    admi->setEasingCurve(QEasingCurve::OutBounce);
    //动起来
    admi->start();
}
