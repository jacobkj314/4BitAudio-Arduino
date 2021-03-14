//IO info
const int pin[] = {2, 4, 6, 8};
#define bits 4
#define levels 16

//Sampling info
const int sampleRate = 1000;
const int sampleLength = 1000000 / sampleRate;

//Pitch info
#include "pitches.h"
const float notes[] = {300};
const int chordSize = sizeof(notes);

//Pi * two
#define twoPi 3.14159 * 2

void setup() {
  //Serial.begin(9600);
  for(int i = 0; i < bits; i++)
    pinMode(pin[i], OUTPUT);
}

void loop() {
  int level[bits];
  int bin = getAmplitude();//binary representation of current amplitude
  //Serial.print(bin);
  //Serial.print("\n");

  //add values to array
  int pos = levels;
  for(int i = bits-1; i >= 0; i--){
    pos /= 2;
    if(bin >= pos)
      level[i] = 1;
    else
      level[i] = 0;
    bin %= pos;
  }
  
  //output the sound to the speaker
  for(int i = 0; i < bits; i++)
    digitalWrite(pin[i], level[i]);
  
  delayMicroseconds(sampleLength);
}

int getAmplitude() {
  static int val;
  val++;

  //calculate current "amplitude"
  float amp = 0;
  for(int i = 0; i < chordSize; i++)
    amp += sin(twoPi * (float)notes[i] * (float)val / (float)sampleRate);
  amp /= chordSize;

  return levels/2 + (int)(amp * levels/2); //convert float interval (-1,1) to int interval (0, 2^bits -1)
}
