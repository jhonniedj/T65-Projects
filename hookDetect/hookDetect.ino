/*
  Input Pull-up Serial

  This example demonstrates the use of pinMode(INPUT_PULLUP). It reads a digital
  input on pin 2 and prints the results to the Serial Monitor.

  The circuit:
  - momentary switch attached from pin 2 to ground
  - built-in LED on pin 13

  Unlike pinMode(INPUT), there is no pull-down resistor necessary. An internal
  20K-ohm resistor is pulled to 5V. This configuration causes the input to read
  HIGH when the switch is open, and LOW when it is closed.

  created 14 Mar 2012
  by Scott Fitzgerald

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/InputPullupSerial
*/

void setup() {
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  digitalWrite(D6, LOW); //pin 4 = Ringing Mode. Sets bias conditions during ringing. Must be set to logic (H) during ringing. Logic (L) for other modes.
  digitalWrite(D7, HIGH);  //pin 3 = Forward/Reverse. A logic (L) will reverse the Tip and Ring voltage polarities. F/R is toggled to produce the ringing output.
  //start serial connection
  Serial.begin(9600);
  //configure pin 2 as an input and enable the internal pull-up resistor
  pinMode(D0, INPUT); 
}

void loop() {
  //read the pushbutton value into a variable
  int sensorVal = digitalRead(D0);
  //print out the value of the pushbutton
  Serial.println(sensorVal);
  delay(200);
}
