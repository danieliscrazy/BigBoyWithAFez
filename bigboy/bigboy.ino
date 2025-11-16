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
  if (irrecv.decode(&results)) {
    if (results.value != 0xFFFFFFFF)
    {
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
      Serial.println(results.value, HEX);
    }
    irrecv.resume();
  }
  delay(100);
}
