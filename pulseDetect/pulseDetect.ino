/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

const int msSampleTime = 5;                 //amount of ms to repeat loop
const int minLowMeasure = 200;              //maximal measure (of 1024) to be detected as 'low' signal
const int minLowPulseWidth = 20;            //minimal width of 'low' signal to be detected as pulse
const int minHighPulseTimeoutWidth = 200;   //ms to timeout and start new pulse count

int pulseCounts = 0;
int lowLastMs = millis();
int highLastMs = millis();
// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // print out the value you read:
  if (sensorValue < minLowMeasure) {
    if ((millis() - lowLastMs) > minLowPulseWidth) {
      pulseCounts = pulseCounts + 1;
      lowLastMs = millis();
    }
    highLastMs  = millis();
  } else {
    lowLastMs = millis();
    if ((millis() - highLastMs ) > minHighPulseTimeoutWidth) {
      highLastMs  = millis();
      if (pulseCounts != 0) {
        Serial.print("total pulses: ");
        Serial.println(pulseCounts);
      }
      pulseCounts = 0;
    }
  }
  delay(msSampleTime);        // delay in between reads for stability
}
