
#include "Arduino.h"
#include <MqttManager.h>


void setup() {
    Serial.begin(115200);
    Serial.println("Setup iniciado");
    
}

void loop() {
    Serial.println("Loop en ejecución");
    delay(1000);
}

