/*
  Example, using the PhoneDTMF library.
  https://github.com/Adrianotiger/phoneDTMF

  This example will measure the DTMF 10 times each second.
  If a valid DTMF was found, it will measure the frequence other 3 times.
  The result will be written on the serial port.
  If 4 measurements give the same results (for at least 80ms), it could be a valid DTMF signal.
*/
//NOTICE!: Use 80Mhz!

#include "PhoneDTMF.h"

// New dtmf
PhoneDTMF dtmf = PhoneDTMF();
uint8_t analogPin = A0;

void setup()
{
  Serial.begin(9600);
  delay(2000); // wait until ADC is ready?
  Serial.println();
  Serial.print("DTMF detect @ gpio ");
  Serial.println(A0);

  dtmf.begin(analogPin);
}

int lastKey = 255;

void loop()
{
  uint8_t   tones;
  char      button;

  // detect tone
  tones = dtmf.detect();

  // if valid tone was found, proof for validity
  button = dtmf.tone2char(tones);
  if (button > 0)
  {
    //Serial.print("Detected tone...");
    // measure 4 times, result of each measurement should be always the same
    // time need for this process: 80ms, so the tone must be present at least 100ms to be valid
    tones |= dtmf.detect() | dtmf.detect() | dtmf.detect();

    if (dtmf.tone2char(tones) > 0)
    {
      button = dtmf.tone2char(tones);

      //Serial.print(" Detected '");
      if (lastKey == 255) {
        Serial.println(button);
        lastKey = button;
        button = -1;
      }
      //Serial.println("' !");
    }
    else
    {
      Serial.print("Dismiss: '");
      Serial.print(button);
      lastKey = button;
      Serial.println("' (invalid)");
    }
    delay(10);
  }
  else {
    lastKey = 255;
  }
  delay(100);
}
