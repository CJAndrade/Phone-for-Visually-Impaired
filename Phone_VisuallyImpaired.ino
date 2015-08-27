//Mode switch which decide between the Phone mode and eye stick
const int modeSwitch = 10;
//Call buttons
const int call1 = 3;
const int call2 = 4;
const int call3 = 5;
const int call4 = 6;

//message button
const int message1 = 11;
const int message2 = 12;

//Vibration motor 
const int motorPin = A0; //Note because the number of digital pins are short using A0 as digital

//Pin the maxbotix sensor is connected to measure the distance from the obstacle in the front
const int maxbotix = 2;
// Phone_Modify this value to the distance in inches from the object based on the persons height 
const int obstacleAt = 10; // in inches considering phone will be pointed downwards


long duration, inches;

void setup() 
{  
Serial.begin(9600);
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
if(digitalRead(modeSwitch)== LOW)
{ //Phone mode
  Serial.println("You are in Phone Mode");
if(digitalRead(call1) == LOW){
  Serial.println("Calling number 1");
}
else if(digitalRead(call2) == LOW){
  Serial.println("Calling number 2");
}
else if(digitalRead(call3) == LOW){
  Serial.println("Calling number 3");
}
else if(digitalRead(call4) == LOW){
  Serial.println("Calling number 4");
}
else if(digitalRead(message1) == LOW){
  Serial.println("Sending message 1");
}
else if(digitalRead(message2) == LOW){
  Serial.println("Sending message 2");
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



