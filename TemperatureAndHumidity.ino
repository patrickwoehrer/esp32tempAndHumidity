#include <SimpleDHT.h>

SimpleDHT11 dht11(26);

void setup() {
  Serial.begin(115200);
}

void loop() {
  float temperature = 0;
  float humidty = 0;
  int err = SimpleDHTErrSuccess;

  if((err=dht11.read2(&temperature, &humidty, NULL)) != SimpleDHTErrSuccess){
    Serial.print("Read DHT11 failed, err=");
    Serial.println(err);
    delay(2000);
    return;
  }
  Serial.println();
  Serial.printf("Temp %.0f", temperature);
  Serial.print("°C \n");
  Serial.printf("Humidity %.0f", humidty);
  Serial.printf("%%");
  Serial.println(); 
  delay(5000);
}
