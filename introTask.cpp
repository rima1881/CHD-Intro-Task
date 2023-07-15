#include <Servo.h>
#include "RTClib.h"

int val;
int angle;
Servo servo;
RTC_DS1307 rtc;


void setup() {

  servo.attach(9);  
  Serial.begin(9600);
  rtc.begin();
}

void loop() {

  DateTime now = rtc.now();

  //getting the percentage of the potentiometer
  val = map(analogRead(0),0,1023,0,100);

  //generating the angle
  //this angle is just used for servo and not for "logging"
  angle = 180 - val*1.8;
  servo.write(angle);

  Serial.println(now.second(),DEC);


}