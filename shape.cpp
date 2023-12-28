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
            for(int i = 0; i < 4; i++){
                delete(previewTiles[i]);
            }
            window->checkLine();
            return false;
        }
    }

    for(int i = 0; i < 4; i++){
        mytilesPosition[i][1] += 1;
    }
    updatePosition();
    return true;
}
bool Shape::moveRight(){
    for(int i = 0; i < 4; i++){
        if(mytilesPosition[i][0]+1 >= 10 ||
           window->tiles[ mytilesPosition[i][0]+1 ][ mytilesPosition[i][1] ] != NULL){
            return false;
        }
    }

    for(int i = 0; i < 4; i++){
        mytilesPosition[i][0] += 1;
    }
    updatePosition();
    return true;
}
bool Shape::moveLeft(){
    for(int i = 0; i < 4; i++){
        if(mytilesPosition[i][0]-1 < 0 ||
           window->tiles[ mytilesPosition[i][0]-1 ][ mytilesPosition[i][1] ] != NULL){
            return false;
        }
    }

    for(int i = 0; i < 4; i++){
        mytilesPosition[i][0] -= 1;
    }
    updatePosition();
    return true;
}
void Shape::moveBottom(){
    for(int i = 0; i < 4; i++){
        mytilesPosition[i][0] = previewPosition[i][0];
        mytilesPosition[i][1] = previewPosition[i][1];
    }
    for(int i = 0; i < 4; i++){
        window->tiles[ mytilesPosition[i][0] ][ mytilesPosition[i][1]] = mytiles[i];
    }
    for(int i = 0; i < 4; i++){
        delete(previewTiles[i]);
    }
    for(int i = 0; i < 4; i++){
        mytiles[i]->setPos(window->tileWidth*mytilesPosition[i][0], window->tileWidth*mytilesPosition[i][1]);
    }
    window->checkLine();
}
bool Shape::rotate(){
    int next[4][2];
    for(int i = 0; i < 4; i++){
        next[i][0] = mytilesPosition[i][0] + rotateTable[dir][i][0];
        next[i][1] = mytilesPosition[i][1] + rotateTable[dir][i][1];
    }
    while(next[0][0]<0 || next[1][0]<0 || next[2][0]<0 || next[3][0]<0){ //check left
        next[0][0] += 1;
        next[1][0] += 1;
        next[2][0] += 1;
        next[3][0] += 1;
    }
    while(next[0][0]>9 || next[1][0]>9 || next[2][0]>9 || next[3][0]>9){ //check right
        next[0][0] -= 1;
        next[1][0] -= 1;
        next[2][0] -= 1;
        next[3][0] -= 1;
    }
    while(next[0][1]>19 || next[1][1]>19 || next[2][1]>19 || next[3][1]>19){ //check down
        next[0][1] -= 1;
        next[1][1] -= 1;
        next[2][1] -= 1;
        next[3][1] -= 1;
    }
    for(int i = 0; i < 4; i++){ //check already has tile
        if(window->tiles[ next[i][0] ][ next[i][1] ] != NULL){
            return false;
        }
    }
    for(int i = 0; i < 4; i++){ //do rotate;
        mytilesPosition[i][0] = next[i][0];
        mytilesPosition[i][1] = next[i][1];
    }
    dir++;
    dir = dir % 4;
    updatePosition();
    return true;
}
void Shape::initTiles(QColor color){
    for(int i = 0; i < 4; i++){
        previewTiles[i] = window->scene_main->addRect(QRect(0, 0, window->tileWidth, window->tileWidth), QPen(color, 2.4));
    }
    for(int i = 0; i < 4; i++){
        mytiles[i] = window->scene_main->addRect(QRect(0, 0, window->tileWidth, window->tileWidth), QPen(Qt::black, 2.4), QBrush(color));
    }
}
void Shape::initArray(int start[4][2], int rotate[4][4][2]){
    for(int i = 0; i < 4; i++){
        startPosition[i][0] = start[i][0];
        startPosition[i][1] = start[i][1];
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            rotateTable[i][j][0] = rotate[i][j][0];
            rotateTable[i][j][1] = rotate[i][j][1];
        }
    }
    dir = 0;
}
void Shape::moveToStart(){
    for(int i = 0; i < 4; i++){
        this->mytilesPosition[i][0] = startPosition[i][0];
        this->mytilesPosition[i][1] = startPosition[i][1];
    }
}
void Shape::updatePosition(){
    for(int i = 0; i < 4; i++){
        mytiles[i]->setPos(window->tileWidth*mytilesPosition[i][0], window->tileWidth*mytilesPosition[i][1]);
    }

    //set previewTiles
    for(int i = 0; i < 4; i++){
        previewPosition[i][0] = mytilesPosition[i][0];
        previewPosition[i][1] = mytilesPosition[i][1];
    }
    while(1){
        int flag = true;
        for(int i = 0; i < 4; i++){
            if(previewPosition[i][1]+1 >= 20 ||
               window->tiles[ previewPosition[i][0] ][ previewPosition[i][1]+1 ] != NULL){
                flag = false;
            }
        }
        if(!flag) break;
        for(int i = 0; i < 4; i++){
            previewPosition[i][1] += 1;
        }
    }
    for(int i = 0; i < 4; i++){
        previewTiles[i]->setPos(window->tileWidth*previewPosition[i][0], window->tileWidth*previewPosition[i][1]);
    }

}

