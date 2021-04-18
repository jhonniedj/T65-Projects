void setup() {
  // put your setup code here, to run once:
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  digitalWrite(D6, LOW);
  digitalWrite(D7, HIGH);
  ring(true);
}


// On and Off Times (as int, max=32secs)
const unsigned int onTime = 1000;
const unsigned int offTime = 4000;

// Tracks the last time event fired
unsigned long previousLoopMillis = 0;

// Interval is how long we wait
int loopInterval = onTime;

// Used to track if LED should be on or off
boolean ringState = true;

void loop() {
  unsigned long currentLoopMillis = millis();

  // Compare to previous capture to see if enough time has passed
  if ((unsigned long)(currentLoopMillis - previousLoopMillis) >= loopInterval) {
    // Change wait interval, based on current LED state
    if (ringState) {
      // LED is currently on, set time to stay off
      loopInterval = offTime;
    } else {
      // LED is currently off, set time to stay on
      loopInterval = onTime;
    }
    // Toggle the LED's state, Fancy, eh!?
    ringState = !(ringState);

    // Save the current time to compare "later"
    previousLoopMillis = currentLoopMillis;
  }

  if (ringState) {
    ringLoop();
  }

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
