#include <DHT.h>
#include <ArduinoJson.h>

#define DHT_PIN 2     // Digital pin for DHT11 humidity/temperature sensor
#define MOISTURE_PIN 0 // Analog pin for VMA303 moisture sensor
#define STATUS_GOOD 0
#define STATUS_BAD_DHT 1
#define STATUS_BAD_MOISTURE 2

int iters = 0;

DHT dht(DHT_PIN, DHT11);

void setup() {
  Serial.begin(9600);
  dht.begin();
  // Wait a few seconds
  delay(2000);
}

void loop() {

  StaticJsonBuffer<512> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  int sensor_status = 0;
  unsigned long interval = 1000L* 60L * 15L; // Every 15 min
  int moisture = analogRead(MOISTURE_PIN);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float humidity = dht.readHumidity();
  float farenheit = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(farenheit)) {
    sensor_status |= STATUS_BAD_DHT;
  } else {
    float heat_idx = dht.computeHeatIndex(farenheit, humidity);
    root["humidity"] = humidity;
    root["temperature"] = farenheit;
    root["heat_index"] = heat_idx;
  }

 if (isnan(moisture)) {
    sensor_status |= STATUS_BAD_MOISTURE;
  } else {
    root["moisture"] = moisture;
  }
  root["status"] = sensor_status;
  root.printTo(Serial);
  Serial.println();
  delay(interval);
}
