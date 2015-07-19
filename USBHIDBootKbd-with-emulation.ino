#include <hidboot.h>
#include <usbhub.h>
// Satisfy IDE, which only needs to see the include statment in the ino.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif

#include <TimerOne.h>
#include <UsbKeyboard.h>

volatile uint8_t buttonPressed;
volatile uint8_t modPressed;
volatile uint8_t buttonToRepeat;
volatile uint8_t modToRepeat;
volatile uint8_t waitCycleCounter;

volatile bool isRAlt;
volatile bool isSpaceShift;
volatile bool isSpaceAlt;

volatile bool rewriteMod;

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

  if (key == 52 && mod == 0) {
    isRAlt = true;
    Serial.println("RALT PRESSED");
  } else if(key == 44 && mod == 0  && isRAlt) {
    isSpaceAlt = true;
    Serial.println("SPACEALT PRESSED");
  } else if(key == 44 && mod == 2) {
    isSpaceShift = true;
    Serial.println("SPACESHIFT PRESSED");
  }
  else {
    if(isRAlt && !rewriteMod)
      modPressed = 64;
      
    UsbKeyboard.sendKeyStroke(buttonPressed, modPressed);
  }

  Timer1.restart();
}

void KbdRptParser::OnKeyUp(uint8_t mod, uint8_t key)
{
  Serial.println("UP");
  PrintKey(key, mod);

  if (key == 52 && mod == 0) {
    isRAlt = false;
    Serial.println("RAlt RELEASED");
  } else if (key == 44) {
    isSpaceAlt = false;
    Serial.println("SPACEALT RELEASED");
    isSpaceShift = false;
    Serial.println("SPACESHIFT RELEASED");
  }
  
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

  rewriteMod = false;

  if (mod == 0) {
    if(isSpaceAlt) {
      switch(key) {
        case 16: buttonChanged = 20; modChanged = 0;  rewriteMod = true; break; //RALt + m - BACKSPACE
      }
    } else if(isRAlt) {
      switch(key) {
        case 16: buttonChanged = 42; modChanged = 0;  rewriteMod = true; break; //RALt + m - BACKSPACE
        case 11: buttonChanged = 43; modChanged = 42; rewriteMod = true; break; //RALt + h - SHIFT-TAB

        case 10: buttonChanged = 47; modChanged = 2; rewriteMod = true; break;  //RALT + g - {
        case 7:  buttonChanged = 38; modChanged = 2; rewriteMod = true; break;  //RALT + d - (
        case 5:  buttonChanged = 47; modChanged = 0; rewriteMod = true; break;  //RALT + b - [

        case 20: buttonChanged = 45; modChanged = 2; rewriteMod = true; break;  //RALT + q - _
        case 4:  buttonChanged = 52; modChanged = 0; rewriteMod = true; break;  //RALT + q - '
        case 29: buttonChanged = 51; modChanged = 2; rewriteMod = true; break;  //RALT + a - :

        case 25: buttonChanged = 45; modChanged = 0; rewriteMod = true; break;  //RALT + v - minus
        case 6:  buttonChanged = 49; modChanged = 0; rewriteMod = true; break;  //RALT + c - divide
        case 27: buttonChanged = 37; modChanged = 2; rewriteMod = true; break;  //RALT + x - multiply
        
        case 19: buttonChanged = 49; modChanged = 2; rewriteMod = true; break;  //RALT + p - |
        case 23: buttonChanged = 36; modChanged = 2; rewriteMod = true; break;  //RALT + t - &

        case 9:  buttonChanged = 30; modChanged = 2; rewriteMod = true; break;  //RALT + f - !
        case 22: buttonChanged = 56; modChanged = 2; rewriteMod = true; break;  //RALT + s - ?

        case 26: buttonChanged = 32; modChanged = 2; rewriteMod = true; break;  //RALT + w - #
        case 21: buttonChanged = 31; modChanged = 2; rewriteMod = true; break;  //RALT + r - @
      }
    } 
    else
      switch (key) {
        case 51: buttonChanged = 20; modChanged = 1; break; //SUPERKEY - ctrl + q

        case 40: buttonChanged = 35; modChanged = 2; break; //ENTER - ^
        case 42: buttonChanged = 53; modChanged = 0; break; //BACKSPACE - `

        case 43: buttonChanged = 41; modChanged = 0; break; //TAB - ESC
        
        default: buttonChanged = key; modChanged = mod; break;
      }
  }
  if (mod == 2) {
    switch (key) {
      case 23: buttonChanged = 40; modChanged = 0; break; //LSHIFT + t - ENTER
      case 25: buttonChanged = 76; modChanged = 0; break; //LSHIFT + v - DELETE
      case 7:  buttonChanged = 43; modChanged = 0; break; //LSHIFT + d - TAB

      case 9:  buttonChanged = 6;  modChanged = 1; break; //LSHIFT + f - control + c
      case 19: buttonChanged = 25; modChanged = 1; break; //LSHIFT + p - control + v

      case 26: buttonChanged = 29; modChanged = 1; break; //LSHIFT + w - control + w
      case 21: buttonChanged = 28; modChanged = 1; break; //LSHIFT + r - control + r

      case 51: buttonChanged = 46; modChanged = 0; break; //LSHIFT + SimpleMotion - =
      case 18: buttonChanged = 52; modChanged = 2; break; //LSHIFT + o - "
      case 56: buttonChanged = 51; modChanged = 0; break; //LSHIFT + / - :
      
      case 13: buttonChanged = 48; modChanged = 2; break; //LSHIFT + J - }
      case 11: buttonChanged = 39; modChanged = 2; break; //LSHIFT + H - )
      case 14: buttonChanged = 48; modChanged = 0; break; //LSHIFT + K - ]
      
      case 16: buttonChanged = 46; modChanged = 2; break; //LSHIFT + m - plus
      
      case 24: buttonChanged = 82; modChanged = 0; break; //LSHIFT + u - up arrow
      case 17: buttonChanged = 80; modChanged = 0; break; //LSHIFT + n - left arrow
      case 12: buttonChanged = 79; modChanged = 0; break; //LSHIFT + i - right arrow
      case 8:  buttonChanged = 81; modChanged = 0; break; //LSHIFT + e - down arrow
      case 15: buttonChanged = 74; modChanged = 0; break; //LSHIFT + l - home
      case 28: buttonChanged = 77; modChanged = 0; break; //LSHIFT + y - end

      case 54: buttonChanged = 32; modChanged = 2; break; //LSHIFT + , - $
      case 55: buttonChanged = 34; modChanged = 2; break; //LSHIFT + , - %

      case 42: buttonChanged = 53; modChanged = 2; break; //LSHIFT + BACKSPACE - ~
      
      
      case 22: buttonChanged = 22; modChanged = 1; break; //LSHIFT + s - control + s
      case 27: buttonChanged = 27; modChanged = 1; break; //LSHIFT + x - control + x
      case 6:  buttonChanged = 6;  modChanged = 1; break; //LSHIFT + c - control + c          
      
      default: buttonChanged = key; modChanged = mod; break;
    }
  }
  if (mod == 4) {
    switch (key) {
      case 43: buttonChanged = 54; modChanged = 2; break; //Shuffle - <

      default: buttonChanged = key; modChanged = mod; break;
    }
  }
  if (mod == 8) {
    switch (key) {
      case 7: buttonChanged = 55; modChanged = 2; break; //Shuffle - >

      default: buttonChanged = key; modChanged = mod; break;
    }
  }
  
  if (buttonChanged || modChanged) {
    buttonPressed = buttonChanged;
    modPressed = modChanged;
  } else {
    buttonPressed = key;
    modPressed = mod;
  }
}

