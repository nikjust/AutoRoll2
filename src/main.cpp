//
// Created by nikju on 28.01.2024.
//

#include <main.h>
#include <Arduino.h>
#include <AccelStepper.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <LittleFS.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>


// Write your hall sensors pins:
// HALL_TOP is pin of hall sensor on top of your window
// HALL_BOTTOM is pin of hall sensor in bottom of your window
#define HALL_TOP 5
#define HALL_BOTTOM 4
// Define your Stepper here:
#define Stepper_pin1 14
#define Stepper_pin2 13
#define Stepper_pin3 12
#define Stepper_pin4 15
#define Max_speed 200
// Write your wi-fi settings:
const char *ssid = "ssid here";
const char *password = "password here";

#define DEBUG 1

AccelStepper stepper(AccelStepper::FULL4WIRE, Stepper_pin1, Stepper_pin2, Stepper_pin3, Stepper_pin4);
MDNSResponder mdns;
AsyncWebServer server(80);

int moveDir = 0;

void setup() {
#ifdef DEBUG
    Serial.begin(9600);
#endif
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
#ifdef DEBUG
        Serial.println(".");
#endif
    }
    mdns.begin("AutoRoll", WiFi.localIP());

    pinMode(14, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    pinMode(15, OUTPUT);

    stepper.setMaxSpeed(Max_speed);

    if (!LittleFS.begin()) {
#ifdef DEBUG
        Serial.println("Unable to initialize FS");
#endif
    }

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/index.html", "text/html");
    });

    server.serveStatic("/", LittleFS, "/");
    server.on("/open", HTTP_GET, [](AsyncWebServerRequest *request) {
        moveDir = 1;
        request->send(200, "ok");
    });
    server.on("/close", HTTP_GET, [](AsyncWebServerRequest *request) {
        moveDir = -1;
        request->send(200, "ok");
    });


    server.begin();
#ifdef DEBUG
    Serial.println("HTTP server started");
#endif
}

void loop() {
    if (moveDir > 0 && digitalRead(HALL_TOP)) { // If curtains opens
        stepper.move(5000);
    } else if (moveDir < 0 && digitalRead(HALL_BOTTOM)) { // If curtains closes
        stepper.move(-5000);
    } else if (moveDir != 0) { // If curtains need to stop
        moveDir = 0;
        stepper.setCurrentPosition(stepper.targetPosition());
    }

    if (!stepper.run()) { // If stepper stopped
        digitalWrite(14, LOW);
        digitalWrite(12, LOW);
        digitalWrite(13, LOW);
        digitalWrite(15, LOW);
        // Bad way to fix stepper overheating
    };

}
