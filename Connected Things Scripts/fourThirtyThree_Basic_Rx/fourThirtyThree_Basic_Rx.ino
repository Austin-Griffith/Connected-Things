/*
  Austin Griffith
  1/31/2019
  Lab 1 & 2 code
  Used to send data signals and messages from one Ardunio to another 

  Recieve data pin is set up on pin 11
*/

// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library
#include <SPI.h>

// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

String str_analogIn;
String str_digitalIn ;
String str_out ;

void setup()
{
  // Initialize ASK Object
  rf_driver.init();
  
  // Setup Serial Monitor
  Serial.begin(9600);
  Serial.println("waiting for received data of size 11 chars...");
}

void loop()
{
  // Set buffer to size of expected message
  //will hold 11 characters
  //initilizing buff to fill blank characters
  
  uint8_t buf[11] = "            ";

  uint8_t buflen = sizeof(buf);

  // Check if there is a received packet and if it is expected size
  if (rf_driver.recv(buf, &buflen))
  {
    Serial.print("len: ") ;
    Serial.println(buflen) ;
    
    // Message received with valid checksum
    Serial.print("Message Received: ");
    Serial.println((char*)buf);

    String str_out = String((char*)buf) ;

    if (str_out.substring(0,4) == "msg1") {
       Serial.println("got msg1") ;
    }

    if (str_out.substring(0,4) == "msg2") {
       Serial.println("got msg2") ;
    }

    for (int i = 0; i < str_out.length(); i++) {
      if (str_out.substring(i, i+1) == ",") {
        str_analogIn = str_out.substring(0,i);
        str_digitalIn = str_out.substring(i+1);
        break;
      }
    }

    Serial.print("analog data:") ;
    Serial.print(str_analogIn.toInt()) ;
    Serial.print(" ,  digital data: ") ;
    Serial.print(str_digitalIn.toInt()) ;
    
  }  //end of If Statement 

}   //end of void loop 
