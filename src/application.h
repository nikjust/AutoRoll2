#pragma once

#include "config.h"
#include "misc/storage.h"
#include "night_mode.h"
#include "hardware/steppers.h"

class Application {
public:
    unsigned long state_change_time = 0;
    AppState state = AppState::INITIALIZATION;
    steppers &stp;

    explicit Application(steppers &stp);
    explicit Application(Application &_app);

    void change_state(AppState s);
//    void load();
//    void update();

    void restart();

};