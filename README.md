# ESP-01-Wifi-Scanner
Scans for wireless networks and displays resuts on a SSD1306 oled display.

This is a work in progress.  After scanning for wifi networks and showing results including SSID, signal level, and if
encryption is enabled the device will go to deep sleep mode. The code is designed for and ESP-01 and a SSD1306  oled
display, but will work on any ESP model and should be adaptable to other dispays without much trouble.

The circuit uses a PNP transistor with the base on the TX-pin of the ESP, the emitter goes to the common 3.3V power, and
the collector connects to the 3.3V power on the display.  A momentary switch attached to ground and the RST-pin is needed
to wake the device from sleep. Other connections SDA/SCL etc.. are in the code...

Fritzing files are included.  The breadboad secion is fine, but the scematic secion still needs to be cleaned up and I
have not even looked at the PCB layout...

There are bugs for sure. I'd love to hear about them, ESPecially if you have a fix for it.
