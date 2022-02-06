#include <Arduino.h>

#define TriggerPin 8
#define EchoPin    9

float distance = 0.0;

uint32_t MeasureDistance()
{
  uint32_t RetVal = 0;
  digitalWrite(TriggerPin,1);
  delayMicroseconds(10);
  digitalWrite(TriggerPin,0);
  RetVal = pulseIn(EchoPin,HIGH);
  return RetVal;
}

void setup() {
  pinMode(TriggerPin,OUTPUT);
  pinMode(EchoPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  distance = MeasureDistance() * 170e-4;
  Serial.print(distance);
  Serial.println("cm");
  delay(1000);
}