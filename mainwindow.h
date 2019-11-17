#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QCheckBox>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QTime>
#include <QSpinBox>
//#include <led_lib.h>
//#include "tablemodes.h"
#include "Effects/effectslist.h"

class MainWindow : public QWidget
{
    Q_OBJECT
    QList<QPushButton*> buttons;
    QTimer *tmr;
    const int size = 10;
    //TableModes *modes;
    EffectsList *effects;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    static void initRand();
    void initTimer();
    QLayout *initButtonMassive();
    QLayout *initControlPanel();
    QLayout *initModeButton();
    QLayout *initControlButton();
    QLayout *initDebugInfo();
    void setTimerInterval(int val);
private slots:
    void on_tick();
    void handlePrevModeButton();
    void handleNextModeButton();
    void handleLeftContButton();
    void handleRightContButton();
    void handleUpContButton();
    void handleDownContButton();
    void handleMidContButton();
    void checkboxDebugClicked(bool flag);
    void spinboxValueChanged(int val);
};

#endif // MAINWINDOW_H
