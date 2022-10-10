#include "Keyboard.h"
int output = 0;
int readReady = 0;
char axis = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  while (digitalRead(2) == 1) {
    if (digitalRead(3) == 1) {
      if (readReady == 1) {
        Serial.println("1");
        readReady = 0;
        switch (axis) {
          case 1:
            Keyboard.write(KEY_RIGHT_ARROW);
            break;

          case 2:
            Keyboard.write(KEY_UP_ARROW);
            break;

          case 3:
            Keyboard.write(KEY_PAGE_UP);
            break;
        }
      }
    }
  }
  readReady = 1;
  
  while (digitalRead(3) == 1) {
    if (digitalRead(2) == 1) {
      if (readReady == 1) {
        Serial.println("2");
        readReady = 0;
        switch (axis) {
          case 1:
            Keyboard.write(KEY_LEFT_ARROW);
            break;

          case 2:
            Keyboard.write(KEY_DOWN_ARROW);
            break;

          case 3:
            Keyboard.write(KEY_PAGE_DOWN);
            break;
        }
      }
    }
  }
  readReady = 1;
}
