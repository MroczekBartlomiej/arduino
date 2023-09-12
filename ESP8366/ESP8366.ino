#define LED_PIN 5
#define BUTTON_PIN 4
#define LED_PIN_2 0
#define BUTTON_PIN_2 2

// set pin numbers
//const int BUTTON_PIN = 4;     // the number of the pushbutton pin
//const int LED_PIN =  5;       // the number of the LED pin

byte lastButtonState = LOW;
byte ledState = LOW;
byte lastButtonState_2 = LOW;
byte ledState_2 = LOW;

// variable for storing the pushbutton status
unsigned long debounceDuration = 50; // millis
unsigned long lastTimeButtonStateChanged = 0;

unsigned long debounceDuration_2 = 50; // millis
unsigned long lastTimeButtonStateChanged_2 = 0;

void setup() {
  Serial.begin(115200);
  Serial.print("Setup");
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BUTTON_PIN_2, HIGH);

}

void loop() {

  //TO chyba ten warunek.
  if (millis() - lastTimeButtonStateChanged > debounceDuration) {
    byte buttonState = digitalRead(BUTTON_PIN);
    Serial.print("Button state 1 : ");
    Serial.println(buttonState);
    if (buttonState != lastButtonState) {
      Serial.println("Button state 1");
      lastTimeButtonStateChanged = millis();
      lastButtonState = buttonState;
      if (buttonState == LOW) {
        Serial.println("DOWN");
        ledState = (ledState == HIGH) ? LOW: HIGH;
        digitalWrite(LED_PIN, ledState);
      }
    }
  }

    if (millis() - lastTimeButtonStateChanged_2 > debounceDuration_2) {
    byte buttonState_2 = digitalRead(BUTTON_PIN_2);
    Serial.print("Button state 2 : ");
    Serial.println(buttonState_2);
    if (buttonState_2 != lastButtonState_2) {
          
      lastTimeButtonStateChanged_2 = millis();
      lastButtonState_2 = buttonState_2;
      if (buttonState_2 == LOW) {
        Serial.println("DOWN");
        ledState_2 = (ledState_2 == HIGH) ? LOW: HIGH;
        digitalWrite(LED_PIN_2, ledState_2);
      }
    }
    }
  }
