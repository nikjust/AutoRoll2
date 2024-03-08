//
// Created by dp on 23.02.2024.
//

#ifndef AUTOROLLS_STEPPERS_H
#define AUTOROLLS_STEPPERS_H


#include "AccelStepper.h"
#include "hall_sensor.h"

class steppers {
private:
    AccelStepper stepper;
    int direction = 0;
    IRAM_ATTR static void on_open_interruption(void *arg);
    IRAM_ATTR static void on_close_interruption(void *arg);
    void stop();
    unsigned short int pin1;
    unsigned short int pin2;
    unsigned short int pin3;
    unsigned short int pin4;
    hall_sensor hall_top;
    hall_sensor hall_bottom;
public:
    steppers(unsigned short int pin1,unsigned short int pin2,unsigned short int pin3,unsigned short int pin4, int max_speed,hall_sensor &topHallSensor, hall_sensor &bottomHallSensor);
//    void attach_upper_hall(hall_sensor &hallSensor);
//    void attach_bottom_hall(hall_sensor &hallSensor);
    void open();
    void close();
    inline void tick() { this->stepper.run();};
};


#endif //AUTOROLLS_STEPPERS_H
