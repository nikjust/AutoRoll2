#pragma once

#include <cctype>

enum class PacketType : uint8_t {
    // COMMANDS
    OPEN = 201,

    CLOSE = 202,

    DISCOVERY = 200,

    RESTART = 222,
};