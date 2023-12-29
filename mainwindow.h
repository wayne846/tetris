#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <queue>
#include "shape.h"
#include "preshape.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        const int tileWidth = 30;
        const int sceneWidth = tileWidth * 10;
        const int sceneHeight = tileWidth * 20;

        QGraphicsRectItem *tiles[10][20]; //[x][y]
        QGraphicsScene *scene_main;

        bool isDead;

        void checkLine();

    protected:
        void keyPressEvent(QKeyEvent*);

    private slots:
        void update();

    private:
        Ui::MainWindow *ui;

        Shape *currentShape;
        Preshape *previewShape;
        Preshape *holdShape;
        int holdShapeNumber;
        bool canHold;
        QGraphicsTextItem *text_score;
        QTimer *timer;

        queue<int> shapeSequence;
        int score;
        int totalLine;

        void addShapeSequence();
        void hold();
};
#endif // MAINWINDOW_H
