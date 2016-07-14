/* This program is a simple sketch to test the two relays for the Reflow oven,
 *  the two relays are grounded to the arduino ground pins and connected to analog pins
 *  five and four respectively. 
 *  
 *  -- June 13th 2016, Kenwood Harris Jr.
 */


#include <FileIO.h>
#include "max6675.h"

#define testpin1 A5
#define testpin2 A4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(testpin1, OUTPUT);
  pinMode(testpin2, OUTPUT);
  Serial.println("Please type 'o' or 't' to select relay");
  
}

void loop() {
  if (Serial.available() > 0){
    
    char relaynum = Serial.read();
   
    if (relaynum == 'b'){
      Serial.println("Testing relay for bottom element (Relay 1)");
      digitalWrite(testpin1, HIGH);
      delay(3000);
      digitalWrite(testpin1, LOW);
      delay(100);
    
    } else if (relaynum == 't'){
      Serial.println("Testing relay for top element (Relay 2)");
      digitalWrite(testpin2, HIGH);
      delay(3000);
      digitalWrite(testpin2, LOW);
      delay(100);
    } else {
      Serial.println("Input invalid");
    }
}
}

