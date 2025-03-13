#include "cage.h"

Cage::Cage() : Cage(0, 0)
{
}

Cage::Cage(int x, int y, int size, bool isAlive) : _size(size), _x(x), _y(y), _isAlive(isAlive), _tempIsAlive(STATE::NONE)
{
}

int Cage::x() const
{
    return _x;
}

void Cage::setX(int x)
{
    _x = x;
}

int Cage::y() const
{
    return _y;
}

void Cage::setY(int y)
{
    _y = y;
}

int Cage::size() const
{
    return _size;
}

void Cage::setSize(int size)
{
    _size = size;
}

bool Cage::isAlive() const
{
    return _isAlive;
}

void Cage::setIsAlive(bool isAlive)
{
    _isAlive = isAlive;
}

void Cage::setTempIsAlive(STATE isAlive)
{
    _tempIsAlive = isAlive;
}

void Cage::execute()
{
    _isAlive = _tempIsAlive == STATE::ALIVE;
    _tempIsAlive = STATE::NONE;
}

bool Cage::contain(int x, int y) const
{
    return (_x >= x && _x <= x + _size) && (_y >= y && _y <= y + _size);
}

void Cage::paint(QPainter& painter)
{
    painter.save();

    painter.setPen(QPen(CAGE_BORDER_COLOR));

    if (_isAlive)
        painter.setBrush(QBrush(CAGE_COLOR));

    QRect rect(_x, _y, _size, _size);
    painter.drawRect(rect);

    painter.restore();
}