void interrupt(void) {
  if (waitCycleCounter < waitCyclesToStick) {
    waitCycleCounter++;
  } else if (buttonPressed != 0) {
    if((buttonPressed == 52 && modPressed == 0) ||
       (buttonPressed == 44 && modPressed == 0 && isRAlt) ||
       (buttonPressed == 44 && modPressed == 2))
      return;
    else {
      buttonToRepeat = buttonPressed;
      modToRepeat = modPressed;
    }
  }
}

USB     Usb;
HIDBoot<HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

uint32_t next_time;

KbdRptParser Prs;

void setup()
{
  Serial.begin( 115200 ); 
  while (!Serial);
  Serial.println("Start");

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay( 200 );

  next_time = millis() + 5000;

  HidKeyboard.SetReportParser(0, (HIDReportParser*)&Prs);

  cli();

  usbDeviceDisconnect();
  delayMs(250);
  usbDeviceConnect();

  sei();

  Timer1.initialize(waitTimeToStick);
  Timer1.attachInterrupt(interrupt);
}

void loop()
{
  Usb.Task();

  UsbKeyboard.update();

  if (buttonToRepeat) {
    UsbKeyboard.sendKeyStroke(buttonToRepeat, modToRepeat);
    buttonToRepeat = 0;
    modToRepeat = 0;
  }
}

void delayMs(unsigned int ms) {
  for ( int i = 0; i < ms; i++ ) {
    delayMicroseconds(1000);
  }
}

