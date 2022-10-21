//#include <SPI.h>
#include <stdint.h>
#include "DHT.h"
#define DHT11Pin PB0
#define DHTType DHT11
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h> 

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
DHT dht(DHT11Pin, DHTType);
String displayString;

#define OLED_RESET 4
Adafruit_SSD1306 display(128,64, &Wire ,OLED_RESET);
const unsigned char PROGMEM frame0 [] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x07, 0xff, 0x80, 
  0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xe0, 0x00, 0x00, 0x1f, 0xff, 0xfc, 
  0x00, 0x00, 0x00, 0x7f, 0xff, 0xf0, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0xff, 0xff, 
  0xf8, 0x00, 0x00, 0x7f, 0xff, 0xff, 0x00, 0x00, 0x01, 0xff, 0xff, 0xfc, 0x00, 0x00, 0xff, 0xff, 
  0xff, 0x80, 0x00, 0x03, 0xff, 0xff, 0xfe, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x07, 0xff, 
  0xff, 0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x07, 0xff, 0xff, 0xff, 0x00, 0x03, 0xff, 
  0xff, 0xff, 0xe0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x1f, 
  0xff, 0xff, 0xff, 0x80, 0x07, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0x07, 
  0xff, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0xff, 0xf8, 0x00, 
  0x3f, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xe0, 
  0x0f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xfe, 
  0x00, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x1f, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xff, 0xff, 0xff, 0xff, 
  0xf0, 0x1f, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xff, 
  0xff, 0x01, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 
  0xff, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 
  0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 
  0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1f, 0xff, 
  0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 
  0xff, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1f, 
  0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0x83, 
  0xff, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xe0, 
  0x0f, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 
  0x83, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 
  0xc0, 0x07, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xff, 0xff, 
  0xff, 0x01, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 
  0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 
  0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xff, 0xff, 
  0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0xff, 
  0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x7f, 
  0xff, 0xff, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x00, 
  0x3f, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 
  0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xe0, 0x00, 0x0f, 0xff, 0xff, 0xe0, 0x00, 
  0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xff, 0x80, 
  0x00, 0x03, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x7f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 
  0x00, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