//I
Shape_I::Shape_I(MainWindow *window){
    this->window = window;
    initTiles(blue);
    int start[4][2] = {{3, 0}, {4, 0}, {5, 0}, {6, 0}};
    int rotate[4][4][2] = {{{2, -1}, {1, 0}, {0, 1}, {-1, 2}},
                           {{1, 2}, {0, 1}, {-1, 0}, {-2, -1}},
                           {{-2, 1}, {-1, 0}, {0, -1}, {1, -2}},
                           {{-1, -2}, {0, -1}, {1, 0}, {2, 1}}};
    initArray(start, rotate);
    moveToStart();
    updatePosition();
}

//J
Shape_J::Shape_J(MainWindow *window){
    this->window = window;
    initTiles(darkBlue);
    int start[4][2] = {{3, 0}, {3, 1}, {4, 1}, {5, 1}};
    int rotate[4][4][2] = {{{2, 0}, {1, -1}, {0, 0}, {-1, 1}},
                           {{0, 2}, {1, 1}, {0, 0}, {-1, -1}},
                           {{-2, 0}, {-1, 1}, {0, 0}, {1, -1}},
                           {{0, -2}, {-1, -1}, {0, 0}, {1, 1}}};
    initArray(start, rotate);
    moveToStart();
    updatePosition();
}

//L
Shape_L::Shape_L(MainWindow *window){
    this->window = window;
    initTiles(orange);
    int start[4][2] = {{5, 0}, {3, 1}, {4, 1}, {5, 1}};
    int rotate[4][4][2] = {{{0, 2}, {1, -1}, {0, 0}, {-1, 1}},
                           {{-2, 0}, {1, 1}, {0, 0}, {-1, -1}},
                           {{0, -2}, {-1, 1}, {0, 0}, {1, -1}},
                           {{2, 0}, {-1, -1}, {0, 0}, {1, 1}}};
    initArray(start, rotate);
    moveToStart();
    updatePosition();
}

//O
Shape_O::Shape_O(MainWindow *window){
    this->window = window;
    initTiles(yellow);
    int start[4][2] = {{4, 0}, {5, 0}, {4, 1}, {5, 1}};
    int rotate[4][4][2] = {{{0, 0}, {0, 0}, {0, 0}, {0, 0}},
                           {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
                           {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
                           {{0, 0}, {0, 0}, {0, 0}, {0, 0}}};
    initArray(start, rotate);
    moveToStart();
    updatePosition();
}

//S
Shape_S::Shape_S(MainWindow *window){
    this->window = window;
    initTiles(green);
    int start[4][2] = {{4, 0}, {5, 0}, {3, 1}, {4, 1}};
    int rotate[4][4][2] = {{{1, 1}, {0, 2}, {1, -1}, {0, 0}},
                           {{-1, 1}, {-2, 0}, {1, 1}, {0, 0}},
                           {{-1, -1}, {0, -2}, {-1, 1}, {0, 0}},
                           {{1, -1}, {2, 0}, {-1, -1}, {0, 0}}};
    initArray(start, rotate);
    moveToStart();
    updatePosition();
}

//T
Shape_T::Shape_T(MainWindow *window){
    this->window = window;
    initTiles(purple);
    int start[4][2] = {{4, 0}, {3, 1}, {4, 1}, {5, 1}};
    int rotate[4][4][2] = {{{1, 1}, {1, -1}, {0, 0}, {-1, 1}},
                           {{-1, 1}, {1, 1}, {0, 0}, {-1, -1}},
                           {{-1, -1}, {-1, 1}, {0, 0}, {1, -1}},
                           {{1, -1}, {-1, -1}, {0, 0}, {1, 1}}};
    initArray(start, rotate);
    moveToStart();
    updatePosition();
}

//Z
Shape_Z::Shape_Z(MainWindow *window){
    this->window = window;
    initTiles(red);
    int start[4][2] = {{3, 0}, {4, 0}, {4, 1}, {5, 1}};
    int rotate[4][4][2] = {{{2, 0}, {1, 1}, {0, 0}, {-1, 1}},
                           {{0, 2}, {-1, 1}, {0, 0}, {-1, -1}},
                           {{-2, 0}, {-1, -1}, {0, 0}, {1, -1}},
                           {{0, -2}, {1, -1}, {0, 0}, {1, 1}}};
    initArray(start, rotate);
    moveToStart();
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

