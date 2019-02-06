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

int analogSensorValue = 0;        // value read from the potentiometer
int digitalSensorValue ;        // value read from the digital button 
int ledBrightness ;        // needed for controlling the LED 

const int analogOutPin = 3; // Analog output pin that the LED is attached to

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
  
  //uint8_t buf[11] = "            ";

  //25 character buf size -->  25 blank characters
  uint8_t buf[25] = "                         ";

  
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
       Serial.println("msg2 has been recieved") ;
       Serial.println(" ") ;
    }

    for (int i = 0; i < str_out.length(); i++) {
      if (str_out.substring(i, i+1) == ",") {
        str_analogIn = str_out.substring(0,i);
        str_digitalIn = str_out.substring(i+1);
        break;
      }
    }

    Serial.println(" ") ;
    Serial.print("analog data:") ;
    Serial.print(str_analogIn.toInt()) ;

//    analogSensorValue = str_analogIn.toInt() ;
//    ledBrightness = map(analogSensorValue, 0, 1023, 0, 255);
    //analogWrite(analogOutPin, ledBrightness);
    
    Serial.print(" ,  digital data: ") ;
    Serial.print(str_digitalIn.toInt()) ;

    digitalSensorValue = str_digitalIn.toInt() ;

    if (str_digitalIn.toInt() == 1) {
      //ledBrightness = 500 ;

      analogSensorValue = str_analogIn.toInt() ;
      ledBrightness = map(analogSensorValue, 0, 1023, 0, 255);
      analogWrite(analogOutPin, ledBrightness) ;
      
    }else {
      ledBrightness = 0 ;
      analogWrite(analogOutPin, ledBrightness) ;
    }
    
    Serial.println(" ") ;
    
  }  //end of If Statement 

}   //end of void loop 
