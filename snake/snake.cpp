#include "snake.h"
#include "start.h"
#include "autosnake.h"
#include "ui_snake.h"
#include<qtimer.h>
#include<QKeyEvent>
#include<qrect.h>
#include<qdebug.h>
#include<QFont>
#include<QPixmap>
#include <qglobal.h>

#define ge_width 10 //定义格子大小


bool isRun = false;
int t = 0;
snake::snake(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::snake),blsRun(false),speed(100)
{
    ui->setupUi(this);
    this->setGeometry(QRect(600,300,580,620));
    start *s=new start();
    //s->setFixedSize(200,300);
    s->setWindowModality(Qt::ApplicationModal);
    s->show();
    setFocusPolicy(Qt::StrongFocus);
}

snake::~snake()
{
    delete ui;
}

void snake::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    if(isRun){
        InitSnake();   //初始化蛇
        InitFood();  //初始化食物
        blsRun = true;
        isRun = false;
    }
    if(blsRun){
        drawBK();
        drawSnake(snake1,true);
        for(int i =0;i<snakes.size();i++){
            drawSnake(snakes[i],false);
        }
    }

}

void snake::drawBK(){
    QPainter painter(this);
    //画游戏背景
    painter.setPen(Qt::black);  //设置画笔颜色
    painter.setBrush(Qt::gray); //设置填充颜色
    painter.drawRect(30,30,520,520);
    //内墙
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawRect(40,40,500,500);
    painter.drawPixmap(40,40,500,500,QPixmap(":/myImage/img/bk01.png"));

    //画小格子
    QColor blue20 = Qt::blue;
    //设置透明度
    blue20.setAlpha(10);
    painter.setPen(blue20);
    for(int i =2 ; i < 102 ; i++){
        painter.drawLine(40,i*ge_width,540,i*ge_width);  //画横线
        painter.drawLine(i*ge_width,40,i*ge_width,540);  //画竖线
    }
    //显示游戏开始结束
    QFont font1("Courier",2);
    painter.setFont(font1);
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    painter.drawText(40,150,sDisplay);

    painter.setPen(Qt::black);  //设置画笔颜色
    painter.setBrush(Qt::green);
    //painter.drawRect(food);
    //画食物
    for(int i =0;i<food.size();i++){
        painter.drawPixmap(food[i],QPixmap(":/myImage/img/food.png"));
    }
    if(isOIPShow)
        painter.drawPixmap(OIP,QPixmap(":/myImage/img/OIP.jpg"));
    //painter.drawRects(&vSnakeRect[0],vSnakeRect.size());  //画n个小方块
    //painter.drawPixmap(20,20,250,250,QPixmap(":/myImage/img/bk.png"));
//    drawSnake(snake1);

    //得分
    QFont font2("Courier",15);
    painter.setFont(font2);
    painter.setPen(Qt::blue);
    painter.setBrush(Qt::blue);
    painter.drawText(280,600,scoreLabel);
    painter.drawText(460,600,QString::number(nScore));
    if(blsOver){
        timer->stop();
    }
}

void snake::drawSnake(autosnake s,bool is_player){
    QPainter painter(this);
    //画蛇
    if(is_player){
        for(int i = 1; i < s.getSnakeSize();i++){
            painter.drawPixmap(s.getSnakeIndex(i),QPixmap(":/myImage/img/snake_body.png"));
        }
        switch(s.getDirection()){
        case 1:
            painter.drawPixmap(s.getSnakeIndex(0),QPixmap(":/myImage/img/head_up.png"));
            break;
        case 2:
            painter.drawPixmap(s.getSnakeIndex(0),QPixmap(":/myImage/img/head_down.jpg"));
            break;
        case 3:
            painter.drawPixmap(s.getSnakeIndex(0),QPixmap(":/myImage/img/head_left.jpg"));
            break;
        case 4:
            painter.drawPixmap(s.getSnakeIndex(0),QPixmap(":/myImage/img/head_right.jpg"));
            break;
        default:;
        }
    }else{
        for(int i = 1; i < s.getSnakeSize();i++){
            painter.drawPixmap(s.getSnakeIndex(i),QPixmap(":/myImage/img/snake_body1.png"));
        }
        switch(s.getDirection()){
        case 1:
            painter.drawPixmap(s.getSnakeIndex(0),QPixmap(":/myImage/img/head_up1.png"));
            break;
        case 2:
            painter.drawPixmap(s.getSnakeIndex(0),QPixmap(":/myImage/img/head_down1.jpg"));
            break;
        case 3:
            painter.drawPixmap(s.getSnakeIndex(0),QPixmap(":/myImage/img/head_left1.jpg"));
            break;
        case 4:
            painter.drawPixmap(s.getSnakeIndex(0),QPixmap(":/myImage/img/head_right1.jpg"));
            break;
        default:;
        }
    }


}

