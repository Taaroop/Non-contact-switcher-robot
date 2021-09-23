// Coded by Taaroop

#include <Servo.h>
Servo servo;

#define echoPin 6
#define trigPin 7

long duration; 
long distance;

void setup() {
  Serial.begin(9600);
  pinMode(echoPin,INPUT); // echo pin will receive the pulse (INPUT)
  pinMode(trigPin,OUTPUT); // trig pin will trigger/send the pulse (OUTPUT) 
  
  servo.attach(8);
  servo.write(0);
  delay(2000);
}

void loop() {
  
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH); // sends the high pulse (high pulse sandwiched between low pulses to ensure a clear high pulse)
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin,HIGH); // measures the time taken for the pulse to reach the object and come back 
  duration = duration/2; // actual duration is half, as the pulse covered the distance two times 
  distance = 0.033*duration; // see calculations at the end of the code
  Serial.println(distance); // in cm
  delay(50);

  if(distance < 20) {
    servo.write(90);
    delay(1000); //pushes the switch/bell
    servo.write(0);
    delay(3000); //delay is increased to ensure that the person actually wants to redo the action
  }
  servo.write(0); // original position
}

/* Calculations:
 * v = s/t, or s = vt 
 * v_pulse (in dry air) = 330 m/s = 33000 cm/s
 * The pulseIn function measures in µs (1 sec = 10^6 µs)
 * So, v_pulse = 33000 cm/10^6 µs = 0.033 cm/µs
 * Therefore, as s = vt, s = 0.033*duration (s (the distance) is in cm)
  */
