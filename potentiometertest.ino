// This program is used to test motor control with potentiometer, motor signal pin: D6

#include <Servo.h>

const uint8_t potPin = A1; // input pin for the potentiometer
const uint8_t escLPin = 6; // digital pin for the left ESC
// int escRPin = 7; // digital pin for the right ESC

Servo escL; // create servo object to control the left ESC
// Servo escR; // create servo object to control the right ESC
int escLVal=0;
// int escRVal=0;
int maxVal = 180;

void setup() {
  escL.attach(escLPin);
  escL.writeMicroseconds(500);
 // escR.attach(escRPin,minPW,maxPW);
  
  Serial.begin(9600); // open the serial port at 9600 bps for Serial monitor

}

void loop() {
  int potVal = analogRead(potPin); // reads raw value from pot
  potVal = map(potVal, 0, 1023, 0, 180);
  
  /*
  if (potVal == maxVal/2) {
    escLVal=maxVal;
    escRVal=maxVal;
  } else if (potVal < 90) {
    escLVal=120+(2.0/3)*potVal;
    escRVal=180;
  } else if (potVal > 90) {
    escLVal=180;
    escRVal=180-(2.0/3)*(potVal-90);
  }

  escL.write(escLVal);
  escR.write(escRVal);
  */
  escL.writeMicroseconds(potVal);

  
  Serial.print("Mapped potVal: ");
  Serial.print(potVal); Serial.print("; ");
  /*
  Serial.print("ESC L Value: ");
  Serial.print(escLVal); Serial.print("; ");
  Serial.print("ESC R Value: ");
  Serial.print(escRVal); Serial.println("; ");
  */
  delay(100);
  
}
