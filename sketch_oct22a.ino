#include <buffer.h>
#include <crc.h>
#include <datatypes.h>
#include <VescUart.h>

#include <Servo.h>
Servo esc1;
Servo esc2;

unsigned long start1;
int pwm1;
unsigned long start2;
int pwm2;

int output1;
int output2;
/*
  //this should be interrupt
  volatile byte pulse;
  float rpm;
  unsigned long timeStamp;
  unsigned long newTime;
  //cycle count
  unsigned int count;
  //if there's a new timestamp
  bool newTimeStamp;
  //sample threshold. arbitrary
  const unsigned int THRESH = 20;
  //arbitrary. how many cycles before serial printing the rpm value
  const float CYCLESTOPRINT = 10;
  //poles in motor
  const float POLES = 10.0;
  //milliseconds in a minute
  const float MILTOMIN = 60000.0;

  //must be an interrupt pin
  const unsigned int PININ = 3;
*/

VescUart UART1;
VescUart UART2;

void setup() {

  pinMode(2, INPUT);    // input from r/c rec
  pinMode(3, INPUT);    // input from r/c rec
  attachInterrupt(0, timeit1, CHANGE);     // pin 2
  attachInterrupt(1, timeit2, CHANGE);     // pin 3

  esc1.attach(4);
  esc2.attach(5);

  /*
    pulse = 0;
    rpm = 0;
    timeStamp = 0;
    newTimeStamp = true;
    count = 0;
    attachInterrupt(digitalPinToInterrupt(PININ), revCount, FALLING);
  */

  Serial.begin(9600);

  Serial1.begin(38400);
  Serial2.begin(19200);

  while (!Serial) {
    ;
  }
  UART1.setSerialPort(&Serial1);
  UART2.setSerialPort(&Serial2);

}

void loop() {
  /*
    //have THRESH samples been taken?
    if (newTimeStamp) {
    noInterrupts();//disable interrupt
    newTimeStamp = false;//toggle newTimeStamp back
    count++;//increment count so cycles can compare so we aren't printing every cycle
    //(pulse/5) / millis/60,000
    rpm = (((float)pulse) * 2.0 / (((float)(newTime - timeStamp) / MILTOMIN) * POLES)); //calc rpm
    //check and print
    if (count >= CYCLESTOPRINT) {
      count = 0;
      Serial.println(rpm);
    }
    //reset pulse and timestamp
    pulse = 0;
    timeStamp = millis();
    interrupts();//reattach interrupt
    }
  */

  if (pwm1 <= 1480) {
    output1 = 0;
    output2 = 0;
  } else {
    output1 = pwm1 + (pwm2 - 1480);
    output2 = pwm1 - (pwm2 - 1480);
    if (pwm1 > 1710) {
      if (output1 < 1710) {
        output1 = 1710;
      }
      if (output2 < 1710) {
        output2 = 1710;
      }
    }
    output1 = constrain(output1, 1530, 1800);
    output2 = constrain(output2, 1530, 1800);

    esc1.writeMicroseconds(output1);
    esc2.writeMicroseconds(output2);

    Serial.print("pwm1: ");
    Serial.print(pwm1);
    Serial.print(' ');
    Serial.print("output1: ");
    Serial.print(output1);
    Serial.print(' ');
    Serial.print("pwm2: ");
    Serial.print(pwm2);
    Serial.print(' ');
    Serial.print("output2: ");
    Serial.println(output2);
    /*
      if ( UART1.getVescValues() ) {
        Serial.print("RPM Left: ");
        Serial.println(UART1.data.rpm);
      }
      else
      {
        Serial.println("Failed to get data from ESC Left!");
      }

      if ( UART2.getVescValues() ) {
        Serial.print("RPM Right: ");
        Serial.println(UART2.data.rpm);
      }
      else
      {
        Serial.println("Failed to get data from ESC Right!");
      }
    */
    delay(100);
  }
}


// timer functions

void timeit1() {
  if (digitalRead(2) == HIGH) {
    start1 = micros();
  }
  else {
    pwm1 = micros() - start1;
  }
}


void timeit2() {
  if (digitalRead(3) == HIGH) {
    start2 = micros();
  }
  else {
    pwm2 = micros() - start2;
  }
}
/*
  void revCount() {
  //update pulse
  pulse++;
  if (pulse >= THRESH) {
    newTime = millis();
    newTimeStamp = true; // flag to tell main code to read the value of timeStamp
  }
  }
*/
