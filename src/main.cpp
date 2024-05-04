#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

#include <string>

#include "PushButton.h"
#include "OnBoardLED.h"
#include "IRCamera.h"

#include "secrets.h"

// globals
const uint8_t BUTTON_PIN = 13; // GPIO13
const uint8_t I2C_DATA_PIN = 21; // GPIO21
const uint8_t I2C_CLOCK_PIN = 22; // GPIO22
const uint8_t CAMERA_I2C_ADDRESS = 0x58;

// objects
//PushButton button(BUTTON_PIN);
IRCamera camera(I2C_DATA_PIN, I2C_CLOCK_PIN, CAMERA_I2C_ADDRESS);
AsyncWebServer server(80);

ArRequestHandlerFunction sendCapture = [](AsyncWebServerRequest *request)
{
    auto snap = camera.snapshot();
    request->send(200, "text/plain", snap.to_string().c_str());
};

void setup() 
{
    Serial.begin(115200); // initialize serial communication

    //button.setup();

    camera.setup();

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("WiFi Failed!");
        while (1) delay(1000);
    }

    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    server.on("/", HTTP_GET, sendCapture);

    server.onNotFound([](AsyncWebServerRequest *request)
    {
        request->send(404, "text/plain", "Not found");
    });
    server.begin();
}

void loop() 
{

}
