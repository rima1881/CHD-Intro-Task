#include <Servo.h>
#include "RTClib.h"
//SD Library has to be added to libraries.txt
#include <SD.h>

//pins section
#define CS_PIN 10
#define SERVO_PIN 9

int val;
int sec;
Servo servo;
RTC_DS1307 rtc;
File logs;
DateTime now;


void setup() {

  
  //setting up the console
  Serial.begin(11600);


  //setting up servo
  servo.attach(SERVO_PIN);



  //setting up the clock
  rtc.begin();
  //the value of sec will be never -1 so the first if for logsHandel always will run
  sec = -1;


  //setting up the SD card
  Serial.println("Initializing SD card... ");

  if (!SD.begin(CS_PIN)) {
    Serial.println("Card initialization failed!");
    while (true);
  }
  

  //getting the logs.txt file
  Serial.println("Initializing logs file...");
  logs = SD.open("logs.txt", FILE_WRITE);

  if(!logs){
    Serial.println("logs Initialization failed!");
    while(true);
  }

  //finishing initialization
  Serial.println("Initialization done.");

  
}

void servoHandle(){
  
  //generating the angle for servo
  //servo input and potentiometer output have reverse relation hance it has to be mirrored
  //x:(0 , 180) -> x'= 180 - (x) -> x':(0 , 180)
  servo.write(180 - val);

}

void logsHandle(){ 

  
  //output time generation section
  Serial.print("[");
  logs.print("[");

  Serial.print(now.year(), DEC);
  logs.print(now.year(), DEC);

  Serial.print("/");
  logs.print("/");

  Serial.print(now.month(), DEC);
  logs.print(now.month(), DEC);

  Serial.print("/");
  logs.print("/");

  Serial.print(now.day(), DEC);
  logs.print(now.day(), DEC);

  Serial.print(" ");
  logs.print(" ");

  Serial.print(now.hour(), DEC);
  logs.print(now.hour(), DEC);

  Serial.print(":");
  logs.print(":");

  Serial.print(now.minute(), DEC);
  logs.print(now.minute(), DEC);

  Serial.print(":");
  logs.print(":");

  Serial.print(now.second(),DEC);
  logs.print(now.second(),DEC);

  Serial.print("]");
  logs.print("]");



  //ouput Angle generation section
  Serial.print(" Angle: ");
  logs.print(" Angle: ");

  // x:(0 , 180) -> x'= 90-x -> x':(90,-90) 
  Serial.print(val - 90);
  logs.print(val - 90);

  Serial.print(" degrees\n");
  logs.print(" degrees");

  logs.println(" ");


}



void loop() {


  //getting the current time
  now = rtc.now();

  //getting the percentage of the potentiometer
  val = map(analogRead(0),0,1023,0,180);

  //changing servo as fast as possible
  servoHandle();

  //logging per second
  if(sec != now.second()){
    logsHandle();
    sec = now.second();
  }
  


}