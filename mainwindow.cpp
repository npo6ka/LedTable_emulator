#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "timer.h"

#define DEF_TIME_VAL 60

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    initTimer();
    initRand();
    timer_start();
    randomInit();

    this->setStyleSheet("background-color: black;");

    QLayout *but_mas = MainWindow::initButtonMassive();
    QLayout *con_pan = MainWindow::initControlPanel();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(but_mas);
    mainLayout->addLayout(con_pan);
    setLayout(mainLayout);

    init_leds(buttons);
    initMatrix();
    effects = new EffectsList();
}

void MainWindow::initTimer()
{
    tmr = new QTimer();
    connect(tmr, SIGNAL(timeout()), this, SLOT(on_tick()));
    setTimerInterval(DEF_TIME_VAL);
}

void MainWindow::setTimerInterval(double val)
{
    tmr->stop();
    if (val > 0) {
        tmr->setInterval(1000.0 / val);
        tmr->start();
    }
}

QLayout *MainWindow::initButtonMassive()
{
    QGridLayout *layout = new QGridLayout;
    const QSize btnSize = QSize(50, 50);
    const QColor *bgColor = new QColor(0, 0, 255);
    buttons.reserve(WIDTH * HEIGHT);
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            QPushButton *button = new QPushButton(QString("%1").arg(i * size + j));
            button->setFixedSize(btnSize);
            button->setStyleSheet(QString("background-color: %1").arg(bgColor->name()));

            buttons << button;
            layout->addWidget(button, i, j);
        }
    }

    return layout;
}

QLayout *MainWindow::initControlPanel()
{
    QVBoxLayout *layout = new QVBoxLayout;
    QLayout *debug = MainWindow::initDebugInfo();
    QLayout *controls =MainWindow::initControlButton();
    QLayout *mode = MainWindow::initModeButton();

    layout->addLayout(debug);
    layout->addLayout(mode);
    layout->addLayout(controls);


    return layout;
}

QLayout *MainWindow::initModeButton()
{
    QHBoxLayout *layout = new QHBoxLayout;
    QPushButton *left_button = new QPushButton(QString("<<"));
    QPushButton *right_button = new QPushButton(QString(">>"));

    connect(left_button, SIGNAL (released()), this, SLOT (handlePrevModeButton()));
    connect(right_button, SIGNAL (released()), this, SLOT (handleNextModeButton()));

    QString qss = QString("background-color: %1").arg("white");
    left_button->setStyleSheet(qss);
    right_button->setStyleSheet(qss);

    layout->addWidget(left_button);
    layout->addWidget(right_button);

    return layout;
}

QLayout *MainWindow::initControlButton()
{
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *left_button = new QPushButton(QString("<"));
    QPushButton *right_button = new QPushButton(QString(">"));
    QPushButton *up_button = new QPushButton(QString("^"));
    QPushButton *down_button = new QPushButton(QString("v"));
    QPushButton *middle_button = new QPushButton(QString("○"));

    QHBoxLayout *fline = new QHBoxLayout;
    QHBoxLayout *sline = new QHBoxLayout;
    QHBoxLayout *tline = new QHBoxLayout;

    fline->addWidget(up_button);
    sline->addWidget(left_button);
    sline->addWidget(middle_button);
    sline->addWidget(right_button);
    tline->addWidget(down_button);

    QString qss = QString("background-color: %1").arg("white");
    up_button->setStyleSheet(qss);
    left_button->setStyleSheet(qss);
    middle_button->setStyleSheet(qss);
    right_button->setStyleSheet(qss);
    down_button->setStyleSheet(qss);

    connect(left_button, SIGNAL (released()), this, SLOT (handleLeftContButton()));
    connect(right_button, SIGNAL (released()), this, SLOT (handleRightContButton()));
    connect(up_button, SIGNAL (released()), this, SLOT (handleUpContButton()));
    connect(down_button, SIGNAL (released()), this, SLOT (handleDownContButton()));
    connect(middle_button, SIGNAL (released()), this, SLOT (handleMidContButton()));

    layout->addLayout(fline);
    layout->addLayout(sline);
    layout->addLayout(tline);
    return layout;
}

QLayout *MainWindow::initDebugInfo()
{
    QVBoxLayout *layout = new QVBoxLayout;
    QCheckBox *checkbox = new QCheckBox("debug label", this);
    checkbox->setChecked(false);

    QDoubleSpinBox *spinbox = new QDoubleSpinBox;
    spinbox->setMinimum(0);
    spinbox->setMaximum(120);
    spinbox->setValue(DEF_TIME_VAL);

    connect(checkbox, SIGNAL(clicked(bool)), this, SLOT(checkboxDebugClicked(bool)));
    connect(spinbox, SIGNAL(valueChanged(double)), this, SLOT(spinboxValueChanged(double)));

    QString qss = QString("background-color: %1").arg("white");
    checkbox->setStyleSheet(qss);
    spinbox->setStyleSheet(qss);

    layout->addWidget(checkbox);
    layout->addWidget(spinbox);


    return layout;
}

void MainWindow::initRand()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}

void MainWindow::on_tick()
{
    Effect *eff = effects->getCurEffect();
    eff->on_update();
    eff->on_render();
}

MainWindow::~MainWindow() {}

void MainWindow::handlePrevModeButton()
{
    effects->prevEffect();
}

void MainWindow::handleNextModeButton()
{
    effects->nextEffect();
}

void MainWindow::handleLeftContButton()
{
    qDebug() << "left control";
}

void MainWindow::handleRightContButton()
{
    qDebug() << "right control";
}

void MainWindow::handleUpContButton()
{
    qDebug() << "up control";
}

void MainWindow::handleDownContButton()
{
    qDebug() << "down control";
}

void MainWindow::handleMidContButton()
{
    qDebug() << "middle control";
}

void MainWindow::checkboxDebugClicked(bool flag)
{
    set_debug_text_flag(flag);
}

void MainWindow::spinboxValueChanged(double val)
{
    setTimerInterval(val);
}




