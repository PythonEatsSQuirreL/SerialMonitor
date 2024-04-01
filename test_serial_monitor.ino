

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#if defined(ARDUINO_FEATHER_ESP32) // Feather Huzzah32
  #define TFT_CS         14
  #define TFT_RST        15
  #define TFT_DC         32

#elif defined(ESP8266)
  #define TFT_DC 4//D2
  #define TFT_CS 15//D8
  #define TFT_MOSI 13//D7
  #define TFT_RST 2//D4
  #define TFT_MISO 12//D6
  #define TFT_CLK 14//D5

#else
  // For the breakout board, you can use any 2 or 3 pins.
  // These pins will also work for the 1.8" TFT shield.
  #define TFT_DC 4//D2
  #define TFT_CS 15//D8
  #define TFT_MOSI 13//D7
  #define TFT_RST 2//D4
  #define TFT_MISO 12//D6
  #define TFT_CLK 14//D5
#endif


Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


float p = 3.1415926;

void setup(void) {
  Serial.begin(9600);
  while (!Serial) {
    ;//wait for serial port to connect
  }
  Serial.print(F("Hello! ST77xx TFT Test"));
  Serial.println("Starting ST7789 Diagnostics:");
  uint8_t x = tft.readcommand8(0x0F);  // RDDSDR AKA Read Display Self-Diagnostic per datasheet
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX); 
  x = tft.readcommand8(ST77XX_RDID1);
  Serial.print(" RDID1: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ST77XX_RDID2);
  Serial.print(" RDID2: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ST77XX_RDID3);
  Serial.print(" RDID3: 0x"); Serial.println(x, HEX);

  tft.init(240, 320);           // Init ST7789 320x240

  Serial.println(F("Initialized"));

  uint16_t time = millis();
  time = millis() - time;

  Serial.println(time, DEC);
  delay(500);

  // large block of text
  //tft.fillScreen(ST77XX_BLACK);
  delay(1000);
  testdrawtext("Serial Reader v1.0\n\nDesigned by\n\nPythonEatsSquirreL", ST77XX_RED);

  delay(5000);
  //tft.fillScreen(ST77XX_BLACK);
  testdrawtext("Please attach the\ndevice you want to\nmonitor", ST77XX_WHITE);

  Serial.println("done");
  delay(5000);
}

void loop() {
  //tft.invertDisplay(true);
  //delay(500);
  tft.invertDisplay(false);
  delay(100);//2500
  tft.setTextWrap(true);//false
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);//30 is 3rd row
  delay(100);

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  //tft.println(Serial.read());
  tft.println(Serial.readString());
  delay(2000);
  
}


void testdrawtext(char *text, uint16_t color) {
  tft.invertDisplay(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextSize(2);
  tft.setTextWrap(true);
  tft.print(text);
}





