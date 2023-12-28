#include "preshape.h"
#include "mainwindow.h"

//preshape
void Preshape::initTiles(QColor color){
    for(int i = 0; i < 4; i++){
        mytiles[i] = window->scene_main->addRect(QRect(0, 0, window->tileWidth, window->tileWidth), QPen(Qt::black, 2.4), QBrush(color));
    }
}
void Preshape::initArray(double start[4][2]){
    for(int i = 0; i < 4; i++){
        startPosition[i][0] = start[i][0];
        startPosition[i][1] = start[i][1];
    }
}
void Preshape::moveToStart(){
    int screenX=0, screenY=0;
    switch(state){
        case 0:
            screenX = window->sceneWidth + window->tileWidth*3;
            screenY = 0;
            break;
        case 1:
            screenX = -window->tileWidth*7.5;
            screenY = 0;
            break;
    }

    for(int i = 0; i < 4; i++){
        mytiles[i]->setPos(screenX + window->tileWidth*startPosition[i][0], screenY + window->tileWidth*startPosition[i][1]);
    }
}
void Preshape::deleteTiles(){
    for(int i = 0; i < 4; i++){
        delete(mytiles[i]);
    }
}

//I
Preshape_I::Preshape_I(MainWindow *window, int state){
    this->window = window;
    this->state = state;
    initTiles(blue);
    double start[4][2] = {{0.25, 1.75}, {1.25, 1.75}, {2.25, 1.75}, {3.25, 1.75}};
    initArray(start);
    moveToStart();
}

//J
Preshape_J::Preshape_J(MainWindow *window, int state){
    this->window = window;
    this->state = state;
    initTiles(darkBlue);
    double start[4][2] = {{0.75, 1.25}, {0.75, 2.25}, {1.75, 2.25}, {2.75, 2.25}};
    initArray(start);
    moveToStart();
}

//L
Preshape_L::Preshape_L(MainWindow *window, int state){
    this->window = window;
    this->state = state;
    initTiles(orange);
    double start[4][2] = {{2.75, 1.25}, {0.75, 2.25}, {1.75, 2.25}, {2.75, 2.25}};
    initArray(start);
    moveToStart();
}

//O
Preshape_O::Preshape_O(MainWindow *window, int state){
    this->window = window;
    this->state = state;
    initTiles(yellow);
    double start[4][2] = {{1.25, 1.25}, {2.25, 1.25}, {1.25, 2.25}, {2.25, 2.25}};

    initArray(start);
    moveToStart();
}

//S
Preshape_S::Preshape_S(MainWindow *window, int state){
    this->window = window;
    this->state = state;
    initTiles(green);
    double start[4][2] = {{1.75, 1.25}, {2.75, 1.25}, {0.75, 2.25}, {1.75, 2.25}};
    initArray(start);
    moveToStart();
}

//T
Preshape_T::Preshape_T(MainWindow *window, int state){
    this->window = window;
    this->state = state;
    initTiles(purple);
    double start[4][2] = {{1.75, 1.25}, {0.75, 2.25}, {1.75, 2.25}, {2.75, 2.25}};
    initArray(start);
    moveToStart();
}

//Z
Preshape_Z::Preshape_Z(MainWindow *window, int state){
    this->window = window;
    this->state = state;
    initTiles(red);
    double start[4][2] = {{0.75, 1.25}, {1.75, 1.25}, {1.75, 2.25}, {2.75, 2.25}};
    initArray(start);
    moveToStart();
}

Preshape* PreshapeFactory::getShape(MainWindow *window, int n, int state){
    Preshape *ret = NULL;
    switch(n){
        case 0:
            ret = new Preshape_I(window, state);
            break;
        case 1:
            ret = new Preshape_J(window, state);
            break;
        case 2:
            ret = new Preshape_L(window, state);
            break;
        case 3:
            ret = new Preshape_O(window, state);
            break;
        case 4:
            ret = new Preshape_S(window, state);
            break;
        case 5:
            ret = new Preshape_T(window, state);
            break;
        case 6:
            ret = new Preshape_Z(window, state);
            break;
    }
    return ret;
}






