void setup() {
  // put your setup code here, to run once:
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  ring(true);
}

void loop() {
  ringLoop();
}

int bellState = LOW;
unsigned long previousMillis = 0;
const long interval = 20; //20ms = 25 Hz
bool ringActive = false;

void ringLoop() {
  if (ringActive) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      if (bellState == LOW) {
        bellState = HIGH;  // Note that this switches the BELL *off*
      } else {
        bellState = LOW;  // Note that this switches the BELL *on*
      }
      digitalWrite(D7, bellState);
    }
  }
}

void ring(bool enableRing) {
  if (enableRing) {
    ringActive = true;
  }
  else {
    ringActive = false;
  }
}