const unsigned char PROGMEM frame1 [] = {
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x10, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x78, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 
  0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 
  0x00, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0xff, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1f, 0xfe, 0x00, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 
  0xff, 0x01, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x01, 0xff, 0xff, 0x80, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0x01, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x03, 
  0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0x00, 0x30, 0x00, 0x00, 0x0f, 0xff, 0xff, 0x83, 0xff, 0xff, 
  0xff, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x01, 
  0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x83, 0xff, 
  0xff, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x1f, 
  0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0x83, 
  0xff, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xe0, 
  0x0f, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 
  0x83, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 
  0xc0, 0x07, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x07, 0xff, 0xff, 0xff, 
  0xff, 0x01, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 
  0xff, 0x80, 0x03, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 
  0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0xff, 0x00, 0x01, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xff, 0xff, 
  0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xfe, 0x00, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0xff, 
  0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 0x7f, 
  0xff, 0xff, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x00, 
  0x3f, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 
  0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xe0, 0x00, 0x0f, 0xff, 0xff, 0xe0, 0x00, 
  0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xff, 0x80, 
  0x00, 0x03, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x7f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 
  0x00, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/*const unsigned char PROGMEM frame2 [] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x07, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x83, 0xe0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x83, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0x83, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x83, 0xfc, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x83, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x7f, 0x83, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x83, 
  0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x83, 0xff, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x03, 0xff, 0x83, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 
  0x83, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0x83, 0xff, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x83, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 
  0xff, 0x01, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x01, 0xff, 0xff, 0x80, 
  0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0x01, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x03, 
  0xff, 0xff, 0x01, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xfe, 0x00, 0xff, 0xff, 
  0xfe, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0xfc, 0x00, 0x7f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x03, 0xff, 0xff, 0xfc, 0x00, 0x7f, 
  0xff, 0xff, 0xfc, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x00, 
  0x3f, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 
  0x1f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xe0, 0x00, 0x0f, 0xff, 0xff, 0xe0, 0x00, 
  0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xff, 0x80, 
  0x00, 0x03, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x7f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 
  0x00, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};*/

const unsigned char PROGMEM frame3 [] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x40, 0x00, 0x00, 0x04, 0x00, 0x40, 
  0x00, 0x00, 0x04, 0x00, 0x00, 0x30, 0x00, 0x00, 0x08, 0x00, 0x20, 0x00, 0x00, 0x08, 0x00, 0x00, 
  0x38, 0x00, 0x00, 0x38, 0x00, 0x30, 0x00, 0x00, 0x38, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x70, 0x00, 
  0x1c, 0x00, 0x00, 0x70, 0x00, 0x00, 0x0f, 0x80, 0x01, 0xe0, 0x00, 0x0f, 0x00, 0x01, 0xe0, 0x00, 
  0x00, 0x07, 0xf0, 0x0f, 0xc0, 0x00, 0x07, 0xe0, 0x1f, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xff, 0x80, 
  0x00, 0x03, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x00, 0x7f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 
  0x00, 0x00, 0x00, 0x1f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
/*
const unsigned char PROGMEM frame4 [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x3f, 0xff, 0x00, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xc0, 
  0x00, 0x00, 0x3f, 0xff, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x7f, 0xff, 0xc0, 
  0x00, 0x00, 0x01, 0xff, 0xff, 0xf0, 0x00, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x03, 0xff, 0xff, 
  0xf8, 0x00, 0x03, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf8, 0x00, 0x03, 0xff, 0xff, 
  0xf8, 0x00, 0x00, 0x07, 0xff, 0xff, 0xfc, 0x00, 0x07, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x07, 0xff, 
  0xff, 0xfe, 0x00, 0x0f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xfe, 0x00, 0x1f, 0xff, 
  0xff, 0xfc, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x1f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x0f, 
  0xff, 0xff, 0xff, 0x00, 0x3f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x80, 0x3f, 
  0xff, 0xff, 0xfe, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xff, 0x00, 0x00, 
  0x1f, 0xff, 0xff, 0xff, 0xc0, 0x7f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xc0, 
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x00, 
  0x00, 0x3f, 0xff, 0xff, 0xff, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xff, 
  0xe1, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 
  0x80, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x3f, 0xff, 0xff, 
  0xff, 0xe1, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xf1, 0xff, 0xff, 0xff, 
  0xff, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x3f, 0xff, 
  0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 
  0xff, 0xff, 0x80, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x3f, 
  0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xf3, 0xff, 
  0xff, 0xff, 0xff, 0x80, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
  0x1f, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xf3, 
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0x00, 
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 
  0xe3, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xfe, 
  0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x07, 0xff, 0xff, 
  0xff, 0xe1, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xc1, 0xff, 0xff, 0xff, 
  0xfc, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x01, 0xff, 
  0xff, 0xff, 0xc0, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 
  0xff, 0xf0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x80, 0x7f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 
  0x7f, 0xff, 0xff, 0x00, 0x7f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0x00, 0x3f, 
  0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xfe, 0x00, 0x3f, 0xff, 0xff, 0x80, 0x00, 0x00, 
  0x00, 0x1f, 0xff, 0xfc, 0x00, 0x1f, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xf8, 0x00, 
  0x0f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xf0, 0x00, 0x07, 0xff, 0xfc, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xff, 0xc0, 0x00, 0x03, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 
  0x00, 0x00, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x80, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};*/

const unsigned char PROGMEM frame5 [] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xc0, 
  0x00, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf8, 0x00, 0x00, 0x00, 0x3f, 0xf8, 
  0x00, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x00, 0x00, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x03, 0xff, 
  0xff, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0x80, 0x00, 0x03, 0xff, 
  0xff, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xc0, 0x00, 0x07, 0xff, 0xff, 0x80, 0x00, 0x00, 0x0f, 
  0xff, 0xff, 0xe0, 0x00, 0x0f, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf0, 0x00, 0x1f, 
  0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xf8, 0x00, 0x1f, 0xff, 0xff, 0xe0, 0x00, 0x00, 
  0x3f, 0xff, 0xff, 0xf8, 0x00, 0x3f, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfc, 0x00, 
  0x7f, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfe, 0x00, 0x7f, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x7f, 0xff, 0xff, 0xfe, 0x00, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 
  0x00, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0xf8, 
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xff, 0xff, 
  0xff, 0x81, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0xff, 
  0xfc, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0x83, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x01, 0xff, 0xff, 
  0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 
  0xff, 0xfc, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x01, 0xff, 
  0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 
  0xff, 0xff, 0xfc, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x01, 
  0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xe7, 
  0xff, 0xff, 0xff, 0xfc, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xfc, 0x00, 
  0x01, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 
  0xe7, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xf8, 
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0xff, 0xff, 0xff, 
  0xff, 0xe7, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 
  0xf8, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x7f, 0xff, 
  0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 
  0xff, 0xf0, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x3f, 
  0xff, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x83, 0xff, 
  0xff, 0xff, 0xe0, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 
  0x0f, 0xff, 0xff, 0xff, 0x81, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0x00, 
  0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 
  0x00, 0x03, 0xff, 0xff, 0xfe, 0x00, 0x7f, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xfc, 
  0x00, 0x7f, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xfc, 0x00, 0x3f, 0xff, 0xfc, 0x00, 
  0x00, 0x00, 0x00, 0x7f, 0xff, 0xf8, 0x00, 0x1f, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 
  0xf0, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xe0, 0x00, 0x07, 0xff, 0xe0, 
  0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x80, 0x00, 0x03, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xfc, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.display();
  display.clearDisplay();
  display.setTextSize(0);
  dht.begin();
  //display.setFont();
  Serial.begin(9600);  
  display.setTextColor(WHITE);
  displayString.reserve(10);
}

