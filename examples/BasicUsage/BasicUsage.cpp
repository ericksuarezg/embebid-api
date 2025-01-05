#include <Arduino.h>
#include <MqttManager.h>

// MQTT server configuration
const char* mqttUser = "user";         // Replace with your MQTT username
const char* mqttPassword = "password"; // Replace with your MQTT password
const char* mqttClientId = "client_id"; // Replace with your MQTT client ID

// Create an instance of the library
MqttManager mqttManager(mqttUser, mqttPassword, mqttClientId);

void setup() {
    Serial.begin(115200);
    Serial.println("Starting the system...");

    // Configure the MQTT connection
    mqttManager.setupConnection();
    mqttManager.connectToMqtt();
    Serial.println("MQTT connection configured.");
}

void loop() {
    // Simulate sensor data
    float temperature = 25.3;
    float humidity = 60.5;
    float temperatureDS18 = 22.8;

    // Publish data to the MQTT server
    mqttManager.publishData(temperature, humidity, temperatureDS18);

    // Handle incoming MQTT messages
    mqttManager.handleClientLoop();

    // Pause between publications
    delay(5000);
}
