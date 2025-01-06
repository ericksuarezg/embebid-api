#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <WiFiManager.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

class MqttManager {
private:
    WiFiClient espClient;
    PubSubClient client;

    const char* mqttServer;
    const char* mqttUser;
    const char* mqttPassword;
    const char* mqttClientId;
    int mqttPort;

    bool mqttConnected;

public:
    // Constructor
    MqttManager(const char* user, const char* password, const char* clientId);

    void setupConnection();
    String connectToMqtt();
    String ensureMqttConnection();
    String messageCallback(char* topic, byte* payload, unsigned int length);
    void publishData(float tempDHT, float humidity, float tempDS18);
    void handleClientLoop();
    String getLastMessage(char* topic, byte* payload, unsigned int length);
};

#endif



