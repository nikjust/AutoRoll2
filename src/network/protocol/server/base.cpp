#include "base.h"

#include "application.h"

ServerBase::ServerBase(Application &app) : _app(app), _protocol() {
    //_app.stp = app.stp;
}

Response ServerBase::handle_packet_data(const uint8_t *buffer, uint16_t length) {
    const auto parseResponse = _protocol.parse_packet(buffer, length);
    if (!parseResponse.success) return parseResponse.response;

    const auto [header, data] = parseResponse.packet;

    if (header->type >= PacketType::DISCOVERY) {
        auto response = process_command(*header);
        return response;
    } else {
        auto response = update_parameter(*header, data);
        //app().update();
        return response;
    }
}

Response ServerBase::update_parameter(const PacketHeader &header, const void *data) {
    switch (header.type) {
        default:
            D_PRINTF("Unable to update value, bad type: %u\n", (uint8_t) header.type);
            return Response::code(ResponseCode::BAD_COMMAND);
    }
}

Response ServerBase::process_command(const PacketHeader &header) {
    bool success = true;

    switch (header.type) {
        case PacketType::RESTART:
            app().restart();
            break;
        case PacketType::OPEN:
            D_PRINT("Should start open");
            this->_app.stp.open();
            break;
        case PacketType::CLOSE:
            D_PRINT("Should start close");
            this->_app.stp.close();
            break;

        case PacketType::DISCOVERY:
            break;

        default:
            D_PRINTF("Unknown command: %u\n", (uint8_t) header.type);
            success = false;
    }

    if (success) D_PRINTF("Command %u\n", (uint8_t) header.type);

    return Response::code(success ? ResponseCode::OK : ResponseCode::BAD_COMMAND);
}

template<typename T>
Response serialize(const T &obj) {
    return Response{ResponseType::BINARY, {.buffer = {.size = sizeof(obj), .data=(uint8_t *) &obj}}};
}

Response ServerBase::process_data_request(const PacketHeader &header) {
    switch (header.type) {
//        case PacketType::SCHEDULE:
//            return serialize_fx_config(ColorEffects.config());
        default:
            return Response{ResponseType::CODE, {.code = ResponseCode::BAD_COMMAND}};
    }
}

