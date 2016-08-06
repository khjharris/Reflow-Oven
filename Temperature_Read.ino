/*This program reads the temperature, and time signature
of the oven using the Max6675, thermocouple, and SD library
Kenwood Harris Jr., Rev 1.0, August 5, 2016
*/

#include <RTClib.h>
#include <SD.h>
#include <Wire.h>
#include <float.h>
#include <SPI.h>
#include "max6675.h"

//Real time clock used, see RTClib.h
RTC_DS3231 rtc;

//Sets the top and bottom relay pins
#define TopElement 5
#define BottomElement 6

char masterfile = "";

//Sets the SD card chip select pin
#define SdChipselect 4

//Sets the thermocouple pins
int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

//To read thermocouple use thermocouple.readFahrenheit()

//Turns the top element on for x duration in milliseconds
void testTop(int duration) {
  int dursec = duration * 1000;

  Serial.println("Duration set for ");
  Serial.print(dursec);
  Serial.print(" seconds");

  //Handels Relay
  digitalWrite(TopElement, HIGH);
  delay(duration);
  digitalWrite(TopElement, LOW);
}

//Turns the botttom element on for x duration in milliseconds
void testBottom(int duration) {
  int dursec = duration * 1000;

  Serial.println("Duration set for ");
  Serial.print(dursec);
  Serial.print(" seconds");

  //Handels Relay
  digitalWrite(BottomElement, HIGH);
  delay(duration);
  digitalWrite(BottomElement, LOW);
}

//Turns on both the top and bottom elements for x duration in milliseconds
void testOven(int duration) {
  //Computes duration into seconds
  int dursec = duration * 1000;

  Serial.println("Duration set for ");
  Serial.print(dursec);
  Serial.print(" seconds");
  Serial.println("Both Top and Bottom Elements ON");

  //Handels Relay
  digitalWrite(TopElement, HIGH);
  digitalWrite(BottomElement, HIGH);
  delay(duration);
  digitalWrite(TopElement, LOW);
  digitalWrite(BottomElement, LOW);
}


void setup() {

  //Set up Serial Communication
  Serial.begin(9600);
  delay(3000);

  //Sets filename
  Serial.println("Please input filename of six characters");
  delay(3000);
  char filename[6];
  if (Serial.availableForWrite(0b0110)){
    Serial.readBytes(filename, 0b1111);
  }

  //Searches for Real Time clock, and prints date
  if (!rtc.begin()){
    Serial.prinln("Real time Clock not found");
  }
  Serial.println("Real Time Clock Found");
  Serial.println(now.day);
  Serial.print("/");
  Serial.print(now.month);
  Serial.print("/");
  Serial/println(now.year);

  //Initialzes SD Card, fails if card is not present
  if (SD.begin(SdChipselect)) {
    Serial.println("SD card found");
  } else {
    Serial.println("SD card not found");
    return;
  }

  //Creates file for logging
  char filstr[128];
  char *Temperature_Log = "Temperature_Log ";
  strcpy(filstr, Temperature_Log);    //Uses strcpy(buffer, string to concatenate)
  strcat(filstr, filename);   //Uses strcat(buffer, strin to concatenate), follows strcpy
  strcat(filstr, ".txt"); //
  Serial.println("Filename: ");
  Serial.print(filstr);
  SD.mkdir(filstr);   //Final filename will be Temperature_LogXXXXXX.txt
  filstr = masterfile; //Sets the file name to the masterfile name


  //Begins reading Temperature
  Serial.println("Initiating Temperature logging...");
  Serial.println("");
  Serial.println("Ambient Temperature of the Oven is ");
  Serial.print(thermocouple.readFahrenheit());
  Serial.print(" F");

  //Saves the initiol Temperature of the oven
  float preTemp = thermocouple.readFahrenheit();

  //Set up the relay pins as outputs
  pinMode(TopELement, OUTPUT);
  pinMode(BottomElement, OUTPUT);
}

void loop() {
  //String buffer for writing to SD Card
  char tempvalue = "";

  //Sets the buffer to the temperature of the Oven
  tempvalue = thermocouple.readFahrenheit();

  //Opens the masterfile, and logs temperature and time
  File temperaturefile = SD.open(masterfile, FILE_WRITE);
  if (temperaturefile){
    temperaturefile.println(tempvalue);
    temperaturefile.print(",");
    temperaturefile.print(" ");
    temperaturefile.print(now.hour);
    temperaturefile.print(":");
    temperaturefile.print(now.minute);
    temperaturefile.print(":");
    temperaturefile.print(now.second);
    temperaturefile.close();
  }

  delay(2000);



}
