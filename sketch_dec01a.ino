
#include <DHT.h>
#include <ArduinoJson.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
}

void loop() {
  int flameValue = digitalRead(3);
  int gasValue = digitalRead(4);
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if(flameValue == 1 && gasValue == 1 && !isnan(humidity) && temperature >=50.0){
    StaticJsonDocument<200> doc;
    
    doc["status"] = 415;
    doc["flameValue"] = flameValue;
    doc["gasValue"] = gasValue;
    doc["humidity"] = humidity;
    doc["temperature"] = temperature;

    char jsonBuffer[200];
    serializeJson(doc, jsonBuffer);

    Serial.println(jsonBuffer);
  } 
  else {
    Serial.println("Sensors not in desired state.");
    Serial.print("Flame Sensor Value: ");
    Serial.println(flameValue);
    Serial.print("Gas Sensor Value: ");
    Serial.println(gasValue);
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
  }
delay(5000);
}
