#include "menuwidget.h"
#include "ui_menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuWidget)
{
    ui->setupUi(this);

    connect(ui->pb_Start, &QPushButton::clicked, this, &MenuWidget::start);
    connect(ui->cb_FillRandom, &QCheckBox::stateChanged, this, &MenuWidget::fillRandom);
};

MenuWidget::~MenuWidget()
{
    delete ui;
}
