# MQTT Manager Library

Biblioteca para manejar conexiones MQTT y publicar datos en dispositivos IoT.

## Instalación

### Con PlatformIO
Agrega la siguiente línea a tu archivo `platformio.ini`:
```ini
lib_deps =
    https://github.com/tu_usuario/mqtt_manager_library.git
```

### Con Arduino IDE
1. Descarga este repositorio como un archivo ZIP.
2. Ve a `Sketch > Include Library > Add .ZIP Library` en Arduino IDE.
3. Selecciona el archivo descargado.

## Uso
Ejemplo básico de uso:

```cpp
#include <MqttManager.h>

MqttManager mqttManager("usuario", "contraseña", "id_cliente");

void setup() {
    Serial.begin(115200);
    mqttManager.setupConnection();
    mqttManager.connectToMqtt();
}

void loop() {
    mqttManager.handleClientLoop();
    delay(1000);
}
```

## Dependencias
- **WiFiManager**: Manejo de conexiones WiFi.
- **PubSubClient**: Cliente MQTT.
- **ArduinoJson**: Manejo de JSON.

## Licencia
MIT
