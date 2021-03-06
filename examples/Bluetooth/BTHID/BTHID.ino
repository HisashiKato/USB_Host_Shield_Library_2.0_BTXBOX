/*
 Example sketch for the HID Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
   
 Modified 18 July 2020 by HisashiKato
 Web      :  http://kato-h.cocolog-nifty.com/khweblog/
*/

#include <BTHIDa.h>
#include <usbhub.h>
#include "KeyboardParser.h"
#include "MouseParser.h"

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
//USBHub Hub1(&Usb); // Some dongles have a hub inside
BTDSSP Btdssp(&Usb); // You have to create the Bluetooth Dongle instance like so

/* You can create the instance of the class in two ways */
// This will start an inquiry and then pair with your device - you only have to do this once
BTHIDa bthida(&Btdssp, PAIR);

// After that you can simply create the instance like so
//BTHIDa bthida(&Btdssp);

KbdRptParser keyboardPrs;
MouseRptParser mousePrs;

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // Halt
  }

  bthida.SetReportParser(KEYBOARD_PARSER_ID, &keyboardPrs);
  bthida.SetReportParser(MOUSE_PARSER_ID, &mousePrs);

  // If "Boot Protocol Mode" does not work, then try "Report Protocol Mode"
  // If that does not work either, then uncomment PRINTREPORT in BTHIDa.cpp to see the raw report
  bthida.setProtocolMode(USB_HID_BOOT_PROTOCOL); // Boot Protocol Mode
  //bthida.setProtocolMode(HID_RPT_PROTOCOL); // Report Protocol Mode

  Serial.print(F("\r\nHID Bluetooth Library Started"));
}
void loop() {
  Usb.Task();
}
