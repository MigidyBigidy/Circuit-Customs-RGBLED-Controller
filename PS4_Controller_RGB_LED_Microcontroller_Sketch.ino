//06.16.2020

#include <EEPROM.h>

// Define Pins
#define BLUE 2
#define GREEN 0
#define RED 1
#define ButtonPin 4
// define variables
int ButtonMode = 1;
int delayTime = 10;
int delayTimeIndv = 5;
int BlinkCounter = 0;
float BlinkLength = 1150;
float onF1 = 0;
float onF2 = 0;
int on = 0;
int off = 0;
int ColorCycleMode = 0;
bool ButtonState = false;
bool ButtonFirstPress = false;
bool SettingMenu = false;
bool ButtonStateM = false;
bool ButtonReleaseFrameM = false;
bool SettingMenuEnterPress = false;
bool TurnOffPress = false;
bool TurnOff = false;
long ButtonTimer = 0;
long LongPressTime = 3000;
long TurnOffTime = 6000;


void setup()
{
    //Define Pins
    pinMode(ButtonPin, INPUT_PULLUP);
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);

    //Remember ButtonMode from EEPROM
    ButtonMode = EEPROM.read(0);

    //Turn on LED from Bootup

    if (ButtonMode == 1){
        //Red
      digitalWrite(RED, HIGH);
    }
    
    if (ButtonMode == 2)
      {
        //Blue
      digitalWrite(BLUE, HIGH);
      }

    if (ButtonMode == 3)
      {
        //Green
       digitalWrite(GREEN, HIGH);
      }

    if (ButtonMode == 4)
      {
        //Yellow
       digitalWrite(RED, HIGH);
       digitalWrite(GREEN, HIGH);
      }

    if (ButtonMode == 6)
      {
        //White
       digitalWrite(GREEN, HIGH);
       digitalWrite(RED, HIGH);
       digitalWrite(BLUE, HIGH);
      }
      
    if (ButtonMode == 5)
      {
        //Purple
       digitalWrite(RED, HIGH);
       digitalWrite(BLUE, HIGH);
      }
}