void loop() {

  blink();
  blink();
  left_side();
  blink();
  blink();
  right_side();
  blink();
  disp_dht();
}

void blink(){
int8_t xx=20;
int8_t yy=8;
int8_t x=45;
int8_t y = 40;
display.clearDisplay();
display.drawBitmap(xx, yy,frame0,86,55, 1);
display.fillCircle(x, y, 10,BLACK);
display.fillCircle(x+38, y, 10,BLACK);
display.display();
delay(2000);

display.clearDisplay();
display.drawBitmap(xx, yy,frame1,86,55, 1);
display.fillCircle(x, y, 10,BLACK);
display.fillCircle(x+38, y, 10,BLACK);
display.display();
delay(30);

display.clearDisplay();
display.drawBitmap(xx, yy,frame1,86,55, 1);
display.fillCircle(x, y, 10,BLACK);
display.fillCircle(x+38, y, 10,BLACK);
display.display();
delay(3);

display.clearDisplay();
display.drawBitmap(xx, yy,frame3,86,55, 1);
display.fillCircle(x, y, 10,BLACK);
display.fillCircle(x+38, y, 10,BLACK);
display.display();
delay(100);

display.clearDisplay();
display.drawBitmap(xx, yy,frame1,86,55, 1);
display.fillCircle(x, y, 10,BLACK);
display.fillCircle(x+38, y, 10,BLACK);
display.display();
delay(3);

display.clearDisplay();
display.drawBitmap(xx, yy,frame1,86,55, 1);
display.fillCircle(x, y, 10,BLACK);
display.fillCircle(x+38, y, 10,BLACK);
display.display();
delay(30);

display.clearDisplay();
display.drawBitmap(xx, yy,frame0,86,55, 1);
display.fillCircle(x, y, 10,BLACK);
display.fillCircle(x+38, y, 10,BLACK);
display.display();
delay(2000);
}

