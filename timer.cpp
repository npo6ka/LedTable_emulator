#include <QTime>

static QTime myTimer;

void timer_start()
{
    myTimer.start();
}

unsigned long millis()
{
    return myTimer.elapsed();
}

unsigned long micros()
{
    return myTimer.elapsed() * 1000;
}
