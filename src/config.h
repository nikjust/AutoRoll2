#pragma once

#include <cctype>

class NtpTime;

enum class AppState {
    INITIALIZATION,
    NORMAL
};

struct __attribute ((packed)) Config {
    uint8_t max_speed = 200;
};