void right_side() {/////////////////////////////////////////////////////////////////////////////
int8_t x=45;
int8_t y = 40;
display.clearDisplay();
display.drawBitmap(20, 8,frame0,86,55, 1);
display.fillCircle(x, y, 10,BLACK);
display.fillCircle(x+38, y, 10,BLACK);
display.display();
delay(1000);

for (int8_t i=20 ; i < 45 ; i=i+5)
{
display.clearDisplay();
display.drawBitmap(i, 8,frame0,86,55, 1);
display.fillCircle(x+i-10, y, 10,BLACK);
display.fillCircle(i+x+38-10, y, 10,BLACK);
display.display();
delay(2);
}

display.clearDisplay();
display.drawBitmap(40, 8,frame5,86,55, 1);
display.fillCircle(x+32, y, 10,BLACK);
display.fillCircle(x+38+30, y, 10,BLACK);
display.display();
delay(3000);

for (int8_t i=45 ; i >= 20 ; i=i-5)
{
display.clearDisplay();
display.fillCircle(x+i-13, y, 10,BLACK);
display.fillCircle(i+x+38-13, y, 10,BLACK);
display.drawBitmap(i, 8,frame0,86,55, 1);
display.display();
delay(2);
}
display.clearDisplay();
display.drawBitmap(20, 8,frame0,86,55, 1);
display.fillCircle(x, y, 10,BLACK);
display.fillCircle(x+38, y, 10,BLACK);
display.display();
delay(1000);
}

void left_side() {///////////////////////////////////////////////////////////////
int8_t x=45;
int8_t y = 40;
display.clearDisplay();
display.drawBitmap(20, 8,frame0,86,55, 1);
display.fillCircle(x, y, 10,BLACK);
display.fillCircle(x+38, y, 10,BLACK);
display.display();
delay(1000);

for (int8_t i=20 ; i >= 5 ; i=i-5)
{
display.clearDisplay();
display.drawBitmap(i, 8,frame0,86,55, 1);
display.fillCircle((x-(x-i))+20, y, 10,BLACK);
display.fillCircle(((x-(x-i))+38)+20, y, 10,BLACK);
display.display();
delay(1);
}

display.clearDisplay();
display.drawBitmap(-13, 8,frame5,86,55, 1);
display.fillCircle(x-27, y, 10,BLACK);
display.fillCircle(x+38-30, y, 10,BLACK);
display.display();
delay(3000);

for (int8_t i=5 ; i < 20 ; i=i+5)
{
display.clearDisplay();
display.drawBitmap(i, 8,frame0,86,55, 1);
display.fillCircle((x-(x-i))+20, y, 10,BLACK);
display.fillCircle(((x-(x-i))+38)+20, y, 10,BLACK);
display.display();
delay(1);
}

display.clearDisplay();
display.drawBitmap(20, 8,frame0,86,55, 1);
display.fillCircle(x, y, 10,BLACK);
display.fillCircle(x+38, y, 10,BLACK);
display.display();
delay(1000);
}

void disp_dht(){
    byte temperature = dht.readTemperature();  
    byte humidity = dht.readHumidity();  
    display.clearDisplay();  
    display.setTextSize(1);  
    display.setTextColor(SSD1306_WHITE);  
    display.setCursor(0, 0);  
    display.print("  TEMP. & HUMIDITY");  
    display.setCursor(0, 25);  
    display.print(" TEMPERATURE : ");  
    display.setCursor(90, 25);  
    display.print((int)temperature);  
    display.setCursor(0, 50);  
    display.print(" HUMIDITY  : ");  
    display.setCursor(90, 50);  
    display.print((int)humidity);  
    display.display();  

 delay(5000) ;
}
