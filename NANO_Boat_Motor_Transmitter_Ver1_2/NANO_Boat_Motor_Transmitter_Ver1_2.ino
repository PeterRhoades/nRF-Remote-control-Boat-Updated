/*Peter Rhoades©:
Monday 02/01/23:
NANO Boat Motor TransmitterVer1.2:
Folder NANO_Boat_Motor_Transmitter_Ver1_2:
Mapping reset for Forward & Reverse Joystick Range better:                           
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
int data[4] = {0, 0, 0, 0}; //Data Array:
RF24 radio(7,8);
int SWL = 4;
const float ver = 1.2; //Version Number Variable:

void setup() {
Serial.begin(115200);
 Serial.println("In Setup");
  Wire.begin();
   radio.begin();
  radio.openWritingPipe(address);
 pinMode(SWL, INPUT_PULLUP);
 data[0] = 7;
 data[1] = 0; 
 radio.write( data, sizeof(data) );
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
  Serial.println("Code 080520231236");
  Serial.print("NANO Boat Motor Transmitter Ver:"); Serial.print (ver, 1); Serial.println("\n");
 }
 
void loop() 
 {
 delay(50);
 if (analogRead(A0) <460) //Joystick Forward:
 {
int forward = (analogRead(A0));
 data[0] = 15; //Code to Identify the data[?] = 15: 
 Serial.print(data[0]);
 data[1] = map(forward, 460, 50, 50, 255); 
    if (data[1] > 255) data[1] = 255; //Limit data[1] to below 255:
    radio.write( data, sizeof(data) );
     Serial.print ("  A0 MSG = "); Serial.print (forward); Serial.print ("  Mapped MSG= "); Serial.print (data[1]);
      Serial.println("  Sent");
 }
 if (analogRead(A0) > 560) //Joystick Reverse: 
 {
int reverse = (analogRead(A0));
 data[0] = 20; //Code to Identify the data[?] = 20: 
  Serial.print(data[0]);
   data[1] = map(reverse, 560, 990, 50, 255);
    if (data[1] > 255) data[1] = 255; //Limit data[1] to below 255:
    radio.write( data, sizeof(data) );
     Serial.print ("  A0 MSG = "); Serial.print (reverse); Serial.print ("  Mapped MSG= "); Serial.print(data[1]);
      Serial.println("  Sent");
 }
 if (digitalRead(SWL) == LOW) //Top Button Clossed Serial.print(digitalRead(SW_pin))
 {
 data[0] = 7;
 data[1] = 0; 
 radio.write( data, sizeof(data) );
   Serial.print(data[0]);Serial.print(" ");
    Serial.print(data[1]);Serial.print(" ");
   Serial.print (" = Button Left "); Serial.print (digitalRead(SWL));
  Serial.println("  Sent");
 }
}
