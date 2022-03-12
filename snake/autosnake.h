#ifndef AUTOSANKE_H
#define AUTOSANKE_H

#include<QRect>
#include<qpainter.h>
#include<QTimer>
class autosnake{

private:
    QVector<QRect> vSnakeRect; //蛇
    QRect SnakeHead; //蛇头
    QTimer *timer; //定时器
    //int length;   //定义蛇身长度
    int nDirection;  //定义蛇头方向
    int x;
    int y;

public:
    autosnake();   //初始化长度
    bool IsEat(QVector<QRect>,bool,int);
//    bool IsHit();    //包括撞到障碍物和墙体
    QRect createRect(int);
    void setX(int);
    void setY(int);  //设置初始化位置
    int getX();
    int getY();
    void setDirection(int);
    int getDirection();
    void setSnakeSize(int);
    int getSnakeSize();
    QVector<QRect> getSnake();
    void setSnakeHead(QRect);
    QRect getSnakeHead();
    QRect getSnakeIndex(int);
    void setSnakeIndex(int,QRect);
    void setHeadTop(int);
    void setHeadBottom(int);
    void setHeadLeft(int);
    void setHeadRight(int);
    void setSnakeLast(QRect);

};



#endif // AUTOSANKE_H
