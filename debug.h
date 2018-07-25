#ifndef DEBUG_H
#define DEBUG_H


#define DEBUG
//#define DEBUG
#ifdef DEBUG
    #include <QDebug>
    #define out(...) qDebug( __VA_ARGS__ );
#else
    #define out(...) ;
#endif

#endif // DEBUG_H
