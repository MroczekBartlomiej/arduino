#include <Keyboard.h>

byte MIC_STATE = LOW;
byte CAM_STATE = LOW;


void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  digitalWrite(8, MIC_STATE);
  digitalWrite(9, CAM_STATE);
  Keyboard.begin();
  Serial.begin(9600);
  Serial.println('PIN STATE');
  Serial.println(digitalRead(2));
  Serial.println(digitalRead(3));
  Serial.println(digitalRead(4));
  Serial.println(digitalRead(5));
}

void loop() {

  if (digitalRead(2) == HIGH) {
    microfon();

    delay(300);
  }
  if (digitalRead(3) == HIGH) {
    camera();
    delay(300);
  }
  if (digitalRead(4) == HIGH) {
    password();
    delay(300);
  }
}

void microfon() {

  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.print("A");
  MIC_STATE = !MIC_STATE;
  digitalWrite(8, MIC_STATE);
  delay(100);
  Keyboard.releaseAll();
}

void camera() {
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.print("B");
  CAM_STATE = !CAM_STATE;
  digitalWrite(9, CAM_STATE);
  delay(100);
  Keyboard.releaseAll();
}

void password() {
  Keyboard.print("^cmTryvv^cmTryvv");
}

void makeCall() {
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(' ');
  Keyboard.releaseAll();
  delay(100);
  Keyboard.print("https://allegro.zoom.us/j/9922945996?pwd=VzA4WWVGZ2ZFQThGeUVHU2JuajIvdz09");
  delay(1000);
  Keyboard.press(KEY_RETURN);
  digitalWrite(15, LOW);
  delay(100);
  Keyboard.releaseAll();
}