//初始化食物
void snake::InitFood(){
    food.resize(100);
    for(int i =0; i < food.size();i++)
       food[i] = CreateRect();

}

void snake::InitSnake(){
    snake1.setDirection(2);  //默认向下的方向
//    nDirection =2;//默认向下运动
    //blsRun = true;
    blsOver = false;
    //food = CreateRect();
    OIP = CreateRect();   //新建磁铁
    isOIPShow =true;
    isOIPUse = false;
    OIP_time = 0;
    sDisplay="游戏开始";
    scoreLabel="得分";
    nScore = 0;
    //QRect rect(100,70,10,10); //蛇的初始化位置
    //vSnakeRect = rect;
//    vSnakeRect.resize(5);
    snake1.setSnakeSize(5);
    for(int i =0 ; i < snake1.getSnakeSize();i++){
        QRect rect(200,140+ge_width*i,ge_width,ge_width);
        snake1.setSnakeIndex(snake1.getSnakeSize()-1-i,rect);
//        snake1.getSnake()[snake1.getSnakeSize()-1-i] = rect;
//        vSnakeRect[vSnakeRect.size()-1-i] = rect;
    }
    snake1.setSnakeHead(snake1.getSnake().first());
//    SnakeHead=vSnakeRect.first();

    //初始化人机蛇
    snakes.resize(4);   //设置人机蛇的条数
    for(int i = 0 ; i < snakes.size(); i++){
        snakes[i].setDirection(qrand()%4 +1);
        snakes[i].setSnakeSize(5);
        for(int j =0 ; j < snakes[i].getSnakeSize();j++){
            QRect rect(300-i*30,150+ge_width*j+30*i,ge_width,ge_width);
            snakes[i].setSnakeIndex(snakes[i].getSnakeSize()-1-j,rect);
        }
        snakes[i].setSnakeHead(snakes[i].getSnake().first());
    }

    timer = new QTimer(this);
    timer->start(speed);    //
    connect(timer,SIGNAL(timeout()),SLOT(Snake_update()));
}
void snake::keyPressEvent(QKeyEvent *event){
    QKeyEvent *key =(QKeyEvent*)event;
    switch(key->key()){
    case Qt::Key_Up:snake1.setDirection(1); //上
        break;
    case Qt::Key_Down:snake1.setDirection(2); //下
        break;
    case Qt::Key_Left:snake1.setDirection(3);  //左
        break;
    case Qt::Key_Right:snake1.setDirection(4); //右
        break;
    case Qt::Key_Space:speed /= 2;
        break;
    default:;
    }
}
void snake::keyReleaseEvent(QKeyEvent *event){
    QKeyEvent *key =(QKeyEvent*)event;
    switch (key->key()) {
    case Qt::Key_Space:speed*=2;
        break;
    default:;
    }

}

void snake::Snake_update(){
    sDisplay = "";

    //更新玩家蛇
    snake1 = update_index(snake1,true);

    if(OIP_time>=0)
        OIP_time--;
    //qDebug()<<OIP_time;

    //更新人机蛇
    t++;
    for(int i = 0; i<snakes.size();i++){
        if(t%10==0){
            if(snakes[i].getSnakeHead().left()<=50){
                snakes[i].setDirection(4);
            }else if(snakes[i].getSnakeHead().right()>=530){
                snakes[i].setDirection(3);
            }else if(snakes[i].getSnakeHead().top()<=30){
                snakes[i].setDirection(2);
            }else if(snakes[i].getSnakeHead().bottom()>=530){
                snakes[i].setDirection(1);
            }else{
                snakes[i].setDirection(qrand()%4+1);   //设置随机方向
            }
        }

        snakes[i] = update_index(snakes[i],false);
    }

    update();
}


