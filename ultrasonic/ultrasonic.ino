#include<Wire.h>
int ledState = 0;
int dist[4] = {0, 0, 0, 0};
int reg = 0;

unsigned int echoPin[4] = {2, 4, 6, 8};   // connect to Echo/RX
unsigned int trigPin[4] = {3, 5, 7, 9};   // connect to Trig/TX

void setup()
{
  Serial.begin(9600);
  Wire.begin(8); // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveData);
  for (int i = 0; i < 4; i++) {
    pinMode(echoPin[i], INPUT);
    pinMode(trigPin[i], OUTPUT);
  }
}

int caculateDistance(int i)
{
  unsigned long time_echo_us = 0;
  unsigned long dist_mm = 0;
  digitalWrite(trigPin[i], LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin[i], HIGH);  // start pluse
  delayMicroseconds(12);        // set pluse width
  digitalWrite(trigPin[i], LOW);   // end pluse

  time_echo_us = pulseIn(echoPin[i], HIGH);  // caculate pluse width
  if ((time_echo_us < 60000) && (time_echo_us > 1)) // validate pluse width range
  {
    dist_mm = time_echo_us * 5 / 29; // caculate distance using pluse duration
  }
  return dist_mm;
}

void loop()
{
  if (ledState == 0) {
    digitalWrite(13, HIGH); // set the LED on
    ledState = 1;
  }
  else {
    digitalWrite(13, LOW); // set the LED off
    ledState = 0;
  }
  noInterrupts();
  for(int i = 0; i < 4; i++) {
    dist[i] = caculateDistance(i);
  }
  interrupts();
  delay(1000);
}

void requestEvent()
{
  byte tmp[2] = {0};
  tmp[0] = highByte(dist[reg]);
  tmp[1] = lowByte(dist[reg]); // BigEndian
  Wire.write(tmp, 2);
}

void receiveData(int byteCount)
{
  while (Wire.available()) {
    reg  = Wire.read();
  }
}

