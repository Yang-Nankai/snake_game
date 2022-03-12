#include<autosnake.h>
#include<snake.h>
#include<QDebug>

autosnake::autosnake(){
}


QRect autosnake::createRect(int ge_width){
    int x,y;
    x = qrand()%(500/ge_width);
    y = qrand()%(500/ge_width);
    QRect rect(40+x*ge_width,40+y*ge_width,ge_width,ge_width);  //食物的位置
    return rect;
}

bool autosnake::IsEat(QVector<QRect>food,bool isOIPUse,int ge_width){
    for(int i =0; i<food.size();i++){
    if(isOIPUse){
        //qDebug()<<SnakeHead.top()<<food.bottom()<<speed<<endl;  调试bug
        if((SnakeHead.top()== food[i].bottom()+1&&SnakeHead.left()==food[i].left())||(SnakeHead.bottom()+1==food[i].top()&&SnakeHead.left()==food[i].left())
                ||(SnakeHead.left()==food[i].right()+1&&SnakeHead.top()==food[i].top())||(SnakeHead.right()+1==food[i].left()&&SnakeHead.top()==food[i].top())
                ||SnakeHead == food[i]){

            SnakeHead = SnakeHead;  //吃到食物，食物变为蛇头
            vSnakeRect.push_back(vSnakeRect.last());
            food[i] = createRect(ge_width);
            //nScore+=10;
            return true;
        }
        //||SnakeHead.bottom()==food.top()||SnakeHead.left()==food.right()||SnakeHead.right()==food.left()||SnakeHead == food
    }
    else if(SnakeHead == food[i]){
        SnakeHead = food[i];  //吃到食物，食物变为蛇头
        vSnakeRect.push_back(vSnakeRect.last());
        food[i] = createRect(ge_width);
        //nScore+=10;
        return true;
    }
    }

}


//bool autosnake::IsHit(){
 //   for(int i = 1; i < vSnakeRect.size();i++){
 //       if(SnakeHead == vSnakeRect[i]){
//            sDisplay = "游戏结束";
//            blsOver = true;
//            update();
//            return true;
//        }
//    }
//    return false;
//}

void autosnake::setX(int xx){
    x = xx;
}
void autosnake::setY(int yy){
    y = yy;
}
int autosnake::getX(){
    return x;
}
int autosnake::getY(){
    return y;
}

void autosnake::setDirection(int direction){
    nDirection = direction;
}

int autosnake::getDirection(){
    return  nDirection;
}

void autosnake::setSnakeSize(int length){
    vSnakeRect.resize(length);
}
int autosnake::getSnakeSize(){
    return vSnakeRect.size();
}
QVector<QRect> autosnake::getSnake(){
    return vSnakeRect;
}
void autosnake::setSnakeHead(QRect rect){
    SnakeHead = rect;
}
QRect autosnake::getSnakeHead(){
    return SnakeHead;
}
QRect autosnake::getSnakeIndex(int i){
    return vSnakeRect[i];
}
void autosnake::setSnakeIndex(int i,QRect rect){
    vSnakeRect[i] = rect;
}

void autosnake::setHeadTop(int top){
    SnakeHead.setTop(top);
}

void autosnake::setHeadBottom(int bottom){
    SnakeHead.setBottom(bottom);
}

void autosnake::setHeadLeft(int left){
    SnakeHead.setLeft(left);
}

void autosnake::setHeadRight(int right){
    SnakeHead.setRight(right);
}

void autosnake::setSnakeLast(QRect rect){
    vSnakeRect.push_back(rect);
}



