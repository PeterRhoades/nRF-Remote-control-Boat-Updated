/*                          
NANO_Boat_Stearing_Transmitter_Ver1_2:
Folder NANO_Boat_Stearing_Transmitter_Ver1_2:
Serial.println("A0  Right=0  Left=1027\n");
                             
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
const byte address[6] = "00092";
int data[4] = {0, 0, 0, 0}; //Data Array to be Sent:
RF24 radio(7,8);
int SWR = 4;
const float ver = 1.2; //Version Number Variable:

void setup() {
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
  Serial.println("Code 080520231801");
  Serial.print("NANO_Boat_Stearing_Transmitter_Ver:"); Serial.print (ver, 1); Serial.println("\n");
  
 }
 
void loop() 
 {
  delay(50);
 if (analogRead(A0) > 550) //Joystick Left: 
  {
  int left = (analogRead(A0));
  
  data[2] = 40; //Code to Identify the data[?] = 25: 
   radio.write( data, sizeof(data) );
   Serial.print ("  A0 MSG = "); Serial.print (left); Serial.print ("  Left MSG= "); Serial.print (data[2]);
   Serial.println("  Sent");
  }
 if (analogRead(A0) < 400) //Joystick Right: 
  {
  int right = (analogRead(A0));
 data[2] = 35; //Code to Identify the data[?] = 30: 
   radio.write( data, sizeof(data) );
   Serial.print ("  A0 MSG = "); Serial.print (right); Serial.print ("  Right MSG= "); Serial.print(data[2]);
   Serial.println("  Sent");
  }
   if (digitalRead(SWR) == LOW) //Top Button Clossed Serial.print(digitalRead(SW_pin))
  {
   data[2] = 3; 
  radio.write( data, sizeof(data) );
   Serial.print ("Rudder 90° "); 
    Serial.print(data[2]); 
     Serial.println("  Sent");
  } 
}
