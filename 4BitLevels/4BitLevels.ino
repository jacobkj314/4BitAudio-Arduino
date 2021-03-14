const int pin[] = {2, 4, 6, 8};
const int bits = sizeof(pin);
const int levels = (int)pow(2, bits);

#include "pitches.h";
const int frequency = NOTE_CS5;//limit to a single note
const int wavelength = (int)(1000000/frequency);

//float twoPi = 3.14159 * 2;
#define dur .1

void setup() { 
  Serial.begin(9600);
  for(int i = 0; i < bits; i++)
    pinMode(pin[i], OUTPUT);
}

void loop() {
  int level[bits];
  int bin = getBin();
  
  //add values to array
  int pos = levels;
  for(int i = bits-1; i >= 0; i--){
    pos /= 2;
    if(bin >= pos)
      level[i] = HIGH;
    else
      level[i] = LOW;
    bin %= pos;
  }

  //output the sound to the speaker
  for(int reps = 0; reps < (int)(dur * frequency); reps++) {//produce sound for one second
    for(int i = 0; i < bits; i++)
      digitalWrite(pin[i], level[i]);
    delayMicroseconds(wavelength/2);
    for(int i = 0; i < bits; i++)
      digitalWrite(pin[i], LOW);
    delayMicroseconds(wavelength/2);
  }
  //delay(1000);
}

int getBin() {
  static int bin;
  bin++;
  bin %= levels;
  return bin;
}
