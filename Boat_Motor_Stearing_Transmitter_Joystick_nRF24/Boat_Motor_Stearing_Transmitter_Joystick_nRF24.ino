/*                          
Boat_Motor_Stearing_Transmitter_Joystick_nRF24:
Folder Boat_Motor_Stearing_Transmitter_Joystick_nRF24:
                             
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

#include <Wire.h>
#include  <SPI.h>
#include "RF24.h"
const byte address[] = "00092";
int data[4] = {0, 0, 0, 0}; //Data Array to be Sent:
RF24 radio(7,8);
const long onDurationB = 500; //Button Delay:
long rememberTime=0;
int SWR = 4;

void setup() 
{
  Serial.begin(115200);
  Serial.println("In Setup");
  Wire.begin();
  radio.begin();
  radio.openWritingPipe(address);
  pinMode(SWR, INPUT_PULLUP); //Pull-Up for Joystick Switch:
  nRF24(); 
 }
void nRF24()
 {
  Serial.println("nRF Tranciver"); 
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
  Serial.println("Code 170920231128");
  Serial.print("Boat_Stearing_Transmitter\n"); 
  
 }
 
void loop() 
 {
 while (analogRead(A7)) 
 {
 delay (50);
  
 if (analogRead(A0) > 550) //Joystick Left: 
 {
  int left = (analogRead(A0));
  data[2] = 40; //Code to Identify the data[?] = 40: 
   radio.write( data, sizeof(data) );
   Serial.print ("left "); Serial.print (data[2]);
   Serial.println(" Sent");
}
 if (analogRead(A0) < 400) //Joystick Right: 
{
  int right = (analogRead(A0));
  data[2] = 35; //Code to Identify the data[?] = 35: 
   radio.write( data, sizeof(data) );
   Serial.print ("Right "); Serial.print (data[2]);
   Serial.println(" Sent");
}
 if (digitalRead(SWR) == LOW && (millis()- rememberTime) >= onDurationB)
{
  data[0] = 7;
  data[1] = 0; 
  data[2] = 3;
   radio.write( data, sizeof(data) );
   Serial.println ("Rudder 90° Power Off"); 
   rememberTime=millis();
 } 
 if (analogRead(A3) <460) //Joystick Forward:
 {
int forward = (analogRead(A1));
 data[0] = 15; //Code to Identify the data[?] = 15: 
 data[1] = map(forward, 460, 50, 50, 255); 
    if (data[1] > 255) data[1] = 255; //Limit data[1] to below 255:
    radio.write( data, sizeof(data) );
     Serial.print (data[0]); Serial.print (" Forward "); Serial.print (data[1]);
     Serial.println(" Sent");
 }
 if (analogRead(A3) > 560) //Joystick Reverse: 
 {
int reverse = (analogRead(A1));
 data[0] = 20; //Code to Identify the data[?] = 20: 
 data[1] = map(reverse, 560, 990, 50, 255);
    if (data[1] > 255) data[1] = 255; //Limit data[1] to below 255:
    radio.write( data, sizeof(data) );
     Serial.print (data[0]); Serial.print (" Reverse "); Serial.print (data[1]);
     Serial.println(" Sent");
  }
 }
}
