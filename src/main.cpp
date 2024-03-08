//
// Created by nikju on 28.01.2024.
//
#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include "network/web.h"
#include "LittleFS.h"
#include "network/wifi.h"
#include "constants.h"
#include "hardware/hall_sensor.h"
#include "hardware/steppers.h"
#include "application.h"
#include "network/protocol/server/udp.h"
#include "network/protocol/server/ws.h"
#include "misc/ntp_time.h"

#define DEBUG




hall_sensor HallTop(TOP_HALL_PIN);
hall_sensor HallBottom(BOTTOM_HALL_PIN);
steppers Steppers(STEPPER_PIN1,STEPPER_PIN2,STEPPER_PIN3,STEPPER_PIN4, MAX_SPEED, HallTop, HallBottom);

Timer global_timer;
//Storage<Config> config_storage(global_timer, "config", STORAGE_CONFIG_VERSION);
Application app(Steppers);

WifiManager wifiMan;
MDNSResponder mdns;
WebServer server;
UdpServer udp_server(app);
WebSocketServer ws_server(app);

NtpTime ntp_time;

int moveDir = 0;

void setup() {
    Serial.begin(115200);
    wifiMan.connect(WIFI_MODE, 5000);
    mdns.begin("AutoRoll", WiFi.localIP());
//    Steppers.attach_bottom_hall(HallBottom);
//    Steppers.attach_upper_hall(HallTop);
    if (!LittleFS.begin()) {
        D_PRINTF("cannot init littleFS");
    }

    udp_server.begin(UDP_PORT);
    ws_server.begin(server);

    server.on("/debug", HTTP_GET, [](AsyncWebServerRequest *request) {
        char result[320] = {};

        size_t offset = snprintf(result, sizeof(result), "General:\nHeap: %u\nNow: %lu\nTime: %lu\n",
                                 ESP.getFreeHeap(), millis(), ntp_time.epoch_tz());

        request->send_P(200, "text/plain", result);
    });


    server.begin();

    ArduinoOTA.setHostname(MDNS_NAME);
    ArduinoOTA.begin();

    app.change_state(AppState::NORMAL);
}

void loop() {
    ntp_time.update();
    ArduinoOTA.handle();
    Steppers.tick();
    wifiMan.handle_connection();
    global_timer.handle_timers();
    udp_server.handle_incoming_data();
    ws_server.handle_incoming_data();
};


