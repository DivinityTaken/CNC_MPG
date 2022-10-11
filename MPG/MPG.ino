#include "Keyboard.h"
#include "EEPROM.h"

//global variables
int output = 0;
int readReady = 0;
int mode = 0;
int axis = 1;
int xPositive = 215;
int xNegative = 216;
int yPositive = 218;
int yNegative = 217;
int zPositive = 211;
int zNegative = 214;
int sm = 49;
int md = 50;
int lg = 51;
int printed = 0;
int rolled = 0;


void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);




  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  if (Serial.available() > 0) {
    String incoming = Serial.readString();
    incoming.toLowerCase();     //convert any upper case to lower case
    incoming.replace(" ", "");  //remove white spaces
    incoming.trim();
    if (incoming.equals("setup")) {
      mode = 1;
    }
  }

  while (mode == 1) {
    if (printed == 0) {
      Serial.println("Setup Mode:");
      Serial.print("X+ = ");
      Serial.println(EEPROM.read(10));
      Serial.print("X- = ");
      Serial.println(EEPROM.read(20));
      Serial.print("Y+ = ");
      Serial.println(EEPROM.read(30));
      Serial.print("Y- = ");
      Serial.println(EEPROM.read(40));
      Serial.print("Z+ = ");
      Serial.println(EEPROM.read(50));
      Serial.print("Z- = ");
      Serial.println(EEPROM.read(60));
      Serial.print("SM = ");
      Serial.println(EEPROM.read(70));
      Serial.print("MD = ");
      Serial.println(EEPROM.read(80));
      Serial.print("LG = ");
      Serial.println(EEPROM.read(90));

      Serial.println("Enter new values in the format of \"X+=###\" where the number is the ascii code for the character you wish to use");
      Serial.println("https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/");
      Serial.println("Type \"exit\" to leave setup");
      printed = 1;
    }
    if (Serial.available() > 0) {

      String incomingString = Serial.readString();  //read the raw incoming data and store it in a string
      incomingString.toLowerCase();                 //convert any upper case to lower case
      incomingString.replace(" ", "");              //remove white spaces
      incomingString.trim();
      int delim = incomingString.indexOf("=");                 //find the index of the equals sign
      String ParamToSet = incomingString.substring(0, delim);  //seperate out the parameter you are setting
      String Value = incomingString.substring(delim + 1);      //seperate out the value for that parameter
      int NewValue = Value.toInt();                            //convert the value from string to int

      if (incomingString.equals("exit")) {
        Serial.println("Leaving setup mode...");
        mode = 0;
      } else if (ParamToSet.equals("x+")) {
        EEPROM.write(10, NewValue);
        printed = 0;
      } else if (ParamToSet.equals("x-")) {
        EEPROM.write(20, NewValue);
        printed = 0;
      } else if (ParamToSet.equals("y+")) {
        EEPROM.write(30, NewValue);
        printed = 0;
      } else if (ParamToSet.equals("y-")) {
        EEPROM.write(40, NewValue);
        printed = 0;
      } else if (ParamToSet.equals("z+")) {
        EEPROM.write(50, NewValue);
        printed = 0;
      } else if (ParamToSet.equals("z-")) {
        EEPROM.write(60, NewValue);
        printed = 0;
      } else if (ParamToSet.equals("sm")) {
        EEPROM.write(70, NewValue);
        printed = 0;
      } else if (ParamToSet.equals("md")) {
        EEPROM.write(80, NewValue);
        printed = 0;
      } else if (ParamToSet.equals("lg")) {
        EEPROM.write(90, NewValue);
        printed = 0;
      } else {
        Serial.println("Parameter not recognized");
        printed = 0;
      }
    }
  }



  if (mode == 0) {
    xPositive = EEPROM.read(10);
    xNegative = EEPROM.read(20);
    yPositive = EEPROM.read(30);
    yNegative = EEPROM.read(40);
    zPositive = EEPROM.read(50);
    zNegative = EEPROM.read(60);
    sm = EEPROM.read(70);
    md = EEPROM.read(80);
    lg = EEPROM.read(90);

    if (digitalRead(6) == 0) {
      axis = 1;
      digitalWrite(A0, 1);
      digitalWrite(A1, 0);
      digitalWrite(A2, 0);
    }
    if (digitalRead(7) == 0) {
      axis = 2;
      digitalWrite(A0, 0);
      digitalWrite(A1, 1);
      digitalWrite(A2, 0);
    }
    if (digitalRead(8) == 0) {
      axis = 3;
      digitalWrite(A0, 0);
      digitalWrite(A1, 0);
      digitalWrite(A2, 1);
    }

    if (digitalRead(14) == 0) {
      Keyboard.write(sm);
    }
    if (digitalRead(15) == 0) {
      Keyboard.write(md);
    }
    if (digitalRead(16) == 0) {
      Keyboard.write(lg);
    }

    while (digitalRead(2) == 1) {
      if (digitalRead(3) == 1) {
        if (readReady == 1) {
          readReady = 0;
          switch (axis) {
            case 1:
              Keyboard.write(xPositive);
              break;

            case 2:
              Keyboard.write(yPositive);
              break;

            case 3:
              Keyboard.write(zPositive);
              break;
          }
        }
      }
    }
    readReady = 1;

    while (digitalRead(3) == 1) {
      if (digitalRead(2) == 1) {
        if (readReady == 1) {
          readReady = 0;
          switch (axis) {
            case 1:
              Keyboard.write(xNegative);
              break;

            case 2:
              Keyboard.write(yNegative);
              break;

            case 3:
              Keyboard.write(zNegative);
              break;
          }
        }
      }
    }
    readReady = 1;
  }

  if (rolled == 0 && digitalRead(6) == 0 && digitalRead(7) == 0 && digitalRead(8) == 0) {
    Keyboard.press(131);
    Keyboard.write(114);
    Keyboard.releaseAll();
    delay(250);
    Keyboard.print("https://www.youtube.com/watch?v=DLzxrzFCyOs");
    Keyboard.write(176);
    rolled = 1;
  }else{
    rolled = 0;
  }
}