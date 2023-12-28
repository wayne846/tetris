#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QKeyEvent>
#include <stdlib.h>
#include <time.h>
#include "shape.h"
#include "preshape.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    //set timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    //init scene_main
    scene_main = new QGraphicsScene(this);
    scene_main->setSceneRect(0, 0, sceneWidth, sceneHeight);
    scene_main->addRect(QRect(-500, -100, 1200, 1000),QPen() , QBrush(QColor(240,240,240)));
    scene_main->addRect(QRect(0, 0, sceneWidth, sceneHeight), QPen(Qt::black, 1), QBrush(Qt::white)); //main background
    for(int i = 0; i < sceneWidth; i += tileWidth){
        scene_main->addLine(QLine(i, 0, i, sceneHeight), QPen(Qt::gray, 0.5));
    }
    for(int i = 0; i < sceneHeight; i += tileWidth){
        scene_main->addLine(QLine(0, i, sceneWidth, i), QPen(Qt::gray, 0.5));
    }
    scene_main->addRect(QRect(0, 0, sceneWidth, sceneHeight), QPen(Qt::black, 3.2)); //main
    scene_main->addRect(QRect(sceneWidth+tileWidth*3, 0, tileWidth*4.5, tileWidth*4.5), QPen(Qt::black, 3.2), QBrush(Qt::white)); //preview
    scene_main->addRect(QRect(-tileWidth*7.5, 0, tileWidth*4.5, tileWidth*4.5), QPen(Qt::black, 3.2), QBrush(Qt::white)); //hold
    QGraphicsTextItem *text_next = scene_main->addText(QString("NEXT"), QFont("Arial", 25));
    text_next->setPos(sceneWidth+tileWidth*3.7, -tileWidth*1.5);
    QGraphicsTextItem *text_hold = scene_main->addText(QString("HOLD"), QFont("Arial", 25));
    text_hold->setPos(-tileWidth*6.9, -tileWidth*1.5);
    ui->graphicsView->setScene(scene_main);

    //init tiles
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 20; j++){
            tiles[i][j] = NULL;
        }
    }

    isDead = false;

    addShapeSequence();
    addShapeSequence();

    currentShape = ShapeFactory::getShape(this, shapeSequence.front());
    shapeSequence.pop();

    previewShape = PreshapeFactory::getShape(this, shapeSequence.front(), 0);
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
    if(isDead) return;

    if(!currentShape->moveDown()){
        delete(currentShape);
        currentShape = ShapeFactory::getShape(this, shapeSequence.front());
        shapeSequence.pop();
        if(shapeSequence.size() < 7) addShapeSequence();
        previewShape->deleteTiles();
        delete(previewShape);
        previewShape = PreshapeFactory::getShape(this, shapeSequence.front(), 0);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(isDead) return;

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
            currentShape = ShapeFactory::getShape(this, shapeSequence.front());
            shapeSequence.pop();
            if(shapeSequence.size() < 7) addShapeSequence();
            previewShape->deleteTiles();
            delete(previewShape);
            previewShape = PreshapeFactory::getShape(this, shapeSequence.front(), 0);
            break;
    }
}

void MainWindow::addShapeSequence(){
    int arr[7] = {0, 1, 2, 3, 4, 5, 6};
    srand(time(NULL));
    for(int i = 0; i < 7; i++){
        int n = rand() % 7;
        int temp = arr[i];
        arr[i] = arr[n];
        arr[n] = temp;
    }
    for(int i = 0; i < 7; i++){
        shapeSequence.push(arr[i]);
    }
}

MainWindow::~MainWindow(){
    delete ui;
}
