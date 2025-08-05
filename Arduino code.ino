#include <Keypad.h>

const String password = "1234";
String inputPassword = "";

const int greenLED = 7;
const int redLED = 6;
const int buzzer = 5;

const byte ROWS = 4; 
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.print("Pressed: ");
    Serial.println(key);

    if (key == '#') {
      if (inputPassword == password) {
        unlockSuccess();
      } else {
        accessDenied();
      }
      inputPassword = "";
    } else if (key == '*') {
      inputPassword = "";
      Serial.println("Input cleared");
    } else {
      inputPassword += key;
    }
  }
}

void unlockSuccess() {
  Serial.println("Access Granted!");
  digitalWrite(greenLED, HIGH);
  tone(buzzer, 1000, 200);
  delay(1000);
  digitalWrite(greenLED, LOW);
}

void accessDenied() {
  Serial.println("Access Denied!");
  digitalWrite(redLED, HIGH);
  tone(buzzer, 500, 1000);
  delay(1000);
  digitalWrite(redLED, LOW);
}
