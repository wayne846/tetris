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
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    //set timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    //init other value
    isDead = false;
    score = 0;
    totalLine = 0;

    //init scene_main
    scene_main = new QGraphicsScene(this);
    scene_main->setSceneRect(0, 0, sceneWidth, sceneHeight);
    scene_main->addRect(QRect(-500, -100, 1200, 1000),QPen() , QBrush(QColor(240,240,240))); //background
    scene_main->addRect(QRect(0, 0, sceneWidth, sceneHeight), QPen(Qt::black, 1), QBrush(Qt::white)); //main background
    for(int i = 0; i < sceneWidth; i += tileWidth){  //grid
        scene_main->addLine(QLine(i, 0, i, sceneHeight), QPen(Qt::gray, 0.5));
    }
    for(int i = 0; i < sceneHeight; i += tileWidth){
        scene_main->addLine(QLine(0, i, sceneWidth, i), QPen(Qt::gray, 0.5));
    }
    scene_main->addRect(QRect(0, 0, sceneWidth, sceneHeight), QPen(Qt::black, 3.2)); //main
    scene_main->addRect(QRect(sceneWidth+tileWidth*3, 0, tileWidth*4.5, tileWidth*4.5), QPen(Qt::black, 3.2), QBrush(Qt::white)); //preview
    scene_main->addRect(QRect(-tileWidth*7.5, 0, tileWidth*4.5, tileWidth*4.5), QPen(Qt::black, 3.2), QBrush(Qt::white)); //hold
    QGraphicsTextItem *text_next = scene_main->addText("NEXT", QFont("Arial", 20));
    text_next->setPos(sceneWidth+tileWidth*3.9, -tileWidth*1.3);
    QGraphicsTextItem *text_hold = scene_main->addText("HOLD", QFont("Arial", 20));
    text_hold->setPos(-tileWidth*6.7, -tileWidth*1.3);
    text_score = scene_main->addText("SCORE: " + QString::number(score), QFont("Arial", 27));
    text_score->setPos(sceneWidth/2.0 - text_score->boundingRect().width()/2, -tileWidth*2.3);
    ui->graphicsView->setScene(scene_main);

    //init tiles
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 20; j++){
            tiles[i][j] = NULL;
        }
    }

    //do some shape thing
    addShapeSequence();
    addShapeSequence();

    currentShape = ShapeFactory::getShape(this, shapeSequence.front());
    shapeSequence.pop();

    previewShape = PreshapeFactory::getShape(this, shapeSequence.front(), 0);

    holdShape = NULL;
    holdShapeNumber = -1;
    canHold = true;
}

void MainWindow::checkLine(){
    int n = 0;
    for(int i = 0; i < 20; i++){
        int flag = true;
        for(int j = 0; j < 10; j++){
            if(tiles[j][i] == NULL){
                flag = false;
                break;
            }
        }
        if(!flag) continue;
        //has line
        n++;
        for(int j = 0; j < 10; j++){
            delete(tiles[j][i]);
            tiles[j][i] = NULL;
        }
        for(int j = i; j > 0; j--){ //move line
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

    //add score
    switch(n){
        case 1:
            score += 100;
            break;
        case 2:
            score += 300;
            break;
        case 3:
            score += 500;
            break;
        case 4:
            score += 800;
            break;
    }
    text_score->setPlainText("SCORE: " + QString::number(score));
    text_score->setPos(sceneWidth/2.0 - text_score->boundingRect().width()/2, -tileWidth*2.3);

    //change timer
    totalLine += n;
    if(totalLine >= 10 && timer->interval() >= 1000){
        timer->setInterval(800);
    }else if(totalLine >= 20 && timer->interval() >= 800){
        timer->setInterval(700);
    }else if(totalLine >= 30 && timer->interval() >= 700){
        timer->setInterval(600);
    }else if(totalLine >= 40 && timer->interval() >= 600){
        timer->setInterval(500);
    }else if(totalLine >= 50 && timer->interval() >= 500){
        timer->setInterval(400);
    }else if(totalLine >= 60 && timer->interval() >= 400){
        timer->setInterval(300);
    }else if(totalLine >= 70 && timer->interval() >= 300){
        timer->setInterval(200);
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
        canHold = true;
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
            if(!currentShape->moveDown()){
                delete(currentShape);
                currentShape = ShapeFactory::getShape(this, shapeSequence.front());
                shapeSequence.pop();
                if(shapeSequence.size() < 7) addShapeSequence();
                previewShape->deleteTiles();
                delete(previewShape);
                previewShape = PreshapeFactory::getShape(this, shapeSequence.front(), 0);
                canHold = true;
            }
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
            canHold = true;
            break;
        case Qt::Key_C:
            hold();
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

void MainWindow::hold(){
    if(!canHold) return;
    if(holdShapeNumber == -1){
        holdShapeNumber = currentShape->getId();
        holdShape = PreshapeFactory::getShape(this, holdShapeNumber, 1);
        //take next shape
        currentShape->deleteTiles();
        delete(currentShape);
        currentShape = ShapeFactory::getShape(this, shapeSequence.front());
        shapeSequence.pop();
        if(shapeSequence.size() < 7) addShapeSequence();
        previewShape->deleteTiles();
        delete(previewShape);
        previewShape = PreshapeFactory::getShape(this, shapeSequence.front(), 0);
        canHold = false;
    }else{
        int temp = holdShapeNumber;
        holdShape->deleteTiles();
        delete(holdShape);
        holdShapeNumber = currentShape->getId();
        holdShape = PreshapeFactory::getShape(this, holdShapeNumber, 1);

        currentShape->deleteTiles();
        delete(currentShape);
        currentShape = ShapeFactory::getShape(this, temp);
        canHold = false;
    }
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_actionrestart_game_triggered()
{
    //delete all shape
    for(int i = 0; i < 20; i++){
        for(int j = 0; j < 10; j++){
            if(tiles[j][i] != NULL) delete(tiles[j][i]);
            tiles[j][i] = NULL;
        }
    }
    if(previewShape != NULL){
        previewShape->deleteTiles();
        delete(previewShape);
        previewShape = NULL;
    }
    if(holdShape != NULL){
        holdShape->deleteTiles();
        delete(holdShape);
        holdShape = NULL;
    }
    holdShapeNumber = -1;
    canHold = true;
    if(currentShape != NULL){
        currentShape->deleteTiles();
        delete(currentShape);
        currentShape = NULL;
    }

    timer->setInterval(1000);

    //init other value
    isDead = false;
    score = 0;
    totalLine = 0;

    //update text
    text_score->setPlainText("SCORE: " + QString::number(score));
    text_score->setPos(sceneWidth/2.0 - text_score->boundingRect().width()/2, -tileWidth*2.3);

    while(!shapeSequence.empty()) shapeSequence.pop();
    addShapeSequence();
    addShapeSequence();
    currentShape = ShapeFactory::getShape(this, shapeSequence.front());
    shapeSequence.pop();
    previewShape = PreshapeFactory::getShape(this, shapeSequence.front(), 0);

}

