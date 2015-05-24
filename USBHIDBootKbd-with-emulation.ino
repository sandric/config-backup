#include <hidboot.h>
#include <usbhub.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

#include "TimerOne.h"
#include "UsbKeyboard.h"

volatile uint8_t buttonPressed;
volatile uint8_t modPressed;
volatile uint8_t buttonToRepeat;
volatile uint8_t modToRepeat;
volatile uint8_t waitCycleCounter;

int waitTimeToStick = 20000;
int waitCyclesToStick = 12;
class KbdRptParser : 
public KeyboardReportParser
{
  void PrintKey(uint8_t key, uint8_t mod);

protected:
  virtual void OnControlKeysChanged(uint8_t before, uint8_t after);

  virtual void OnKeyDown(uint8_t mod, uint8_t key);
  virtual void OnKeyUp(uint8_t mod, uint8_t key); 
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{ 
  Serial.println("DN");
  PrintKey(key, mod);
 
  Timer1.stop();
  waitCycleCounter = 0;

  parseKeystroke(key, mod);
  
  UsbKeyboard.sendKeyStroke(buttonPressed, modPressed);

  Timer1.restart();
}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
  Serial.println("UP");
  PrintKey(key, mod);

  Timer1.stop();
  buttonPressed = 0;
  modPressed = 0;
};


void KbdRptParser::OnControlKeysChanged(uint8_t before, uint8_t after) {

  MODIFIERKEYS beforeMod;
  *((uint8_t*)&beforeMod) = before;

  MODIFIERKEYS afterMod;
  *((uint8_t*)&afterMod) = after;

  if (beforeMod.bmLeftCtrl != afterMod.bmLeftCtrl) {
    Serial.println("LeftCtrl changed");
  }
  if (beforeMod.bmLeftShift != afterMod.bmLeftShift) {
    Serial.println("LeftShift changed"); 
  }
  if (beforeMod.bmLeftAlt != afterMod.bmLeftAlt) {
    Serial.println("LeftAlt changed");
  }
  if (beforeMod.bmLeftGUI != afterMod.bmLeftGUI) {
    Serial.println("LeftGUI changed");
  }

  if (beforeMod.bmRightCtrl != afterMod.bmRightCtrl) {
    Serial.println("RightCtrl changed");
  }
  if (beforeMod.bmRightShift != afterMod.bmRightShift) {
    Serial.println("RightShift changed");
  }
  if (beforeMod.bmRightAlt != afterMod.bmRightAlt) {
    Serial.println("RightAlt changed");
  }
  if (beforeMod.bmRightGUI != afterMod.bmRightGUI) {
    Serial.println("RightGUI changed");
  }
};

void KbdRptParser::PrintKey(uint8_t key, uint8_t mod)
{
  Serial.print("key: ");
  Serial.println(key);
  Serial.print("modifier: ");
  Serial.println(mod);
};


