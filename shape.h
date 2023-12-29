#ifndef SHAPE_H
#define SHAPE_H

#include <QGraphicsItem>

class MainWindow;

using namespace std;

class Shape{
    public:
        bool moveDown();
        bool moveRight();
        bool moveLeft();
        void moveBottom();
        bool rotate();
        void deleteTiles();
        int getId();

    protected:
        const QColor blue = QColor(0,173,214);
        const QColor darkBlue = QColor(0,96,206);
        const QColor orange = QColor(255,166,0);
        const QColor yellow = QColor(255,228,37);
        const QColor green = QColor(0,197,46);
        const QColor purple = QColor(164,26,192);
        const QColor red = QColor(237,21,0);

        QGraphicsRectItem *mytiles[4];
        QGraphicsRectItem *previewTiles[4];
        int mytilesPosition[4][2]; //[][0]:x  [][1]:y;
        int previewPosition[4][2];
        int startPosition[4][2];
        int dir;
        int rotateTable[4][4][2];
        int id;
        MainWindow *window;

        void initTiles(QColor color);
        void initArray(int start[4][2], int rotate[4][4][2]);
        void moveToStart();
        void updatePosition();
        void checkDead();
};

class Shape_I : public Shape{
    public:
        Shape_I(MainWindow *window);
};

class Shape_J : public Shape{
    public:
        Shape_J(MainWindow *window);
};

class Shape_L : public Shape{
    public:
        Shape_L(MainWindow *window);
};

class Shape_O : public Shape{
    public:
        Shape_O(MainWindow *window);
};

class Shape_S : public Shape{
    public:
        Shape_S(MainWindow *window);
};

class Shape_T : public Shape{
    public:
        Shape_T(MainWindow *window);
};

class Shape_Z : public Shape{
    public:
        Shape_Z(MainWindow *window);
};

class ShapeFactory{
    public:
        static Shape* getShape(MainWindow *window);
        static Shape* getShape(MainWindow *window, int n);
};

#endif // SHAPE_H
