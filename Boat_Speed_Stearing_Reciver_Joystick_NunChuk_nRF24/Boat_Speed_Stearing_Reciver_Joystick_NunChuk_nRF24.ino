/*
Boat_Speed_Stearing_Reciver_Joystick_NunChuk.
Folder Boat_Speed_Stearing_Reciver_Joystick_NunChuk.
nRF Transceiver, Connected to L298N Motor Drive & Servo.
Works with JoyStick and NunChuk.
  
  nRF Tranciver 
  1 = GRN  Black   
  2 = 3.3v Red
  3 = CE   Pin 7  Blue
  4 = CSN  Pin 8  Breen
  5 = SCK  Pin 13 Yellow
  6 = MOSI Pin 11 White
  7 = MISO Pin 12 Orange
   _______________________
  | 1 | 2 |              |
  | 3 | 4 |              | 
  | 5 | 6 |              |
  |_7_|___|______________|
*/

#include <Servo.h>
#include  <SPI.h>
#include "RF24.h"
#include <Wire.h>
int data[4] = {0, 0, 0, 0}; //[0]=Foward, Reverse, Stop [1]=PWM Foward & Reverse [2]=Stearing [3]=Rudder turn control:
RF24 radio(7,8);               
Servo myservo;
const byte address[6] = "00092"; //Pipe Number same as nRF Sender:
int i = 90; //Servos Variable Center Position -> 90°:
int servoPin = 9; //Boat Rudder Servo:
// Motor connections
int enA = 3;
int in1 = 5;
int in2 = 6;


void setup()
{
  Serial.begin(115200);
  Serial.println("In Setup");
 radio.begin();
 radio.openReadingPipe(1,address);
 radio.startListening();
 Wire.begin();
 pinMode(enA, OUTPUT); //Set all the motor control pins to outputs:
 pinMode(in1, OUTPUT);
 pinMode(in2, OUTPUT);
  digitalWrite(in1, LOW); //Turn off motors - Initial State:
  digitalWrite(in2, LOW);
    myservo.attach(servoPin);//,570, 2540);
    myservo.write(90); //Move Servos to Center Position -> 90°:
    nRF24();
  }
 void nRF24()
 {
  Serial.println("nRF Tranciver to NANO"); 
  Serial.println("1 = GRN  Black");   
  Serial.println("2 = 3.3v Red");
  Serial.println("3 = CE   Pin 7  Blue");
  Serial.println("4 = CSN  Pin 8  Breen");
  Serial.println("5 = SCK  Pin 13 Yellow");
  Serial.println("6 = MOSI Pin 11 White");
  Serial.println("7 = MISO Pin 12 Orange");
  Serial.println(" _______________________");
  Serial.println("| 1 | 2 |              |");
  Serial.println("| 3 | 4 |              |");
  Serial.println("| 5 | 6 |              |");
  Serial.println("|_7_|___|______________|");
  Serial.println("Code 080520231807");
  Serial.print("Boat Motor & Stearing JoyStick and NunChuk Reciver\n"); 
 }

void loop()
{
 if ( radio.available() )
 {
 radio.read(data, sizeof(data));
 
if (data[0] == 15) //Data Header Forward Direction:
  {
   Serial.print(data[0]);
   Serial.print(" Forward = ");
   Serial.print(data[1]); //Speed PWM Motor, data[1] = 0 to 255:
   Serial.println(" Received");
   analogWrite(enA, data[1]); //Send Speed data[1] PWM to Motor:
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
  }
if (data[0] == 20) //Reverse:
  {
   Serial.print(data[0]);
   Serial.print("  Reverse ");
   Serial.print(data[1]); //Speed PWM Motor, data[1] = 0 to 255:
   Serial.println(" Received");
   analogWrite(enA, data[1]); //Send Speed data[1] PWM to Motor:
 digitalWrite(in1, LOW);
 digitalWrite(in2, HIGH);
  }
if (data[0] == 7)//STOP!!!!!
  {
   Serial.print(data[0]);
   Serial.print("  ");
   Serial.print(data[1]); //Speed PWM Motor, data[1] = 0:
   Serial.print(" ");
   Serial.println ("Stop Motor"); 
   analogWrite(enA, data[1]); //Send Speed data[1] PWM to Motor:
   digitalWrite(in1, LOW); //Engine Brake:
   digitalWrite(in2, LOW); //Engine Brake:
 }
if (data[2] == 25) //Stearing Data:
 {
  Serial.print(data[2]);
   i = data[3]; //Rudder 25 to 155°:
    Serial.print("  ");
    Serial.print(i); Serial.print("°");
    myservo.write(i);
   Serial.print(" Left nunChuk ");
  Serial.println("Received");
  
 }
if (data[2] == 30) //Stearing Data:
{
  Serial.print(data[2]);
    i = data[3]; //Rudder 25 to 155°:
     Serial.print("  ");
    Serial.print(i); Serial.print("°");
    myservo.write(i);
   Serial.print(" Right nunChuk ");
  Serial.println("Received");
  
}
if (data[2] == 3) //Rudder to 90°:
 {  
  Serial.print(data[2]);
   i = 90;
       Serial.print("  ");
      Serial.print(i);
      myservo.write(i);
     Serial.print("°");
    Serial.println(" Center Stearing Received");
 }
 if (data[2] == 35)
 {
  Serial.print(data[2]);
   i = i+5 ;
   if (i > 155) 
   {
    i = 155;
   }
    Serial.print("  ");
    Serial.print(i); Serial.print("°");
    myservo.write(i);
   Serial.print(" Right JoyStick ");
  Serial.println("Received");
  
 }
 if (data[2] == 40)
 {
  Serial.print(data[2]);
   i = i-5 ;
   if (i < 25) 
   {
    i = 25;
   }
    Serial.print("  ");
    Serial.print(i); Serial.print("°");
    myservo.write(i);
   Serial.print(" Left JoyStick ");
  Serial.println("Received");
  
 }
 }
}

 
