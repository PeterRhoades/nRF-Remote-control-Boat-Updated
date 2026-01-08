#include <Wire.h>
#include  <SPI.h>
#include "RF24.h"
#include "nunchuk.h"
const byte address[6] = "00092"; //rf24 Address:
const long onDurationB = 250; //Button Delay:
const long onDurationR = 100; //Rudder Delay:
const long onDurationS = 200; //Speed Delay:
long rememberTime=0;
int data[4] = {0, 0, 0, 0}; //Data Array
RF24 radio(7,8); 
//Nano pins used 7-8-11-12-13-A5-A5
void setup() 
{
Serial.begin(115200);
Serial.println("In Setup");
Wire.begin();
radio.begin();
radio.openWritingPipe(address);
radio.setPALevel(RF24_PA_HIGH); //Set power amp High to increase range
radio.setDataRate(RF24_250KBPS); //Lower data rate to increase range
nunchuk_init();
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
Serial.println("Boat Motor & Stearing NunChuk Transmitter"); 
Serial.println("Code 180920231919");
data[0] = 7;
radio.write( data, sizeof(data) ); 
data[0] = 3;
radio.write( data, sizeof(data) );
}

void loop() 
{
while (nunchuk_read()) 
{
if (nunchuk_joystickX() < -10 && (millis()- rememberTime) >= onDurationR) 
{
data[0] = 25; //Code to Identify the data[?] = 25 Nunchuk Stearing:
radio.write( data, sizeof(data) );
Serial.print(data[0]);
Serial.print("  ");
Serial.println(" Left nunChuk Sent ");
rememberTime=millis();
}
if (nunchuk_joystickX() > 10 && (millis()- rememberTime) >= onDurationR) 
{
data[0] = 30; //Code to Identify the data[?] = 30 Nunchuk Stearing:
radio.write( data, sizeof(data) );
Serial.print(data[0]);
Serial.print("  ");
Serial.println(" Right nunChuk Sent ");
rememberTime=millis();
}
if (nunchuk_joystickY() > 20 && (millis()- rememberTime) >= onDurationS) 
{
data[0] = 15; //Code to Identify the data[?] = 15:
data[1] = map(nunchuk_joystickY(), 20, 127, 40, 255); //map Motor Speed 40 upto 255 PWM:
radio.write( data, sizeof(data) );
Serial.print(data[0]);
Serial.print(" Forward = ");
Serial.print(data[1]); //Speed PWM Motor, data[1] = 0 upto 255:
Serial.println(" Sent");
rememberTime=millis();
}
if (nunchuk_joystickY() < -20 && (millis()- rememberTime) >= onDurationS) 
{
data[0] = 20; //Code to Identify the data[?] = 20:
data[1] = map(nunchuk_joystickY(), -20, -128, 40, 200); //map Motor Speed 40 to 255 PWM:
radio.write( data, sizeof(data) );
Serial.print(data[0]);
Serial.print("  Reverse ");
Serial.print(data[1]); //Speed PWM Motor, data[1] = 0 to 255:
Serial.println(" Sent");
rememberTime=millis();
}
if (nunchuk_buttonC() > 0 && (millis()- rememberTime) >= onDurationB) 
{
data[0] = 7; //Code to Identify the data[?] = 7:
data[1] = 0; //Motor Speed 0 PWM:
radio.write( data, sizeof(data) );
Serial.print(data[0]);
Serial.print("  ");
Serial.print(data[1]); //Speed PWM Motor, data[1] = 0:
Serial.print(" ");
Serial.println ("Stop Motor"); 
rememberTime=millis();
}
if (nunchuk_buttonZ() > 0 && (millis()- rememberTime) >= onDurationB) 
{
data[0] = 3; //Code to Identify the data[?] = 3 Rudder 90°:
radio.write( data, sizeof(data) );
Serial.print(data[0]);
Serial.print("  ");
Serial.print("90°");
Serial.println(" Center Stearing Received");
rememberTime=millis();
}
}
}
