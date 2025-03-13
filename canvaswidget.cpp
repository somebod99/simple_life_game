#include "canvaswidget.h"
#include "ui_canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CanvasWidget),
      _curCageSize(CAGE_SIZE),
      _isFillRandom(false),
      _generation(0)
{
    ui->setupUi(this);

    QPalette pal = palette();
    pal.setColor(backgroundRole(), Qt::black);
    setPalette(pal);

    connect(&_tickTimer, &QTimer::timeout, this, &CanvasWidget::tick);

    _tickTimer.setInterval(SPEED_COEF - START_SPEED);
}

CanvasWidget::~CanvasWidget()
{
    delete ui;
}

void CanvasWidget::setIsFillRandom(bool isFillRandom)
{
    _isFillRandom = isFillRandom;
}

void CanvasWidget::start()
{
    _tickTimer.start();
    emit started();
}

void CanvasWidget::stop()
{
    _tickTimer.stop();
    emit stopped();
}

void CanvasWidget::next()
{
    tick();
}

void CanvasWidget::setSpeed(int speed)
{
    _tickTimer.setInterval(SPEED_COEF - speed);
}

int CanvasWidget::generation() const
{
    return _generation;
}

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter p(this);

    for (auto& cage : _cages)
        cage->paint(p);
}

void CanvasWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    fillCages();
}

void CanvasWidget::wheelEvent(QWheelEvent *event)
{
    _curCageSize += event->delta() > 0 ? WHEEL_STEP : -WHEEL_STEP;
    fillCages();
    repaint();
}

void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

    if (event->button() == Qt::LeftButton)
        for (auto& cage : _cages)
            if (cage->contain(event->x() - _curCageSize, event->y() - _curCageSize))
            {
                cage->setIsAlive(!cage->isAlive());
                repaint();
                break;
            }
}

void CanvasWidget::tick()
{
    checkCages();

    for (auto& cage : _cages)
        cage->execute();

    repaint();

    ++_generation;

    emit ticked(_generation);
}

void CanvasWidget::fillCages()
{
    _generation = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 100);

    _cages.clear();

    _cageCountX = width() / _curCageSize;
    _cageCountY = height() / _curCageSize;

    for (int i = 0; i < _cageCountY; ++i)
        for (int j = 0; j < _cageCountX; ++j)
        {
            bool isAlive = _isFillRandom ? distr(gen) > 80 : false;
            _cages.emplace_back(new Cage(_curCageSize * j, _curCageSize * i, _curCageSize, isAlive));
        }
}

void CanvasWidget::checkCages()
{
    for (int i = 0; i < _cageCountY; ++i)
    {
        for (int j = 0; j < _cageCountX; ++j)
        {
            int countAliveAround = calcNeighbours(i, j);

            Cage* curCage = _cages[i * _cageCountX + j].get();

            if (curCage->isAlive())
            {
                if (countAliveAround < 2 || countAliveAround > 3)
                    curCage->setTempIsAlive(Cage::STATE::DEAD);
                else
                    curCage->setTempIsAlive(Cage::STATE::ALIVE);
            }
            else
            {
                if (countAliveAround == 3)
                    curCage->setTempIsAlive(Cage::STATE::ALIVE);
            }
        }
    }
}

int CanvasWidget::calcNeighbours(int i, int j)
{
    int countAliveAround = 0;

    if (i > 0)
    {
        countAliveAround += (int)_cages[(i - 1) * _cageCountX + j]->isAlive();

        if (j > 0)
            countAliveAround += (int)_cages[(i - 1) * _cageCountX + (j - 1)]->isAlive();

        if (j < _cageCountX - 1)
            countAliveAround += (int)_cages[(i - 1) * _cageCountX + (j + 1)]->isAlive();
    }

    if (i < _cageCountY - 1)
    {
        countAliveAround += (int)_cages[(i + 1) * _cageCountX + j]->isAlive();

        if (j > 0)
            countAliveAround += (int)_cages[(i + 1) * _cageCountX + (j - 1)]->isAlive();

        if (j < _cageCountX - 1)
            countAliveAround += (int)_cages[(i + 1) * _cageCountX + (j + 1)]->isAlive();
    }

    if (j > 0)
        countAliveAround += (int)_cages[i * _cageCountX + (j - 1)]->isAlive();

    if (j < _cageCountX - 1)
        countAliveAround += (int)_cages[i * _cageCountX + (j + 1)]->isAlive();

    return countAliveAround;
}