autosnake snake::update_index(autosnake s,bool is_player){

    s.setSnakeHead(s.getSnake().first());
    s= IsEat(s);
    s= IsHit(s,is_player);


    for(int j = 0; j < s.getSnakeSize()-1;j++){
        s.setSnakeIndex(s.getSnakeSize()-1-j,s.getSnakeIndex(s.getSnakeSize()-2-j));
    }

    switch (s.getDirection()) {
    case 1://上
        s.setHeadTop(s.getSnakeHead().top()-ge_width);
        s.setHeadBottom(s.getSnakeHead().bottom()-ge_width);
        break;
    case 2://下
        s.setHeadTop(s.getSnakeHead().top()+ge_width);
        s.setHeadBottom(s.getSnakeHead().bottom()+ge_width);
        break;
    case 3: //左
        s.setHeadLeft(s.getSnakeHead().left()-ge_width);
        s.setHeadRight(s.getSnakeHead().right()-ge_width);
        break;
    case 4: //右
        s.setHeadLeft(s.getSnakeHead().left()+ge_width);
        s.setHeadRight(s.getSnakeHead().right()+ge_width);
        break;
    default:;
    }
    s.setSnakeIndex(0,s.getSnakeHead());  //第一个节点设置位蛇头位置
    if(s.getSnakeHead().left()<40||s.getSnakeHead().right()>540||s.getSnakeHead().top()<40||s.getSnakeHead().bottom()>540){
        if(is_player){
            sDisplay = "游戏结束";
            blsOver=true;
        }
    }
    return s;

}

QRect snake::CreateRect(){
    int x,y;
    x = qrand()%(500/ge_width);
    y = qrand()%(500/ge_width);
    QRect rect(40+x*ge_width,40+y*ge_width,ge_width,ge_width);  //食物的位置
    return rect;
}

autosnake snake::CreateSnake(){
    autosnake s;
    s.setDirection(qrand()%4 +1);
    s.setSnakeSize(5);
    for(int i =0 ; i < s.getSnakeSize();i++){
        QRect rect(200,140+ge_width*i,ge_width,ge_width);
        s.setSnakeIndex(s.getSnakeSize()-1-i,rect);
    }
    return s;
}

autosnake snake::IsEat(autosnake s){
    for(int i =0; i<food.size();i++){
    if(isOIPUse){
        //qDebug()<<SnakeHead.top()<<food.bottom()<<speed<<endl;  调试bug
        if((s.getSnakeHead().top()== food[i].bottom()+1&&s.getSnakeHead().left()==food[i].left())||(s.getSnakeHead().bottom()+1==food[i].top()&&s.getSnakeHead().left()==food[i].left())
                ||(s.getSnakeHead().left()==food[i].right()+1&&s.getSnakeHead().top()==food[i].top())||(s.getSnakeHead().right()+1==food[i].left()&&s.getSnakeHead().top()==food[i].top())
                ||s.getSnakeHead() == food[i]){

            s.setSnakeHead(s.getSnakeHead());  //吃到食物，食物变为蛇头
            s.setSnakeLast(s.getSnake().last()); //将新的放入
//            s.getSnake().push_back(s.getSnake().last());
            //s.setSnakeSize(s.getSnakeSize()+1);
            food[i] = CreateRect();
            //nScore+=10;
        }
        //||SnakeHead.bottom()==food.top()||SnakeHead.left()==food.right()||SnakeHead.right()==food.left()||SnakeHead == food
    }
    else if(s.getSnakeHead() == food[i]){
        s.setSnakeHead(food[i]);  //吃到食物，食物变为蛇头
        s.setSnakeLast(s.getSnake().last()); //将新的放入
        //s.setSnakeSize(s.getSnakeSize()+1);
        qDebug()<<s.getSnakeSize();
        food[i] = CreateRect();
        //nScore+=10;
    }
    }
    //如果吃到磁铁
    if(s.getSnakeHead() == OIP){
        s.getSnakeHead() = OIP;
        isOIPShow = false;
        isOIPUse = true;
        OIP_time = 100;
    }
    if(!isOIPShow && OIP_time <= 0){
        OIP = CreateRect();
        isOIPShow = true;
        isOIPUse = false;
    }
    return s;

}

autosnake snake::IsHit(autosnake s,bool is_player){

    if(is_player){
        for(int i=0; i <snakes.size();i++){
            for(int j = 0; j < snakes[i].getSnakeSize();j++){
                if(s.getSnakeHead()==snakes[i].getSnakeIndex(j)){
                    sDisplay = "游戏结束";
                    blsOver = true;
                    update();
                }
            }
        }
    }else{
        for(int i=0; i< snake1.getSnakeSize();i++){
            if(s.getSnakeHead()==snake1.getSnakeIndex(i)){
                snake1.setSnakeSize(snake1.getSnakeSize()+s.getSnakeSize());
                //s = CreateSnake();
                s.setSnakeSize(1);
                update();
            }
        }
    }
    return s;

}
