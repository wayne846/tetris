#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QKeyEvent>
#include "shape.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    //set timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(500);

    //init scene_main
    scene_main = new QGraphicsScene(this);
    scene_main->setSceneRect(0, 0, sceneWidth, sceneHeight);
    for(int i = 0; i < sceneWidth; i += tileWidth){
        scene_main->addLine(QLine(i, 0, i, sceneHeight), QPen(Qt::gray, 0.5));
    }
    for(int i = 0; i < sceneHeight; i += tileWidth){
        scene_main->addLine(QLine(0, i, sceneWidth, i), QPen(Qt::gray, 0.5));
    }
    scene_main->addRect(QRect(0, 0, sceneWidth, sceneHeight), QPen(Qt::black, 3.2));
    ui->graphicsView->setScene(scene_main);

    //init tiles
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 20; j++){
            tiles[i][j] = NULL;
        }
    }

    currentShape = ShapeFactor::getShape(this);
}

void MainWindow::checkLine(){
    for(int i = 0; i < 20; i++){
        int flag = true;
        for(int j = 0; j < 10; j++){
            if(tiles[j][i] == NULL){
                flag = false;
                break;
            }
        }
        if(!flag) continue;
        for(int j = 0; j < 10; j++){
            delete(tiles[j][i]);
            tiles[j][i] = NULL;
        }
        for(int j = i; j > 0; j--){
            for(int k = 0; k < 10; k++){
                if(tiles[k][j-1] != NULL){
                    tiles[k][j-1]->setPos(tiles[k][j-1]->x(), tiles[k][j-1]->y()+tileWidth);
                }
                tiles[k][j] = tiles[k][j-1];
                tiles[k][j-1] = NULL;
            }
        }
        for(int j = 0; j < 10; j++){
            tiles[j][0] = NULL;
        }
    }
}

void MainWindow::update(){
    if(!currentShape->moveDown()){
        delete(currentShape);
        currentShape = ShapeFactor::getShape(this);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_Up:
        case Qt::Key_W:
            currentShape->rotate();
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            currentShape->moveRight();
            break;
        case Qt::Key_Left:
        case Qt::Key_A:
            currentShape->moveLeft();
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            currentShape->moveDown();
            break;
        case Qt::Key_Space:
            currentShape->moveBottom();
            delete(currentShape);
            currentShape = ShapeFactor::getShape(this);
            break;
    }
}

MainWindow::~MainWindow(){
    delete ui;
}
