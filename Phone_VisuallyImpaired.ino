//Code for Phone for Visual impaired V1.0
//Author: Carmelito Andrade Date:27 August 2015
//Code based on sample code at http://www.seeedstudio.com/wiki/GPRS_Shield_V1.0
//CC BY-SA 3.0 US
//To test your GPRS sheild with AT commands before uploading this sketch refer to http://www.seeedstudio.com/wiki/GPRS_Shield_V1.0
#include <SoftwareSerial.h> 
#include <String.h>
#include "PhoneSettings.h"//Modify the .h file with the number to call and message and obstacle distance
SoftwareSerial mySerial(7, 8);
//Mode switch which decide between the Phone mode and eye stick
const int modeSwitch = 6;//was 10
//Call buttons
const int call1 = 4; 
const int call2 = 11;
const int call3 = 5;
const int call4 = 12;
//message button
const int message1 = 3;
const int message2 = 10;

//Vibration motor 
const int motorPin = A0; //Note because the number of digital pins are short using A0 as digital

//Pin the maxbotix sensor is connected to measure the distance from the obstacle in the front
const int maxbotix = 2;
// Phone_Modify this value to the distance in inches from the object based on the persons height 
const int obstacleAt = OBSTACLE_DISTANCE; // in inches considering phone will be pointed downwards


long duration, inches;

void setup() 
{  
mySerial.begin(19200);   // the GPRS baud rate   
Serial.begin(19200);    // the GPRS baud rate 
delay(500);
//Serial.begin(9600);
pinMode(modeSwitch, INPUT_PULLUP);
pinMode(call1, INPUT_PULLUP);
pinMode(call2, INPUT_PULLUP);
pinMode(call3, INPUT_PULLUP);
pinMode(call4, INPUT_PULLUP);
pinMode(message1, INPUT_PULLUP);
pinMode(message2, INPUT_PULLUP);
pinMode(motorPin, OUTPUT);
//pinMode(9,OUTPUT);//Pin 9 default power up http://www.seeedstudio.com/wiki/GPRS_Shield_V1.0
} 

void loop() 
{ 
if(digitalRead(modeSwitch)== HIGH) //CJA changed to high
{ //Phone mode
      Serial.println("You are in Phone Mode");
    if(digitalRead(call1) == LOW){
      Serial.println("Calling number 1");
      Serial.print(CALL_NUMBER1);
      DialVoiceCall(CALL_NUMBER1);
    }
    else if(digitalRead(call2) == LOW){
      Serial.println("Calling number 2");
      Serial.print(CALL_NUMBER2);
      DialVoiceCall(CALL_NUMBER2);
    }
    else if(digitalRead(call3) == LOW){
      Serial.println("Calling number 3");
      Serial.print(CALL_NUMBER3);
      DialVoiceCall(CALL_NUMBER3);
    }
    else if(digitalRead(call4) == LOW){
      Serial.println("Calling number 4");
      Serial.print(CALL_NUMBER4);
      DialVoiceCall(CALL_NUMBER4);
    }
    else if(digitalRead(message1) == LOW){
      Serial.println("Sending message 1");
      String messageNumber = MESSAGE_NUMBER1;
      Serial.print(messageNumber);
      SendTextMessageOne();
    }
    else if(digitalRead(message2) == LOW){
      Serial.println("Sending message 2");
      Serial.print(MESSAGE_NUMBER2);
      SendTextMessageTwo();
    }
    else{
      Serial.println("Do Nothing");
    }
      
}else{
         //eye stick mode
          Serial.println("eye stick mode");
          duration = 0;
          inches = 0;
          // The trigger is sent by a HIGH pulse of 2 or more microseconds.
          // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
          pinMode(maxbotix, OUTPUT);
          digitalWrite(maxbotix, LOW);
          delayMicroseconds(2);
          digitalWrite(maxbotix, HIGH);
          delayMicroseconds(5);
          digitalWrite(maxbotix, LOW);
        
          // The same pin is used to read the signal,pulse whose duration is the time (in microseconds) from the sending
          pinMode(maxbotix, INPUT);
          duration = pulseIn(maxbotix, HIGH);
          Serial.println("Duration time");
          Serial.println(duration);
          // convert the time into a distance in inches
          inches = microsecondsToInches(duration);
          
          Serial.println("Distance in inches");
          Serial.println(inches);
          // check for obstacle distance to vibrate motor
          if ( inches < obstacleAt ) {
            Serial.println("Object in front of you , vibrating vibration motor");
            //Vibrate the Vibration motor for 1 second
            digitalWrite(motorPin, HIGH);
            delay(1000);
          }else
          {
            digitalWrite(motorPin, LOW);
            delay(100);
          }
}
  
  

  delay(500); // Phone_Modify change this to a lower value
}

long microsecondsToInches(long microseconds)
{
  // basically sound travels at 1130 feet per second,which means 73.746 microseconds per inch.
  // divide by 2 to get the distance of the obstacle.
  return microseconds / 74 / 2;
}

///this function is to send a sms message
 void SendTextMessageOne()
{
  mySerial.print("AT+CMGF=1\r");    //Because we want to send the SMS in text mode
  delay(100);
  mySerial.println("AT + CMGS = \"" MESSAGE_NUMBER1 "");//send sms message// mySerial.println("AT + CMGS = \"+12222222222\"");
  delay(100);
  mySerial.println(MESSAGE_TEXT1);//the content of the message //mySerial.println("please call Landline");
  delay(100);
  mySerial.println((char)26);//the ASCII code of the ctrl+z is 26
  delay(100);
  mySerial.println();
}

 void SendTextMessageTwo()
{
  mySerial.print("AT+CMGF=1\r");    //Because we want to send the SMS in text mode
  delay(100);
  mySerial.println("AT + CMGS = \"" MESSAGE_NUMBER2 "");
  delay(100);
  mySerial.println(MESSAGE_TEXT2);//the content of the message
  delay(100);
  mySerial.println((char)26);//the ASCII code of the ctrl+z is 26
  delay(100);
  mySerial.println();
}

///this function is to dial a voice call
void DialVoiceCall(String number)
{
  mySerial.println("ATD + " + number + ";");//dial the number 
  delay(100);
  mySerial.println();
}
 
 


