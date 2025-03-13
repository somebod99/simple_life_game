#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>

namespace Ui {
class MenuWidget;
}

class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent = nullptr);
    ~MenuWidget();

signals:
    void start();
    void fillRandom(int state);

private:
    Ui::MenuWidget *ui;
};

#endif // MENUWIDGET_H
