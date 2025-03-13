#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include "canvaswidget.h"
#include "menuwidget.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

    enum START_STOP
    {
        STOP,
        START
    };

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
