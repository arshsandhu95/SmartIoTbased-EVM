
#include <Adafruit_Fingerprint.h> //Adafruit fingerprint library

#define mySerial Serial1 //Using UART 2 for fingerprint scanner data read
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial); //object of my serial to Serial1 

void setup()  //Setting up 
{
  Serial.begin(9600); //UART communication with raspberry pi
  pinMode(PC13, OUTPUT); //Setting the led pin of STM32 board to output
  digitalWrite(PC13, LOW); // Setting pin status to low by default
  while (!Serial);  //Checking if anything available on serial port
  delay(100); //delay 100 ms
  finger.begin(57600); //Setting the baud rate for sensor
  delay(5); //After reading holding it for sometime
  //Uncomment this to check if sensor connected properly or not
  if (finger.verifyPassword()) {
    //Serial.println("Found fingerprint sensor!");
  } else {
    //Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount(); //Read the templates stored in the sensor

}

void loop()                     // run over and over again
{
  getFingerprintID(); //Function for reading the finger data and matching it with existing templates
  delay(50);            //don't ned to run this at full speed so giving some delay of 50 ms
}

uint8_t getFingerprintID() { //Function to read finger data
  uint8_t p = finger.getImage(); //
  switch (p) {
    case FINGERPRINT_OK:
      //Image taken
      break;
    case FINGERPRINT_NOFINGER:
      //No finger detected
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Communication error
      return p;
    case FINGERPRINT_IMAGEFAIL:
      //Imaging error
      return p;
    default:
      //Unknown error
      return p;
  }



  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      //Image converted
      break;
    case FINGERPRINT_IMAGEMESS:
      //Image too messy
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      //Communication error
      return p;
    case FINGERPRINT_FEATUREFAIL:
      //Could not find fingerprint features
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      //Could not find fingerprint features
      return p;
    default:
      //Unknown error
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    //Finger found
    Serial.println("1"); //Send '1' if finger matches with teamplates stored
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    //Communication error
    Serial.println("3"); //Send 3 if finger scanner communication error
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    digitalWrite(PC13, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(2000);              // wait for a second
    digitalWrite(PC13, LOW);    // turn the LED off by making the voltage LOW
    delay(2000);              // wait for a second
    Serial.println("2"); //Send '2' on raspberry uart if wrong finger
    
    return p;
  } else {
    //Unknown error
    return p;
  }   


  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  return finger.fingerID; 
}

