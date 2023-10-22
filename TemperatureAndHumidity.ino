#include <SimpleDHT.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include "tinyTimeR.hpp"

static tinyTimeR tt;

const int cScreenWidth = 128;    // OLED display width, in pixels
const int cScreenHeight = 32;    // OLED display height, in pixels
const int cScreenAdress = 0x3C;  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
const float cHumidityLimit = 60.0;

SimpleDHT11 dht11(26);
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void u8g2_prepare() {
  u8g2.setFont(u8g2_font_8x13_t_symbols);   //perfect for for temperature and humidity output: u8g2_font_8x13_t_symbols
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1); //black background and white font
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void setup() {
  Serial.begin(115200);

  //dispaly init
  u8g2.begin();
  u8g2_prepare();
}

void loop() {
  float temperature = 0;
  float humidity = 0; //max 60%
  int err = SimpleDHTErrSuccess;

  if ((err = dht11.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err=");
    Serial.println(err);
    delay(2000);
    return;
  }

//Printing values for evaluation
/*
  Serial.println();
  Serial.printf("Temp %.0f", temperature);
  Serial.print("°C \n");
  Serial.printf("Humidity %.0f", humidty);
  Serial.printf("%%");
  Serial.println();
*/
  //Integer values for display output 
  int temperatureInt = round(temperature);
  int humidityInt = round(humidity);

  //Output on display
  u8g2.clearBuffer();
  u8g2_prepare();
    if (humidity > cHumidityLimit) {
  } else {
  }
  u8g2.setCursor(0, 0);
  u8g2.print("Innen: " + String(temperatureInt) + "\xC2B0\C " + String(humidityInt) + "%");
  u8g2.drawStr(0, cScreenHeight * 0.5, "Aussen: ");
  u8g2.sendBuffer();

  delay(5000);
}
