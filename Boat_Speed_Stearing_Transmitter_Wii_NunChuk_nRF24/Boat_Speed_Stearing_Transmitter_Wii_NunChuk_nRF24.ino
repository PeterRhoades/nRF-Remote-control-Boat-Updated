/*
Boat_Stearing_Transmitter_Wii_NunChuk_nRF24
folder \\Boat_Stearing_Transmitter_Wii_NunChuk_nRF24 
Code 180920231919
 Wii nunchuk
 Red to GND
 Green to 3.3v
 Yellow to SDA
 White to SCL
 */

#include <Wire.h>
#include  <SPI.h>
#include "RF24.h"
#include "nunchuk.h"
const byte address[6] = "00092"; //rf24 Address:
const long onDurationB = 500; //Button Delay:
const long onDurationR = 50; //Rudder Delay:
const long onDurationS = 50; //Speed Delay:
long rememberTime=0;
int data[4] = {0, 0, 0, 0}; //Data Array
RF24 radio(7,8); 


void setup() {
    Serial.begin(115200);
    Serial.println("In Setup");
    Wire.begin();
    radio.begin();
    nunchuk_init();
    radio.openWritingPipe(address);
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
  Serial.println("Code 180920231919");
      data[0] = 7;
      data[1] = 0;                         
      data[2] = 3; 
      radio.write( data, sizeof(data) ); //Used to Stop Motor and 90° Rudder at StartUp:
    }

void loop() 
    {
    while (nunchuk_read()) {
    
    if (nunchuk_joystickX() < -10 && (millis()- rememberTime) >= onDurationR) 
    {
      Serial.print ("Left "); Serial.println (nunchuk_joystickX());
      data[2] = 25; //Code to Identify the data[?] = 25 Nunchuk Stearing:
      data[3] = map(nunchuk_joystickX(), -127, 128, 25, 155); //map Rudder 25 to 155°
      radio.write( data, sizeof(data) );
      Serial.print (" data[2] "); Serial.println (data[2]);
      Serial.print (" data[3] "); Serial.println (data[3]);
      rememberTime=millis();
    }
     if (nunchuk_joystickX() > 10 && (millis()- rememberTime) >= onDurationR) 
    {
      Serial.print ("Right "); Serial.println (nunchuk_joystickX());
      data[2] = 30; //Code to Identify the data[?] = 30 Nunchuk Stearing:
      data[3] = map(nunchuk_joystickX(), -127, 128, 25, 155); //map Rudder 25 to 155°
      radio.write( data, sizeof(data) );
      Serial.print (" data[2] "); Serial.println (data[2]);
      Serial.print (" data[3] "); Serial.println (data[3]);
      rememberTime=millis();
    }
     if (nunchuk_joystickY() > 20 && (millis()- rememberTime) >= onDurationS) 
    {
      data[0] = 15; //Code to Identify the data[?] = 15:
      data[1] = map(nunchuk_joystickY(), 20, 127, 40, 255); //map Motor Speed 40 to 255 PWM:
      radio.write( data, sizeof(data) );
      Serial.print ("Foward "); Serial.print (data[0]);
      Serial.print (" data[1] "); Serial.println (data[1]);
      rememberTime=millis();
    }
     if (nunchuk_joystickY() < -20 && (millis()- rememberTime) >= onDurationS) 
    {
      data[0] = 20; //Code to Identify the data[?] = 20:
      data[1] = map(nunchuk_joystickY(), -20, -128, 40, 255); //map Motor Speed 40 to 255 PWM:
      radio.write( data, sizeof(data) );
      Serial.print ("Reverse "); Serial.print (data[0]);
      Serial.print (" data[1] "); Serial.println (data[1]);
      rememberTime=millis();
    }
    if (nunchuk_buttonC() > 0 && (millis()- rememberTime) >= onDurationB) 
    {
      Serial.print ("Top Fire Button Stop ");
      data[0] = 7; //Code to Identify the data[?] = 7:
      data[1] = 0; //Motor Speed 0 PWM:
      radio.write( data, sizeof(data) );
      Serial.print("data[0]=");Serial.print(data[0]);
      Serial.print(" data[1]=");Serial.println(data[1]);
      rememberTime=millis();
    }
    if (nunchuk_buttonZ() > 0 && (millis()- rememberTime) >= onDurationB) 
    {
      Serial.print ("Bottom Fire Button Rudder 90° ");
      data[2] = 3; //Code to Identify the data[?] = 3 Rudder 90°:
      radio.write( data, sizeof(data) );
      Serial.print("data[2]=");Serial.println(data[2]);
      rememberTime=millis();
   }
  }
 }
