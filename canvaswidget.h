#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QTimer>

#include <vector>
#include <memory>
#include <random>

#include "cage.h"

namespace Ui {
class CanvasWidget;
}

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    ~CanvasWidget();

    void setIsFillRandom(bool isFillRandom);
    void start();
    void stop();
    void next();

    void setSpeed(int speed);

    int generation() const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void tick();

private:
    void fillCages();
    void checkCages();
    int calcNeighbours(int i, int j);

signals:
    void started();
    void stopped();
    void ticked(int generation);

private:
    Ui::CanvasWidget *ui;
    std::vector<std::unique_ptr<Cage>> _cages;
    int _curCageSize;
    bool _isFillRandom;

    int _cageCountX;
    int _cageCountY;

    int _generation;

    QTimer _tickTimer;
};
#endif // CANVASWIDGET_H
