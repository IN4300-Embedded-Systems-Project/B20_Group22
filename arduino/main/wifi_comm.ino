#include <WiFi.h>
#include <WebServer.h>

WebServer server;

#define WIFI_SSID "vivo Y19s"
#define WIFI_PASSWORD "vinod123"

void setupWiFi(void (*handleMove)(String), void (*handleStop)(), void (*handleLEDs)()) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("\nWiFi Connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.enableCORS();

    server.on("/move", [handleMove]() {
        String path = server.arg("path");  
        handleMove(path); 
        server.send(200, "text/plain", "Moving");
    });

    server.on("/stop", [handleStop]() {
        handleStop();
        server.send(200, "text/plain", "Stopped");
    });

    server.on("/leds", [handleLEDs]() {
        String type = server.arg("type");  
        handleLEDs(type);
        server.send(200, "text/plain", "LEDs toggled");
    })

    server.onNotFound([](){ server.send(404, "text/plain", "Not Found"); });

    server.begin();
}

void handleWiFiRequests() {
    server.handleClient();
}
