//
// Created by dp on 23.02.2024.
//

#include "steppers.h"
#include "constants.h"

void steppers::stop() {
    this->direction = 0;
    this->stepper.moveTo(0);
    this->stepper.setCurrentPosition(0);
    digitalWrite(this->pin1, LOW);
    digitalWrite(this->pin2, LOW);
    digitalWrite(this->pin3, LOW);
    digitalWrite(this->pin4, LOW);

}

void steppers::on_open_interruption(void *arg) {
    auto *self = (steppers *) arg;

    if (self->direction > 0) {
        self->stop();
    }
}

void steppers::on_close_interruption(void *arg) {
    auto *self = (steppers *) arg;

    if (self->direction < 0) {
        self->stop();
    }
}

void steppers::close() {
    if (this->hall_bottom.state() == 0)
        return;

    this->direction = -1;
    this->stepper.move(-MAX_STEPS_COUNT);
    D_PRINT(String("Stepper ") + String(this->pin1) + "_" + String(this->pin2) + "_" + String(this->pin3) + "_" + String(this->pin4) + ":");
    D_PRINT("Close...");
}

void steppers::open() {
    if (this->hall_top.state() == 0)
        return;

    this->direction = 1;
    this->stepper.move(MAX_STEPS_COUNT);
    D_PRINT(String("Stepper ") + String(this->pin1) + "_" + String(this->pin2) + "_" + String(this->pin3) + "_" + String(this->pin4) + ":");
    D_PRINT("Open...");
}


steppers::steppers(unsigned short pin1, unsigned short pin2, unsigned short pin3, unsigned short pin4, int max_speed,hall_sensor &topHallSensor, hall_sensor &bottomHallSensor): hall_top(topHallSensor),
                                                                                                                                                                                 hall_bottom(bottomHallSensor) {
    this->stepper = AccelStepper(AccelStepper::FULL4WIRE, pin1, pin2, pin3, pin4);
    stepper.setMaxSpeed(max_speed);
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->pin3 = pin3;
    this->pin4 = pin4;
    this->hall_top = topHallSensor;
    this->hall_top.attachInterruption(on_open_interruption, this);
    this->hall_bottom = bottomHallSensor;
    this->hall_bottom.attachInterruption(on_close_interruption, this);
}

//void steppers::attach_upper_hall(hall_sensor &hallSensor) {
//    this->hall_top = hallSensor;
//    this->hall_top.attachInterruption(on_open_interruption, this);
//}
//
//void steppers::attach_bottom_hall(hall_sensor &hallSensor) {
//    this->hall_bottom = hallSensor;
//    this->hall_bottom.attachInterruption(on_close_interruption, this);
//}




