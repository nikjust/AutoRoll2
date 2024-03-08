//
// Created by dp on 23.02.2024.
//

#include "Arduino.h"
#include "hall_sensor.h"

bool hall_sensor::state() const {
    return digitalRead(this->pin);
}

void hall_sensor::attachInterruption(void(*function)(void *), void *arg) const {
    attachInterruptArg(this->pin, function, arg, FALLING);
}

hall_sensor::hall_sensor(char pin) {
    this->pin = pin;
}
