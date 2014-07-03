/**
 * Playground project for getting started with my Arduino Uno
 *
 * ConcurrentHashMap <ConcurrentHashMap@arcor.de>
 *
 * Derived from the example code for LiquidCrystal Library - Serial Input
 * (http://arduino.cc/en/Tutorial/LiquidCrystalSerial),
 * combined with the button sample code originally by Mark Bramwell, July 2010
 * 
 * This source code is in the public domain.
 */

#include <LiquidCrystal.h>
#define RIGHT  0
#define UP     1
#define DOWN   2
#define LEFT   3
#define SELECT 4
#define NONE   5

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int buttonPressed  = 0;

// Read the current pressed button and return it
int whichButtonPressed() {
  buttonPressed = analogRead(0);
  if (buttonPressed > 1000) return NONE;
  if (buttonPressed < 50)   return RIGHT;  
  if (buttonPressed < 250)  return UP; 
  if (buttonPressed < 450)  return DOWN; 
  if (buttonPressed < 650)  return LEFT; 
  if (buttonPressed < 850)  return SELECT;  

  return NONE;
}

void setup(){
  // Set up the number of columns and rows of the display and move cursor to first char in first line
  lcd.begin(16, 2);
  lcd.setCursor(0,0);

  // Listen to serial port on 9600 baud
  Serial.begin(9600);
}

void loop() {
  // Print out elapsed time since start
  lcd.setCursor(12,1);
  lcd.print(millis()/1000);
 
  // Set cursor to first char in second line
  lcd.setCursor(0,1);
  buttonPressed = whichButtonPressed();
  
  // Switch between available buttons and display which one is currently pressed
  switch(buttonPressed) {
    case RIGHT: {
      lcd.print("RIGHT ");
      break;
    }
    case LEFT: {
      lcd.print("LEFT   ");
      break;
    }
    case UP: {
      lcd.print("UP    ");
      break;
    }
    case DOWN: {
      lcd.print("DOWN  ");
      break;
    }
    case SELECT: {
      lcd.print("SELECT");
      break;
    }
    case NONE: {
      lcd.print("      ");
      break;
    }
  }

  // When characters arrive over the serial port...
  if (Serial.available()) {
    // Wait a bit for the entire message to arrive
    delay(100);
    lcd.clear();
    // Read all the available characters from serial port
    while (Serial.available() > 0) {
      // Display each character on the display
      lcd.write(Serial.read());
    }
  }
}

