/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 11;    //where you connect the IR receiver, connect wire to leftmost prong
// on IR reciever goes from left to right  Data pin --> ground --> power 

IRrecv irrecv(RECV_PIN);
decode_results results;

int ledPin = 3;     //where you connect LED to pin 3

void setup()
{
  Serial.begin(9600);
  
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  
  irrecv.enableIRIn(); // Start the receiver
  
  Serial.println("Enabled IRin");

   // output to toggle on/off with receieved and decoded messages
  pinMode(ledPin, OUTPUT);
  
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    //if the button press equals the hex value 0x....
    if (results.value == 0x2BB3A279)    //power Button
    {
      //do something useful here
      Serial.println("got button 1");
      //Serial.println(brightness);
      digitalWrite(ledPin, HIGH);
      
    } else if (results.value == 0x32653C05)     //search Button
    {          
      Serial.println("got button 2");
      digitalWrite(ledPin, LOW);
    }
    
    irrecv.resume(); // Receive the next value
  }

 
  
  delay(100);
}


//HEX Values 
//
//****Power Button 
//    2BB3A279

//****Search Button 
//    32653C05

//****Menu Button 
//  DC0B4C27
