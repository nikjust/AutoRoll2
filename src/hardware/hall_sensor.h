//
// Created by dp on 23.02.2024.
//

#ifndef AUTOROLLS_HALL_SENSOR_H
#define AUTOROLLS_HALL_SENSOR_H


class hall_sensor {
private:
    unsigned short int pin;
public:
    explicit hall_sensor(char pin);
    bool state() const;

    void attachInterruption(void(function)(void *), void *arg) const;
};


#endif //AUTOROLLS_HALL_SENSOR_H
