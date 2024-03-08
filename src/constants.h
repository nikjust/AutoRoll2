#pragma once

#include "sys_constants.h"

// HALL_TOP is pin of hall sensor on top of your window
// HALL_BOTTOM is pin of hall sensor in bottom of your window
#define TOP_HALL_PIN                            5
#define BOTTOM_HALL_PIN                         4

#define STEPPER_PIN1 14
#define STEPPER_PIN2 13
#define STEPPER_PIN3 12
#define STEPPER_PIN4 15
#define MAX_SPEED 200

#define MAX_STEPS_COUNT 30000 // In case of hardware broke, for stepper protection

#define WIFI_MODE                               (WIFI_STA_MODE)
#define WIFI_SSID                               ""
#define WIFI_PASSWORD                           ""

#define WIFI_CONNECTION_CHECK_INTERVAL          (5000u)                 // Interval (ms) between Wi-Fi connection check
#define WIFI_MAX_CONNECTION_ATTEMPT_INTERVAL    (0u)                    // Max time (ms) to wait for Wi-Fi connection before switch to AP mode
                                                                        // 0 - Newer switch to AP mode

#define TIME_ZONE                               (5.f)                   // GMT +5:00

#define MDNS_NAME                               "autorolls"