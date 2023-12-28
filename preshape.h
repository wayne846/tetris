#ifndef PRESHAPE_H
#define PRESHAPE_H

#include <QGraphicsItem>

class MainWindow;

class Preshape
{
    public:
        void deleteTiles();

    protected:
        const QColor blue = QColor(0,173,214);
        const QColor darkBlue = QColor(0,96,206);
        const QColor orange = QColor(255,166,0);
        const QColor yellow = QColor(255,228,37);
        const QColor green = QColor(0,197,46);
        const QColor purple = QColor(164,26,192);
        const QColor red = QColor(237,21,0);

        QGraphicsRectItem *mytiles[4];
        double startPosition[4][2];
        int state; //0: preview  1:hold
        MainWindow *window;

        void initTiles(QColor color);
        void initArray(double start[4][2]);
        void moveToStart();
};

class Preshape_I : public Preshape{
    public:
        Preshape_I(MainWindow *window, int state);
};

class Preshape_J : public Preshape{
    public:
        Preshape_J(MainWindow *window, int state);
};

class Preshape_L : public Preshape{
    public:
        Preshape_L(MainWindow *window, int state);
};

class Preshape_O : public Preshape{
    public:
        Preshape_O(MainWindow *window, int state);
};

class Preshape_S : public Preshape{
    public:
        Preshape_S(MainWindow *window, int state);
};

class Preshape_T : public Preshape{
    public:
        Preshape_T(MainWindow *window, int state);
};

class Preshape_Z : public Preshape{
    public:
        Preshape_Z(MainWindow *window, int state);
};

class PreshapeFactory{
    public:
        static Preshape* getShape(MainWindow *window, int n, int state);
};

#endif // PRESHAPE_H
