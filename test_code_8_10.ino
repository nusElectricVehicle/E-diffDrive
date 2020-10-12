#include <Servo.h>

int potPin = A1;
int potVal = 0;
float mapVal = 0.0;

int escLpin = 6;

Servo escL;
int escLVal = 0;  // variable to keep assigned motor speed value to the eS
int minPW = 1208; // define min Pulse Width
int maxPW = 2200; // define max Pulse Width
int onoff = 0;
int mode = 0;


void setup() {
  // put your setup code here, to run once:
 
escL.attach(escLpin, minPW, maxPW);  
Serial.begin(9600);


}

void loop() {
  if (Serial.available() > 0)
  {
    onoff = Serial.read(); // get input from serial
  }
  
  if (onoff == 'a') // typing 'a' will trigger 'ON' mode
  {
    mode = 1;
  } 
  else if (onoff == 'b') // typing 'b' will trigger 'OFF' mode
  {
    mode = 0;
  }
  
  // get reading from potentiometer
  potVal  = analogRead(potPin); 
  
  if (mode == 1) // 'ON' mode: assign motor speed using potentiometer
  {
    mapVal = (potVal/1023.0)*180.0;
    escLVal = (int)mapVal;
  }
  else // 'OFF' mode: motor speed = 0
  {
    escLVal = 0;
  }
 
 // assign motor speed 
 escL.write(escLVal);
  
 // print out values from potentiometer and assigned motor speed
 Serial.print(potVal);
 Serial.print(" ");
 Serial.println(escLVal);
 delay(100);

 
   //Serial.print("Mapped potVal: ");
   //Serial.print(potVal); Serial.print("; ");
   //Serial.print("ESC L Value: ");
   //Serial.print(escLVal); Serial.print("; ");
   
}
