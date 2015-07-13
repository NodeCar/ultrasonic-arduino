unsigned int echoPin[4] = {2, 4, 6, 8};   // connect to Echo/RX
unsigned int trigPin[4] = {3, 5, 7, 9};   // connect to Trig/TX

void setup(){ 
  Serial.begin(9600); 
  Serial.setTimeout(10); // Serial read timeout
  for(int i = 0; i < 4; i++) {
    pinMode(echoPin[i], INPUT);  
    pinMode(trigPin[i], OUTPUT); 
  }
}

void loop(){
  while(Serial.available() > 0) {

    int no = Serial.parseInt();

    if(no >= 4) {
      continue;
    }
    
    unsigned long time_echo_us = 0;
    unsigned long dist_mm = 0;
    
    digitalWrite(trigPin[no], LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin[no], HIGH);  // start pluse
    delayMicroseconds(12);        // set pluse width
    digitalWrite(trigPin[no], LOW);   // end pluse
    
    time_echo_us = pulseIn(echoPin[no], HIGH);  // caculate pluse width
    if((time_echo_us < 60000) && (time_echo_us > 1)) // validate pluse width range
    {
      dist_mm = time_echo_us*5/29;  // caculate distance using pluse duration
      
      Serial.print(dist_mm, DEC); 
      Serial.println("");
    }
  }
}
