
// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>


// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

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
  uint8_t buf[11];

  uint8_t buflen = sizeof(buf);

  // Check if there is a received packet and if it is expected size
  if (rf_driver.recv(buf, &buflen))
  {
    Serial.print("len: " );
    Serial.println(buflen);


    // Message received with valid checksum
    Serial.print("Message Received: ");
    Serial.println((char*)buf);

  }

}
