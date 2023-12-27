#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
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

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::update(){
    if(!currentShape->moveDown()){
        currentShape = ShapeFactor::getShape(this);
    }
}
