#ifndef SNAKE_H
#define SNAKE_H

#include <QMainWindow>
#include<qpainter.h>
#include<qtimer.h>
#include<QKeyEvent>
#include<autosnake.h>

namespace Ui {
class snake;
}

class snake : public QMainWindow
{
    Q_OBJECT

public:
    explicit snake(QWidget *parent = nullptr);
    ~snake();
    void paintEvent(QPaintEvent *event);
    void InitSnake(); //初始化蛇
    void InitFood();   //初始化食物
    QRect CreateRect();
    autosnake IsEat(autosnake);
    autosnake IsHit(autosnake,bool);    //包括撞到障碍物和墙体
    void IsEatSkill();   //吃到磁铁
    void playOIP();   //磁铁开始作用
    void drawBK();  //画背景图像
    void drawSnake(autosnake,bool);  //画蛇
    autosnake update_index(autosnake,bool);
    autosnake CreateSnake();

private slots:
    void Snake_update();
    //void Food_update();   //食物进行更新

private:
    Ui::snake *ui;
    //QVector<QRect> vSnakeRect; //蛇
    autosnake snake1;  //生成一条长度为5的蛇
    QVector<autosnake> snakes;  //设置人机
    //QRect SnakeHead; //蛇头
    void keyPressEvent(QKeyEvent *event);   //键盘事件
    void keyReleaseEvent(QKeyEvent *event);
    QTimer *timer; //定时器
    bool blsRun; //是否开始
    bool blsOver;  //是否结束
    QString sDisplay; //开始结束提示
    //int nDirection;  //蛇移动的方向
    //QRect food;  //食物
    QVector<QRect> food; //将食物增多
    //QVector<QRect> food; //食物集合
    int nScore; //得分
    QString scoreLabel;  //显示得分
    int speed;  //速度
    QRect OIP;   //磁铁
    QTimer *timer_OIP;  //记录磁铁的时间
    bool isOIPShow;
    bool isOIPUse;   //磁铁是否开始作用
    int OIP_time;   //磁铁的作用时间

};




#endif // SNAKE_H
