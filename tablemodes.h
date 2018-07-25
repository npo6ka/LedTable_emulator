#ifndef TABLEMODES_H
#define TABLEMODES_H
#include "mode.h"
#include <list>
#include "animation00.h"

class TableModes
{
public:
    TableModes();
    void addMode(Mode *name);
    void nextMode();
    void prevMode();
    void on_tick();
private:
    void modeInit();
    std::list<Mode *> modes;
};

#endif // TABLEMODES_H
