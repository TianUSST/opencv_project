#pragma once
#include <cstdint>

namespace PacketUtils {
    constexpr uint8_t IMAGE_PACKET = 0xA0;
    constexpr uint8_t COMMAND_PACKET = 0xB0;

    inline bool isImagePacket(uint8_t type) {
        return type == IMAGE_PACKET;
    }

    inline bool isCommandPacket(uint8_t type) {
        return type == COMMAND_PACKET;
    }
}