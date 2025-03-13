#ifndef CAGE_H
#define CAGE_H

#include <QWidget>
#include <QPainter>

#include "consts.h"

class Cage
{
public:
    enum STATE
    {
        NONE,
        ALIVE,
        DEAD
    };

    Cage();
    Cage(int x, int y, int size = CAGE_SIZE, bool isAlive = false);

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

    int size() const;
    void setSize(int size);

    bool isAlive() const;
    void setIsAlive(bool isAlive);

    void setTempIsAlive(STATE isAlive);

    void execute();

    bool contain(int x, int y) const;

    void paint(QPainter& painter);

private:
    int _size;
    int _x;
    int _y;
    bool _isAlive;
    STATE _tempIsAlive;
};

#endif // CAGE_H
