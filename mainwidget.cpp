#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    ui->pb_Back->setVisible(false);
    ui->pb_Next->setVisible(false);
    ui->hs_Speed->setVisible(false);
    ui->lb_Generation->setVisible(false);
    ui->pb_StartStop->setVisible(false);
    ui->pb_StartStop->setProperty(START_STOP_PROP, START_STOP::START);

    CanvasWidget* cw = new CanvasWidget();
    MenuWidget* mw = new MenuWidget();

    ui->stackedWidget->addWidget(mw);
    ui->stackedWidget->addWidget(cw);

    ui->stackedWidget->setCurrentIndex(0);

    connect(mw, &MenuWidget::start, this, [this]()
    {
        QPalette pal = palette();
        pal.setColor(backgroundRole(), Qt::black);
        setPalette(pal);

        ui->stackedWidget->setCurrentIndex(1);
        ui->pb_Back->setVisible(true);
        ui->pb_StartStop->setVisible(true);
        ui->pb_Next->setVisible(true);
        ui->hs_Speed->setVisible(true);
        ui->lb_Generation->setVisible(true);
    });

    connect(mw, &MenuWidget::fillRandom, this, [cw = cw](int state)
    {
        cw->setIsFillRandom(state == Qt::CheckState::Checked);
    });

    connect(ui->pb_Back, &QPushButton::clicked, this, [this]()
    {
        QPalette pal = palette();
        pal.setColor(backgroundRole(), Qt::white);
        setPalette(pal);

        ui->stackedWidget->setCurrentIndex(0);
        ui->pb_Back->setVisible(false);
        ui->pb_StartStop->setVisible(false);
        ui->pb_Next->setVisible(false);
        ui->hs_Speed->setVisible(false);
        ui->lb_Generation->setVisible(false);
    });

    connect(ui->pb_StartStop, &QPushButton::clicked, this, [this, cw = cw]()
    {
        if (ui->pb_StartStop->property(START_STOP_PROP).value<int>() == START_STOP::STOP)
        {
            cw->stop();
            ui->pb_StartStop->setText("Start");
            ui->pb_StartStop->setProperty(START_STOP_PROP, START_STOP::START);
        }
        else
        {
            cw->start();
            ui->pb_StartStop->setText("Stop");
            ui->pb_StartStop->setProperty(START_STOP_PROP, START_STOP::STOP);
        }
    });

    connect(cw, &CanvasWidget::started, this, [this]()
    {
        ui->pb_Next->setEnabled(false);
    });

    connect(cw, &CanvasWidget::stopped, this, [this]()
    {
        ui->pb_Next->setEnabled(true);
    });

    connect(ui->pb_Next, &QPushButton::clicked, cw, &CanvasWidget::next);
    connect(ui->hs_Speed, &QSlider::valueChanged, cw, &CanvasWidget::setSpeed);

    connect(cw, &CanvasWidget::ticked, this, [this](int generation)
    {
        QPalette pal = ui->lb_Generation->palette();
        pal.setColor(foregroundRole(), Qt::white);
        ui->lb_Generation->setPalette(pal);

        ui->lb_Generation->setText(QString("Generation: %1").arg(generation));
    });
}

MainWidget::~MainWidget()
{
    delete ui;
}
