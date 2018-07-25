#include "tablemodes.h"

TableModes::TableModes() {}

void TableModes::addMode(Mode *mode)
{
    modes.push_back(mode);
    if (!modes.empty()) {
        modeInit();
    }
}

void TableModes::nextMode()
{
    if (!modes.empty()) {
        Mode *mode = modes.front();
        modes.pop_front();
        modes.push_back(mode);
        modeInit();
    }
}

void TableModes::prevMode()
{
    if (!modes.empty()) {
        Mode *mode = modes.front();
        modes.pop_front();
        modes.push_back(mode);
        modeInit();
    }
}

void TableModes::modeInit()
{
    if (!modes.empty()) {
        Mode *mode = modes.front();
        mode->on_clear();
        led_clear();
        mode->on_init();
    }
}

void TableModes::on_tick()
{
    if (!modes.empty()) {
        Mode *mode = modes.front();
        mode->on_tick();
    }
}
