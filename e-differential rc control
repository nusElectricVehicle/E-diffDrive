/*
   EG3301R FTS-308 Shell Eco-Marathon Project
   E-DIFFERENTIAL SYSTEM

   Developed by:
   Nathanael Septianto Pratama A0184578L
   Jagtap Sumeet Manish A0184354B

   Description:
   This project aims to control the speed distribution to two sensored BLDC motors to establish the initial building blocks of an E-differential system
   An RC transmitter is used to simulate throttle and steering of our vehicle as a proof of concept of our algorithm
*/

// define VESC UART Baud Rate, which is 115200 bps
#define BAUD_RATE 115200

// include VESC UART to Arduino Mega library
#include <VescUart.h>

// include servo library for the ESCs
#include <Servo.h>

// initiate Servo class
Servo escL;
Servo escR;

// initiate VescUart class
VescUart UART_R;
VescUart UART_L;

unsigned long start1;
int throttle; // throttle PWM signal
unsigned long start2;
int steer; // steer PWM signal

int outputL;
int outputR;
float rpm_R;
float rpm_L;

void setup() {

  pinMode(2, INPUT);    // input from r/c rec
  pinMode(3, INPUT);    // input from r/c rec
  attachInterrupt(0, timeit1, CHANGE);     // pin 2
  attachInterrupt(1, timeit2, CHANGE);     // pin 3

  escR.attach(5); // Serial1
  escL.attach(6); // Serial2

  Serial.begin(BAUD_RATE);
  // Serials for UART Communication
  Serial1.begin(BAUD_RATE); // ESC Right
  Serial2.begin(BAUD_RATE); // ESC Left

  UART_R.setSerialPort(&Serial1);
  UART_L.setSerialPort(&Serial2);

}

void loop() {

  if (throttle <= 1383) { // throttle is at its default position
    outputL = 0;
    outputR = 0;
  } else { // throttle is engaged
    // assign motor speed distribution
    if (steer < 1366) {
      // turn left
      outputL = throttle + (steer - 1366);
      outputR = throttle;
    } else if (steer == 1366) {
      // go straight
      outputL = throttle;
      outputR = throttle;
    } else if (steer > 1366) {
      // turn right
      outputL = throttle;
      outputR = throttle - (steer - 1366);
    }

    if (throttle > 1520) { // throttle is above minimum distributed speed
      // set the minimum speed for both motors after speed distribution
      if (outputL < 1520) {
        outputL = 1520;
      }
      if (outputR < 1520) {
        outputR = 1520;
      }
    } else { // throttle is below minimum distributed speed
      // both motors run in accordance with the throttle
      outputL = throttle;
      outputR = throttle;
    }

    // setting min and max PWM outputs at 1400 and 1800
    outputL = constrain(outputL, 1400, 1800);
    outputR = constrain(outputR, 1400, 1800);

    // assign PWM outputs to ESCs
    escL.writeMicroseconds(outputL);
    escR.writeMicroseconds(outputR);
  }
  
  Serial.print(throttle);
  Serial.print(' ');
  Serial.print(steer);
  Serial.print(' ');

  Serial.print(outputL);
  Serial.print(' ');
  Serial.print(outputR);
  Serial.print(' ');

  // get RPM reading from ESC Left
  if ( UART_L.getVescValues() ) {
    // divide ERPM from ESC by number of pole pairs (7) to get RPM
    rpm_L = UART_L.data.rpm / 7; 
    // display converted RPM to Serial Monitor
    Serial.print("ESC Left = ");
    Serial.print(rpm_L);
    Serial.print(" RPM");
  } else {
    Serial.println("Failed to get data from ESC Left!");
  }

  // get rpm reading from ESC Right
  if ( UART_R.getVescValues() ) {
    // divide ERPM from ESC by number of pole pairs (7) to get RPM
    rpm_R = UART_R.data.rpm / 7;
    // display converted RPM to Serial Monitor
    Serial.print(" ESC Right = ");
    Serial.print(rpm_R);
    Serial.println(" RPM; ");
  } else {
    Serial.println("Failed to get data from ESC Right!");
  }

  delay(100);
}


// timer functions timeit1() and timeit2()
void timeit1() {
  if (digitalRead(2) == HIGH) {
    start1 = micros();
  }
  else {
    throttle = micros() - start1;
  }
}


void timeit2() {
  if (digitalRead(3) == HIGH) {
    start2 = micros();
  }
  else {
    steer = micros() - start2;
  }
}
