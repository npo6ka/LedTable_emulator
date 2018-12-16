#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "timer.h"

#define DEF_TIME_VAL 400

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    initTimer();
    initRand();
    timer_start();
    randomInit();

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
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    setTimerInterval(DEF_TIME_VAL);
}

void MainWindow::setTimerInterval(int val)
{
    tmr->stop();
    if (val > 0) {
        tmr->setInterval((int) ((float) 10000 / val));
        tmr->start();
    }
}

QLayout *MainWindow::initButtonMassive()
{
    QGridLayout *layout = new QGridLayout;
    const QSize btnSize = QSize(50, 50);
    const QColor *bgColor = new QColor(0, 0, 255);

    buttons.reserve(WIDTH * HEIGHT);
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < HEIGHT; ++j) {
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
    checkbox->setChecked(true);

    QSpinBox *spinbox = new QSpinBox;
    spinbox->setMinimum(0);
    spinbox->setMaximum(1200);
    spinbox->setValue(DEF_TIME_VAL);

    connect(checkbox, SIGNAL(clicked(bool)), this, SLOT(checkboxDebugClicked(bool)));
    connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(spinboxValueChanged(int)));

    layout->addWidget(checkbox);
    layout->addWidget(spinbox);

    return layout;
}

void MainWindow::initRand()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}

void MainWindow::updateTime()
{
    effects->getCurEffect()->on_tick();
    effects->getCurEffect()->show();
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

void MainWindow::spinboxValueChanged(int val)
{
    setTimerInterval(val);
}




