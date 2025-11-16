
// 2025 Daniel Davidson/danieliscrazy for Big Boy with a Fez for the HackNYU hackathon. Licensed under the GNU GPLv3. AI was used for debugging purposes, but did not directly generate code.

#include <IRremote.h>
#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS     10
#define TFT_RST    9
#define TFT_DC     8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Servo neck;
int RECV_PIN = 11;
int SERVOPIN = 7;
IRrecv irrecv(RECV_PIN);
int incomingByte = 0;
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  neck.attach(SERVOPIN);
  neck.write(90);
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_WHITE);
  tft.fillRect(0, 0, 24, 160, ST77XX_WHITE);
  tft.fillCircle(24, 80, 80, ST77XX_BLACK);
  tft.fillCircle(24, 80, 70, ST77XX_WHITE);
  tft.fillRect(0, 0, 24, 160, ST77XX_WHITE);

}

void loop() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    if (incomingByte == 49) {
      tft.fillScreen(ST7735_WHITE);
      tft.fillCircle(24, 80, 80, ST77XX_BLACK);
      tft.fillCircle(24, 80, 70, ST77XX_WHITE);
      tft.fillRect(0, 0, 24, 160, ST77XX_WHITE);
    }
  }
  if (irrecv.decode(&results)) {
    if (results.value != 0xFFFFFFFF)
    {
      Serial.println(results.value, HEX);
      if (results.value == 0x20DFE01F)
      {
        neck.write(120);
      }
      if (results.value == 0x20DF609F)
      {
        neck.write(60);
      }
      if (results.value == 0x20DF22DD)
      {
        neck.write(90);
      }
      if (results.value == 0x20DF8877) // 1 button
      {
        tft.fillScreen(ST7735_WHITE);
        tft.fillCircle(24, 80, 80, ST77XX_BLACK);
        tft.fillCircle(24, 80, 70, ST77XX_WHITE);
        tft.fillRect(0, 0, 24, 160, ST77XX_WHITE);
      }
      if (results.value == 0x20DF48B7) // 2 button
      {
        tft.fillScreen(ST7735_WHITE);
        tft.fillCircle(104, 80, 80, ST77XX_BLACK);
        tft.fillCircle(104, 80, 70, ST77XX_WHITE);
        tft.fillRect(104, 0, 24, 160, ST77XX_WHITE);
      }
      if (results.value == 0x20DFC837) // 3 button
      {
        tft.fillScreen(ST7735_WHITE);
        tft.fillRect(54, 5, 20, 150, ST77XX_BLACK);
      }
      if (results.value == 0x20DF28D7 || results.value == 0x20DFE817 || results.value == 0x20DF18E7) // 4, 7, 8 buttons
      {
        tft.fillScreen(ST7735_WHITE);
        tft.fillCircle(24, 80, 80, ST77XX_BLACK);
        tft.fillCircle(24, 80, 70, ST77XX_WHITE);
        tft.fillRect(0, 0, 24, 160, ST77XX_WHITE);
        tft.fillRect(24, 0, 10, 160, ST77XX_BLACK);
      }
      if (results.value == 0x20DFA857) // 5 button
      {
        tft.fillScreen(ST7735_WHITE);
        tft.fillCircle(104, 80, 80, ST77XX_BLACK);
        tft.fillCircle(104, 80, 70, ST77XX_WHITE);
        tft.fillRect(104, 0, 24, 160, ST77XX_WHITE);
        tft.fillRect(94, 0, 10, 160, ST77XX_BLACK);
      }
      if (results.value == 0x20DF6897) // 6 button
      {
        tft.fillScreen(ST7735_WHITE);
        tft.fillRect(24, 5, 80, 150, ST77XX_BLACK);
        tft.fillRect(34, 15, 60, 130, ST77XX_WHITE);
      }
      if (results.value == 0x20DF9867) // 9 button
      {
        tft.fillScreen(ST7735_WHITE);
        tft.fillCircle(24, 80, 80, ST77XX_BLACK);
        tft.fillCircle(24, 80, 70, ST77XX_WHITE);
        tft.fillRect(0, 0, 24, 160, ST77XX_WHITE);
        tft.fillRect(24, 0, 10, 160, ST77XX_BLACK);
        delay(3000);
        neck.write(120);
        delay(800);
        neck.write(60);
        delay(1200);
        neck.write(90);
      }
    }
    irrecv.resume();
  }
  delay(100);
}
