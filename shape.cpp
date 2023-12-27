#include "shape.h"
#include "mainwindow.h"
#include <QDebug>
#include <stdlib.h>
#include <time.h>

//Shape
bool Shape::moveDown(){
    for(int i = 0; i < 4; i++){
        if(mytilesPosition[i][1]+1 >= 20 ||
           window->tiles[ mytilesPosition[i][0] ][ mytilesPosition[i][1]+1 ] != NULL){
            for(int i = 0; i < 4; i++){
                window->tiles[ mytilesPosition[i][0] ][ mytilesPosition[i][1]] = mytiles[i];
            }
            return false;
        }
    }

    for(int i = 0; i < 4; i++){
        mytilesPosition[i][1] += 1;
    }
    updatePosition();
    return true;
}
void Shape::updatePosition(){
    for(int i = 0; i < 4; i++){
        mytiles[i]->setPos(window->tileWidth*mytilesPosition[i][0], window->tileWidth*mytilesPosition[i][1]);
    }
}

//I
Shape_I::Shape_I(MainWindow *window){
    this->window = window;
    for(int i = 0; i < 4; i++){
        this->mytiles[i] = window->scene_main->addRect(QRect(0, 0, window->tileWidth, window->tileWidth), QPen(Qt::black, 2.4), QBrush(blue));
        this->mytilesPosition[i][0] = 3+i;
        this->mytilesPosition[i][1] = 1;
    }
    updatePosition();
}

//J
Shape_J::Shape_J(MainWindow *window){
    this->window = window;
    for(int i = 0; i < 4; i++){
        this->mytiles[i] = window->scene_main->addRect(QRect(0, 0, window->tileWidth, window->tileWidth), QPen(Qt::black, 2.4), QBrush(darkBlue));
    }
    this->mytilesPosition[0][0] = 3;
    this->mytilesPosition[0][1] = 0;
    for(int i = 1; i < 4; i++){
        this->mytilesPosition[i][0] = 2+i;
        this->mytilesPosition[i][1] = 1;
    }
    updatePosition();
}

//L
Shape_L::Shape_L(MainWindow *window){
    this->window = window;
    for(int i = 0; i < 4; i++){
        this->mytiles[i] = window->scene_main->addRect(QRect(0, 0, window->tileWidth, window->tileWidth), QPen(Qt::black, 2.4), QBrush(orange));
    }
    this->mytilesPosition[0][0] = 5;
    this->mytilesPosition[0][1] = 0;
    for(int i = 1; i < 4; i++){
        this->mytilesPosition[i][0] = 2+i;
        this->mytilesPosition[i][1] = 1;
    }
    updatePosition();
}

//O
Shape_O::Shape_O(MainWindow *window){
    this->window = window;
    for(int i = 0; i < 4; i++){
        this->mytiles[i] = window->scene_main->addRect(QRect(0, 0, window->tileWidth, window->tileWidth), QPen(Qt::black, 2.4), QBrush(yellow));
    }
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            this->mytilesPosition[i*2+j][0] = 4 + j;
            this->mytilesPosition[i*2+j][1] = 0 + i;
        }
    }
    updatePosition();
}

//S
Shape_S::Shape_S(MainWindow *window){
    this->window = window;
    for(int i = 0; i < 4; i++){
        this->mytiles[i] = window->scene_main->addRect(QRect(0, 0, window->tileWidth, window->tileWidth), QPen(Qt::black, 2.4), QBrush(green));
    }
    int arr[4][2] = {{4, 0}, {5, 0}, {3, 1}, {4, 1}};
    for(int i = 0; i < 4; i++){
        this->mytilesPosition[i][0] = arr[i][0];
        this->mytilesPosition[i][1] = arr[i][1];
    }
    updatePosition();
}

//T
Shape_T::Shape_T(MainWindow *window){
    this->window = window;
    for(int i = 0; i < 4; i++){
        this->mytiles[i] = window->scene_main->addRect(QRect(0, 0, window->tileWidth, window->tileWidth), QPen(Qt::black, 2.4), QBrush(purple));
    }
    int arr[4][2] = {{4, 0}, {3, 1}, {4, 1}, {5, 1}};
    for(int i = 0; i < 4; i++){
        this->mytilesPosition[i][0] = arr[i][0];
        this->mytilesPosition[i][1] = arr[i][1];
    }
    updatePosition();
}

//Z
Shape_Z::Shape_Z(MainWindow *window){
    this->window = window;
    for(int i = 0; i < 4; i++){
        this->mytiles[i] = window->scene_main->addRect(QRect(0, 0, window->tileWidth, window->tileWidth), QPen(Qt::black, 2.4), QBrush(red));
    }
    int arr[4][2] = {{3, 0}, {4, 0}, {4, 1}, {5, 1}};
    for(int i = 0; i < 4; i++){
        this->mytilesPosition[i][0] = arr[i][0];
        this->mytilesPosition[i][1] = arr[i][1];
    }
    updatePosition();
}

//ShapeFactor
Shape* ShapeFactor::getShape(MainWindow *window){
    srand(time(NULL));
    int n = rand() % 7;
    Shape *ret = NULL;
    switch(n){
        case 0:
            ret = new Shape_I(window);
            break;
        case 1:
            ret = new Shape_J(window);
            break;
        case 2:
            ret = new Shape_L(window);
            break;
        case 3:
            ret = new Shape_O(window);
            break;
        case 4:
            ret = new Shape_S(window);
            break;
        case 5:
            ret = new Shape_T(window);
            break;
        case 6:
            ret = new Shape_Z(window);
            break;
    }
    return ret;
}

