/*
 * 
 * The MIT License (MIT)
 * 
 *
 * Copyright (c) 2018 by ThingPulse, Daniel Eichhorn
 * Copyright (c) 2018 by Fabrice Weinberg
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ThingPulse invests considerable time and money to develop these open source libraries.
 * Please support us by buying our products (and not the clones) from
 * https://thingpulse.com
 * 
 * 
 * ESP-01 Wifi Network Scanner v1.0
 * 
 * Copyright (c) 2020 by UncleGrumpy (Winford)
 * 
 * This is a WiFi network scanner written for the ESP-01 and ssd1306 oled.
 * This code was construced entirely from the examples provided by the standard and
 * imported libraries.
 *
 */

#include "ESP8266WiFi.h"
 
// Include the correct display library

// For a connection via I2C using the Arduino Wire include:
#include "SSD1306Wire.h"
// OR #include "SH1106Wire.h"

// splashscreen image
#include "images.h"

// Initialize the OLED display using Arduino Wire:
//SSD1306Wire display(0x3c, SDA, SCL);   // ADDRESS, SDA, SCL  -  SDA and SCL usually populate automatically based on your board's pins_arduino.h
SSD1306Wire display(0x3c, 0, 2);  // ADDRESS, SDA, SCL  -  If not, they can be specified manually.
// SSD1306Wire display(0x3c, SDA, SCL, GEOMETRY_128_32);  // ADDRESS, SDA, SCL, OLEDDISPLAY_GEOMETRY  -  Extra param required for 128x32 displays.
// SH1106 display(0x3c, SDA, SCL);     // ADDRESS, SDA, SCL

// Setup for deepSleep
int runs = 0;
int displayPin = 1;

void setup() {
  // disable board led to save power
//  pinMode(LED_BUILTIN, OUTPUT);
//  digitalWrite(LED_BUILTIN, HIGH);
  // Turn on and setup the display.
  pinMode(displayPin, OUTPUT);
  digitalWrite(displayPin, LOW);
  delay(10);
  display.init();
  display.flipScreenVertically();
  // SplashScreen
  display.setFont(ArialMT_Plain_16);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 0, "Uncle Grumpy's");
  display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 48, "Scanner v1.1  \u00ae" );
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(10, 128, String(millis()));
  // display the screen!
  display.display();
  // Setup wifi
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  display.setFont(ArialMT_Plain_10);
  delay(100);
}

void loop() {
  // clear the display
  display.clear();
  int l = 0;
  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  if (n == 0) {
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_24);
    display.drawString(64, 32, "No networks!");
    display.setFont(ArialMT_Plain_16);
  } else {
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    String netNum = String(String((n)) + " Networks Discovered:");
    display.drawString(0, l, netNum);
    l = l + 14;
    for (int i = 0; i < n; ++i) {
      // Print SSID, RSSI and encryption for each network found
      String netName = String((WiFi.SSID(i)));
      String netDb = String((WiFi.RSSI(i)));
      String netEnc = String(((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*" ));
      display.drawString(0, l, netName+" "+netDb+ "% "+netEnc );
      l = l + 14;
      }
  // write the buffer to the display
  display.display();
  }
 delay(10);
 runs = ++runs;
 if (runs == 7) {
  digitalWrite(displayPin, HIGH);
  ESP.deepSleep(0);
 }
}
