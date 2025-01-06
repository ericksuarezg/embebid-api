
#include "MqttManager.h"

// Constructor
MqttManager::MqttManager(const char* user, const char* password, const char* clientId)
    : mqttUser(user), mqttPassword(password), mqttClientId(clientId), client(espClient) {
    mqttServer = "aguisu.com"; // Ajusta el servidor según sea necesario
    mqttPort = 7080;           // Ajusta el puerto según sea necesario
    mqttConnected = false;
}

void MqttManager::setupConnection() {
    client.setServer(mqttServer, mqttPort);
    client.setCallback([this](char* topic, byte* payload, unsigned int length) {
        this->messageCallback(topic, payload, length);
    });
}

void MqttManager::connectToMqtt() {
    while (!client.connected()) {
        Serial.println("Attempting MQTT connection...");
        if (client.connect(mqttClientId, mqttUser, mqttPassword)) {
            Serial.println("Connected to MQTT broker");
            mqttConnected = true;
            client.subscribe(mqttUser);
        } else {
            Serial.print("Failed to connect. State: ");
            Serial.println(client.state());
            delay(5000);
        }
    }
}

String MqttManager::ensureMqttConnection() {
    if (!client.connected()) {
        Serial.println("MQTT connection lost. Reconnecting...");
        connectToMqtt();
        return "Reconnected to MQTT"; // Indica que se tuvo que reconectar
    } else {
        return "No issues"; // Mensaje general para reutilización
    }
}

void MqttManager::messageCallback(char* topic, byte* payload, unsigned int length) {
    String message = "";
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.println("Message received: " + message);
}

void MqttManager::publishData(float tempDHT, float humidity, float tempDS18) {
    DynamicJsonDocument jsonDoc(256);
    jsonDoc["typeMessage"] = "messageCurrent";
    jsonDoc["deviceId"] = mqttClientId;

    JsonObject data = jsonDoc.createNestedObject("data");
    JsonArray header = data.createNestedArray("header");
    header.add("Temperature DHT22");
    header.add("Humidity");
    header.add("Temperature DS18B20");

    JsonArray body = data.createNestedArray("body");
    body.add(tempDHT);
    body.add(humidity);
    body.add(tempDS18);

    String jsonString;
    serializeJson(jsonDoc, jsonString);

    client.publish(mqttClientId, jsonString.c_str());
    Serial.println("Data published to MQTT.");
}

void MqttManager::handleClientLoop() {
    client.loop();
}

String MqttManager::getLastMessage(char* topic, byte* payload, unsigned int length) {
    String message = "";
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    return message;
}