void parseKeystroke(uint8_t key, uint8_t mod) {
  uint8_t buttonChanged, modChanged;
  if(mod == 0) {
    switch(key){
      case 51: buttonChanged = 20; modChanged = 1; break; //; - :
      case 30: buttonChanged = 30; modChanged = 2; break; //!
      case 31: buttonChanged = 35; modChanged = 2; break; //^
      case 32: buttonChanged = 33; modChanged = 2; break; //$
      case 33: buttonChanged = 37; modChanged = 2; break; //*
      case 34: buttonChanged = 36; modChanged = 2; break; //&
      case 35: buttonChanged = 49; modChanged = 2; break; //|
      case 36: buttonChanged = 32; modChanged = 2; break; //#
      case 37: buttonChanged = 31; modChanged = 2; break; //@
      case 38: buttonChanged = 34; modChanged = 2; break; //%
      case 39: buttonChanged = 56; modChanged = 2; break; //?
      
      case 45: buttonChanged = 49; modChanged = 0; break; //?
      
      case 47: buttonChanged = 51; modChanged = 2; break; //{ - ;
      
      case 49: buttonChanged = 14; modChanged = 1; break; //?
      
      //Make myself a pavlog-dog to push me using another buttons for enter/backspace/delete/tab
      //case 40: buttonChanged = 30; modChanged = 2; break; //!
      //case 42: buttonChanged = 30; modChanged = 2; break; //!
      //case 43: buttonChanged = 30; modChanged = 2; break; //!
      //case 76: buttonChanged = 30; modChanged = 2; break; //!
    }
  }
  if(mod == 2) {
    switch(key) {
      case 24: buttonChanged = 82; modChanged = 0; break; //LeftShift + U - up arrow
      case 17: buttonChanged = 80; modChanged = 0; break; //LeftShift + N - left arrow
      case 12: buttonChanged = 79; modChanged = 0; break; //LeftShift + I - right arrow
      case 8:  buttonChanged = 81; modChanged = 0; break; //LeftShift + E - down arrow
      
      case 15: buttonChanged = 74; modChanged = 0; break; //LeftShift + L - home
      case 28: buttonChanged = 77; modChanged = 0; break; //LeftShift + Y - end
      
      case 18: buttonChanged = 10; modChanged = 1; break; //leftShift + O - UP
      case 56: buttonChanged = 7;  modChanged = 1; break; //leftShift + / - DOWN
      
      case 10: buttonChanged = 47; modChanged = 2; break; //leftShift + G - {
      case 13: buttonChanged = 48; modChanged = 2; break; //leftShift + J - }
      case 7:  buttonChanged = 38; modChanged = 2; break; //leftShift + D - (
      case 11: buttonChanged = 39; modChanged = 2; break; //leftShift + H - )
      case 5:  buttonChanged = 47; modChanged = 0; break; //leftShift + B - [
      case 14: buttonChanged = 48; modChanged = 0; break; //leftShift + K - ]
      
      case 16: buttonChanged = 46; modChanged = 2; break; //leftShift + V - plus
      
      case 25: buttonChanged = 45; modChanged = 0; break; //leftShift + M - minus
      case 27: buttonChanged = 45; modChanged = 2; break; //leftShift + P - _
      case 6:  buttonChanged = 46; modChanged = 0; break; //leftShift + T - =
      
      case 30: buttonChanged = 30; modChanged = 0; break; //1
      case 31: buttonChanged = 31; modChanged = 0; break; //2
      case 32: buttonChanged = 32; modChanged = 0; break; //3
      case 33: buttonChanged = 33; modChanged = 0; break; //4
      case 34: buttonChanged = 34; modChanged = 0; break; //5
      case 35: buttonChanged = 35; modChanged = 0; break; //6
      case 36: buttonChanged = 36; modChanged = 0; break; //7
      case 37: buttonChanged = 37; modChanged = 0; break; //8
      case 38: buttonChanged = 38; modChanged = 0; break; //9
      case 39: buttonChanged = 39; modChanged = 0; break; //0
      
      case 42: buttonChanged = 42; modChanged = 0; break;
    
      case 44: buttonChanged = 4; modChanged = 1; break; //leftShift + Space - ctrl + t  
      
      case 21: buttonChanged = 21; modChanged = 1; break; //leftShift + r - control + r  
      case 22: buttonChanged = 22; modChanged = 1; break; //leftShift + r - control + s 
      case 23: buttonChanged = 23; modChanged = 1; break; //leftShift + r - control + t 
      
      case 51: buttonChanged = 18; modChanged = 1; break; //leftShift + r - control + t 
      
      case 19: buttonChanged = 19; modChanged = 1; break; //leftShift + p - control + p 
      case 26: buttonChanged = 26; modChanged = 1; break; //leftShift + w - control + w 
      
      //case 52: buttonChanged = 11; modChanged = 1; break; //?
      
      case 47: buttonChanged = 51; modChanged = 0; break; //
      
      case 49: buttonChanged = 5; modChanged = 1; break; //?
      
      case 9: buttonChanged = 9; modChanged = 1; break; //?
    }
  }
  if(mod == 4) {
    switch(key) {
      case 43: buttonChanged = 75; modChanged = 0; break; //Shuffle - ,
    }
  }
  if(mod == 6) {
    switch(key) {
      case 17: buttonChanged = 17; modChanged = 1; break; //shift + alt n - ctrl + n
      case 12: buttonChanged = 13; modChanged = 1; break; //shift + alt i - ctrl + j
      case 24: buttonChanged = 24; modChanged = 1; break; //shift + alt u - ctrl + u
      case 8:  buttonChanged = 8;  modChanged = 1; break; //shift + alt e - ctrl + e
      case 15: buttonChanged = 15; modChanged = 1; break; //shift + alt j - ctrl + l
      case 28: buttonChanged = 28; modChanged = 1; break; //shift + alt y - ctrl + y
      
      case 43: buttonChanged = 29; modChanged = 1; break; //Shuffle - ,
    }
  }
  if(mod == 8) {
    switch(key) {
      case 7: buttonChanged = 78; modChanged = 0; break; //Shuffle - .
    }
  }
  if(mod == 3) {    
      switch(key) {
      case 17: buttonChanged = 80; modChanged = 1; break;
      case 12: buttonChanged = 79; modChanged = 1; break;
    }
  }
  if(mod == 10) {    
      switch(key) {
      case 7: buttonChanged = 27; modChanged = 1; break;
    }
  }
  if(buttonChanged || modChanged) {
    buttonPressed = buttonChanged;
    modPressed = modChanged;
  } else {
    buttonPressed = key;
    modPressed = mod;
  }
}

void interrupt(void) {
  if(waitCycleCounter < waitCyclesToStick) {
    waitCycleCounter++;
  } else if(buttonPressed != 0) {    
    buttonToRepeat = buttonPressed;
    modToRepeat = modPressed;
  }
}

USB     Usb;
//USBHub     Hub(&Usb);
HIDBoot<HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

uint32_t next_time;

KbdRptParser Prs;

void setup()
{
  Serial.begin( 115200 );
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
  Serial.println("Start");

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay( 200 );

  next_time = millis() + 5000;

  HidKeyboard.SetReportParser(0, (HIDReportParser*)&Prs);

  cli();

  // Force re-enumeration so the host will detect us
  usbDeviceDisconnect();
  delayMs(250);
  usbDeviceConnect();

  // Set interrupts again
  sei();

  Timer1.initialize(waitTimeToStick);
  Timer1.attachInterrupt(interrupt);
}

void loop()
{
  Usb.Task();

  UsbKeyboard.update();

  if(buttonToRepeat){
    UsbKeyboard.sendKeyStroke(buttonToRepeat, modToRepeat);
    buttonToRepeat = 0;
    modToRepeat = 0;
  }
}

// helper method for V-USB library
void delayMs(unsigned int ms) {
  for( int i=0; i<ms; i++ ) {
    delayMicroseconds(1000);
  }
}

