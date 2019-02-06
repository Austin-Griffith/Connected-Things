/*
 Austin Griffith 
 Lab 1 & 2 Ardunio Code 
 
  Transmit data pin is set up on pin 12
*/

// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>

// Include dependant SPI Library 
#include <SPI.h> 

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

// Define Variables

int analogIn;    // stores input values
int digitalIn;

int aPin = A0;
int dPin = 2;


//VARIABLES 
String str_analogIn;
String str_digitalIn ;
String str_out ;


void setup()
{
    // Initialize ASK Object
    rf_driver.init();

    pinMode(2, INPUT_PULLUP) ;
}

void loop()
{
  // a string is just a bunch of characters  --> messages
    char *msg1 = "Its Austin!";
    rf_driver.send((uint8_t *)msg1, strlen(msg1));
    rf_driver.waitPacketSent();
    delay(1000);

    char *msg2 = "Whats up!";
    rf_driver.send((uint8_t *)msg2, strlen(msg2));
    rf_driver.waitPacketSent();
    delay(1000);

    //analogRead is reading on pin A0
    //DigitalRead is reading on pin 2 
    analogIn = analogRead(aPin) ;
    digitalIn = digitalRead(dPin) ;

    if(analogIn < 1000 && analogRead > 99) {
      str_analogIn = "0" + String(analogIn) ;
    }
    else if (analogIn < 100 && analogIn > 9 ) {
      str_analogIn = "00" + String(analogIn) ;
    }
    else if (analogIn < 10 && analogIn > 9 ) {
      str_analogIn = "000" + String(analogIn) ;
    }
    else {
      str_analogIn = String(analogIn) ;
    }

    //str_analogIn = String(analogIn) ;
    
    str_digitalIn = String(digitalIn) ;

    str_out = str_analogIn + "," + str_digitalIn ;

    char *msg = str_out.c_str() ;
    rf_driver.send((uint8_t *)msg, strlen(msg)) ;
    rf_driver.waitPacketSent() ;
}
