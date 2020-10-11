#include <Servo.h>

int potPin = A1;
int potVal = 0;
float mapVal = 0.0;

int escLpin = 6;

Servo escL;
int escLVal = 0;  
int maxVal = 180; 
int minPW = 1208; //defining min Pulse Width
int maxPW = 2200;




void setup() {
  // put your setup code here, to run once:
 
 escL.attach(escLpin, minPW, maxPW);  
Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
 potVal  = analogRead(potPin);
 
 mapVal = (potVal/1023.0)*180.0;

 escL.write((int)mapVal);

 Serial.print(potVal);
 Serial.print(" ");
 Serial.println((int)mapVal);
 //delay(10);

 
   //Serial.print("Mapped potVal: ");
   //Serial.print(potVal); Serial.print("; ");
   //Serial.print("ESC L Value: ");
   //Serial.print(escLVal); Serial.print("; ");
   
}
