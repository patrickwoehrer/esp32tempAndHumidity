#include <SimpleDHT.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

const int c_screen_width = 128;    // OLED display width, in pixels
const int c_screen_height = 32;    // OLED display height, in pixels
const int c_screen_adress = 0x3C;  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

SimpleDHT11 dht11(26);

void u8g2_prepare() {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void setup() {
  Serial.begin(115200);

  u8g2.begin();
  u8g2_prepare();
}

void loop() {
  float temperature = 0;
  float humidty = 0;
  int err = SimpleDHTErrSuccess;

  if ((err = dht11.read2(&temperature, &humidty, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err=");
    Serial.println(err);
    delay(2000);
    return;
  }

  temperature = round(temperature);
  humidty = round(humidty);

  Serial.println();
  Serial.printf("Temp %f", temperature);
  Serial.print("°C \n");
  Serial.printf("Humidity %f", humidty);
  Serial.printf("%%");
  Serial.println();

  u8g2.clearBuffer();
  u8g2_prepare();
  //u8g2.drawStr(0, 0, "Temperatur: ");
  u8g2.setCursor(0, 0);
  u8g2.print("Temperatur: " + String(temperature) + "°C");
  //u8g2.drawStr(0, c_screen_height * 0.33, "Luftfeuchtigkeit: ");
  u8g2.setCursor(0, c_screen_height * 0.33);
  u8g2.print("Luftfeuchtigkeit: " + String(humidty) + "%%");
  u8g2.drawStr(0, c_screen_height * 0.66, "Aussentemperatur: ");
  u8g2.sendBuffer();

  delay(5000);
}