// main loop
void loop()
{
// Checking if button is pressed
  if (digitalRead(ButtonPin) == LOW && SettingMenu == false && TurnOffPress == false)
  {
    if (ButtonFirstPress == false)
    {
      ButtonFirstPress = true;
      ButtonTimer = millis();
    }
  
    if (millis() - ButtonTimer > LongPressTime)
    {
      // Turns on the Settings Menu
      SettingMenu = true;
      TurnOff = false;
      SettingMenuEnterPress = true;
      ColorCycleMode = 1;
    }

  } else {
   
    // Resets the long press count
    if (digitalRead(ButtonPin) == HIGH && ButtonFirstPress == true){
      ButtonFirstPress = false;
    }

   if (millis() - ButtonTimer > TurnOffTime && SettingMenu == true && ButtonFirstPress == true)
    {
      // Turns off the LED
      SettingMenu = false;
      TurnOffPress = true;
      TurnOff = true;
      digitalWrite (RED, LOW);
      digitalWrite (BLUE, LOW);
      digitalWrite (GREEN, LOW);
    }
  }

    if (digitalRead(ButtonPin) == HIGH && TurnOffPress == true){
      TurnOffPress = false;
      ButtonFirstPress = false;
      BlinkCounter = 0;
    }

    if (SettingMenu == false && ButtonMode == 7 && ColorCycleMode <= 6){
    ColorCycleMode += 1;
  }

  if (SettingMenu == false && ColorCycleMode > 6){
    ColorCycleMode = 1;
  }

  if (SettingMenu == true && ButtonMode == 7){
    ColorCycleMode += 1;
  }
  
  if (SettingMenu == true && ColorCycleMode > 3){
    ColorCycleMode = 1;
  }

  if (SettingMenu == false){
      BlinkCounter = 0;
  }
  
  //Settings Menu Interface
  if (SettingMenu == true)
  {
    if (ButtonMode > 7)
    {
      ButtonMode = 1;
    }
    //Ending Menu Interface with Blink Count (5 Blinks)  
    if (BlinkCounter >= 5000){
      BlinkCounter = 0;
      SettingMenu = false;
      EEPROM.write(0, ButtonMode);
    }
  
    if (digitalRead(ButtonPin) == LOW && ButtonState == false && SettingMenuEnterPress == false)
      {
        ButtonState = true;
      }
    
    if (digitalRead(ButtonPin) == HIGH && ButtonState == true && SettingMenuEnterPress == false)
      {
        ButtonState = false;
        ButtonMode += 1;
        BlinkCounter = 0;
        ButtonReleaseFrameM = false;
        digitalWrite (RED, LOW);
        digitalWrite (BLUE, LOW);
        digitalWrite (GREEN, LOW);
      }
    
    if (digitalRead(ButtonPin) == HIGH && SettingMenuEnterPress == true){
          SettingMenuEnterPress = false;
          ButtonState = false;
          ButtonReleaseFrameM = false;
        }
    
    if (ButtonMode == 1)
      {
        //Red Fading In and Out
       for(int i = 0; i < BlinkLength && ButtonReleaseFrameM == false; i += 1) 
       {
        on = BlinkLength - i;
        off = i;
        BlinkCounter += 1;
        digitalWrite(RED, HIGH);
        delayMicroseconds(on);
        digitalWrite(RED, LOW);
        delayMicroseconds(off);
        CheckButtonPressWhileSolid();
       }
       digitalWrite(RED, HIGH);
      }
    
      if (ButtonMode == 2)
      {
        //Blue
       for(int i = 0; i < BlinkLength && ButtonReleaseFrameM == false; i += 1) {
        on = BlinkLength - i;
        off = i;
        BlinkCounter += 1;
        digitalWrite(BLUE, HIGH);
        delayMicroseconds(on);
        digitalWrite(BLUE, LOW);
        delayMicroseconds(off);
        CheckButtonPressWhileSolid();
       }
      digitalWrite(BLUE, HIGH);
      }
    
      if (ButtonMode == 3)
      {
        //Green
       for(int i = 0; i < BlinkLength && ButtonReleaseFrameM == false; i += 1) {
        on = BlinkLength - i;
        off = i;
        BlinkCounter += 1;
        digitalWrite(GREEN, HIGH);
        delayMicroseconds(on);
        digitalWrite(GREEN, LOW);
        delayMicroseconds(off);
        CheckButtonPressWhileSolid();
       }
       digitalWrite(GREEN, HIGH);
      }
  
      if (ButtonMode == 4)
      {
        //Yellow
       for(int i = 0; i < BlinkLength && ButtonReleaseFrameM == false; i += 1) {
        on = BlinkLength - i;
        off = i;
        BlinkCounter += 1;
        digitalWrite(RED, HIGH);
        digitalWrite(GREEN, HIGH);
        delayMicroseconds(on);
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, LOW);
        delayMicroseconds(off);
        CheckButtonPressWhileSolid();
       }
       digitalWrite(RED, HIGH);
       digitalWrite(GREEN, HIGH);
      }
  
      if (ButtonMode == 6)
      {
        //White
       for(int i = 0; i < BlinkLength && ButtonReleaseFrameM == false; i += 1) {
        on = BlinkLength - i;
        off = i;
        BlinkCounter += 1;
        digitalWrite(RED, HIGH);
        digitalWrite(GREEN, HIGH);
        digitalWrite(BLUE, HIGH);
        delayMicroseconds(on);
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, LOW);
        digitalWrite(BLUE, LOW);
        delayMicroseconds(off);
        CheckButtonPressWhileSolid();
       }
       digitalWrite(GREEN, HIGH);
       digitalWrite(RED, HIGH);
       digitalWrite(BLUE, HIGH);
      }
  
      if (ButtonMode == 5)
      {
        //Purple
       for(int i = 0; i < BlinkLength && ButtonReleaseFrameM == false; i += 1) {
        on = BlinkLength - i;
        off = i;
        BlinkCounter += 1;
        digitalWrite(RED, HIGH);
        digitalWrite(BLUE, HIGH);
        delayMicroseconds(on);
        digitalWrite(RED, LOW);
        digitalWrite(BLUE, LOW);
        delayMicroseconds(off);
        CheckButtonPressWhileSolid();
       }
       digitalWrite(RED, HIGH);
       digitalWrite(BLUE, HIGH);
      }
      
    if (ButtonMode == 7 && SettingMenu == true)
     {
      if (ColorCycleMode == 1)
      {
       for(float i = 0; i < BlinkLength && ButtonReleaseFrameM == false && BlinkCounter <= 5000; i += 1) {
        onF1 = ((-i*(i-BlinkLength))/BlinkLength);
        onF2 = BlinkLength - i - onF1;
        off = i;
        BlinkCounter += 1;
        digitalWrite(RED, HIGH);
        digitalWrite(GREEN, HIGH);
        delayMicroseconds(onF1);
        digitalWrite(GREEN, LOW);
        delayMicroseconds(onF2);
        digitalWrite(RED, LOW);
        delayMicroseconds(off);
        if (digitalRead(ButtonPin) == LOW && ButtonStateM == false){
          ButtonState = true;
          ButtonStateM = true;
        }
        if (digitalRead(ButtonPin) == HIGH && ButtonStateM == true){
          ButtonStateM = false;
          ButtonReleaseFrameM = true;
        }
       }
      }
      
      if (ColorCycleMode == 2)
      {
       for(float i = 0; i < BlinkLength && ButtonReleaseFrameM == false && BlinkCounter <= 5000; i += 1) {
        onF1 = ((-i*(i-BlinkLength))/BlinkLength);
        onF2 = BlinkLength - i - onF1;
        off = i;
        BlinkCounter += 1;
        digitalWrite(GREEN, HIGH);
        digitalWrite(BLUE, HIGH);
        delayMicroseconds(onF1);
        digitalWrite(BLUE, LOW);
        delayMicroseconds(onF2);
        digitalWrite(GREEN, LOW);
        delayMicroseconds(off);
        if (digitalRead(ButtonPin) == LOW && ButtonStateM == false){
          ButtonState = true;
          ButtonStateM = true;
        }
        if (digitalRead(ButtonPin) == HIGH && ButtonStateM == true){
          ButtonStateM = false;
          ButtonReleaseFrameM = true;
        }
       }
      }

     if (ColorCycleMode == 3)
     {
      for(float i = 0; i < BlinkLength && ButtonReleaseFrameM == false && BlinkCounter <= 5000; i += 1) {
        onF1 = ((-i*(i-BlinkLength))/BlinkLength);
        onF2 = BlinkLength - i - onF1;
        off = i;
        BlinkCounter += 1;
        digitalWrite(BLUE, HIGH);
        digitalWrite(RED, HIGH);
        delayMicroseconds(onF1);
        digitalWrite(RED, LOW);
        delayMicroseconds(onF2);
        digitalWrite(BLUE, LOW);
        delayMicroseconds(off);
        if (digitalRead(ButtonPin) == LOW && ButtonStateM == false){
          ButtonState = true;
          ButtonStateM = true;
        }
        if (digitalRead(ButtonPin) == HIGH && ButtonStateM == true){
          ButtonStateM = false;
          ButtonReleaseFrameM = true;
        }
       // Serial.println("Blink 3");
       }
      }
    delay(10);
    } 
  }

  if (SettingMenu == false && ButtonMode == 7 && TurnOff == false)
  {
    if (ColorCycleMode == 1){
      RedToYellow();
    }
    if (ColorCycleMode == 2){
      YellowToGreen();
    }
    if (ColorCycleMode == 3){
      GreenToCyan();
    }
    if (ColorCycleMode == 4){
      CyanToBlue();
    }
    if (ColorCycleMode == 5){
      BlueToMagenta();
    }
    if (ColorCycleMode == 6){
      MagentaToRed();
    }
  }
}

  void RedToYellow(){
    
    digitalWrite(RED, HIGH);
    digitalWrite(BLUE, LOW);

    for(float i = 0; i < 1150 && ButtonReleaseFrameM == false; i += 1) {
        on = i;
        off = BlinkLength - i;
        digitalWrite(GREEN, HIGH);
        delayMicroseconds(on);
        digitalWrite(GREEN, LOW);
        delayMicroseconds(off);
        if (digitalRead(ButtonPin) == LOW && SettingMenu == false && TurnOffPress == false)
  
    if (ButtonFirstPress == false && digitalRead(ButtonPin) == LOW && SettingMenu == false && TurnOffPress == false)
    {
      ButtonFirstPress = true;
      ButtonTimer = millis();
    }
   }
 }

  void YellowToGreen(){
    
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, HIGH);

    for(float i = 0; i < 1150 && ButtonReleaseFrameM == false; i += 1) {
        on = i;
        off = BlinkLength - i;
        digitalWrite(RED, HIGH);
        delayMicroseconds(off);
        digitalWrite(RED, LOW);
        delayMicroseconds(on);
        if (ButtonFirstPress == false && digitalRead(ButtonPin) == LOW && SettingMenu == false && TurnOffPress == false)
    {
      ButtonFirstPress = true;
      ButtonTimer = millis();
    }
   }
  }

  void GreenToCyan(){
    
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);

    for(float i = 0; i < 1150 && ButtonReleaseFrameM == false; i += 1) {
        on = i;
        off = BlinkLength - i;
        digitalWrite(BLUE, HIGH);
        delayMicroseconds(on);
        digitalWrite(BLUE, LOW);
        delayMicroseconds(off);
       if (ButtonFirstPress == false && digitalRead(ButtonPin) == LOW && SettingMenu == false && TurnOffPress == false)
    {
      ButtonFirstPress = true;
      ButtonTimer = millis();
    }
   }
  }

  void CyanToBlue(){
    
    digitalWrite(RED, LOW);
    digitalWrite(BLUE, HIGH);

    for(float i = 0; i < 1150 && ButtonReleaseFrameM == false; i += 1) {
        on = i;
        off = BlinkLength - i;
        digitalWrite(GREEN, HIGH);
        delayMicroseconds(off);
        digitalWrite(GREEN, LOW);
        delayMicroseconds(on);
        if (ButtonFirstPress == false && digitalRead(ButtonPin) == LOW && SettingMenu == false && TurnOffPress == false)
    {
      ButtonFirstPress = true;
      ButtonTimer = millis();
    }  
   }
  }

  void BlueToMagenta(){
    
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, HIGH);

    for(float i = 0; i < 1150 && ButtonReleaseFrameM == false; i += 1) {
        on = i;
        off = BlinkLength - i;
        digitalWrite(RED, HIGH);
        delayMicroseconds(on);
        digitalWrite(RED, LOW);
        delayMicroseconds(off);
       if (ButtonFirstPress == false && digitalRead(ButtonPin) == LOW && SettingMenu == false && TurnOffPress == false)
    {
      ButtonFirstPress = true;
      ButtonTimer = millis();
    }
   }
  }

  void MagentaToRed(){
    
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);

    for(float i = 0; i < 1150 && ButtonReleaseFrameM == false; i += 1) {
        on = i;
        off = BlinkLength - i;
        digitalWrite(BLUE, HIGH);
        delayMicroseconds(off);
        digitalWrite(BLUE, LOW);
        delayMicroseconds(on);
        if (ButtonFirstPress == false && digitalRead(ButtonPin) == LOW && SettingMenu == false && TurnOffPress == false)
    {
      ButtonFirstPress = true;
      ButtonTimer = millis();
    }
   }
  }

  void CheckButtonPressWhileSolid(){
    if (digitalRead(ButtonPin) == LOW && ButtonStateM == false){
          ButtonState = true;
          ButtonStateM = true;
        }
        if (digitalRead(ButtonPin) == HIGH && ButtonStateM == true){
          ButtonStateM = false;
          ButtonReleaseFrameM = true;
  }
 } 

