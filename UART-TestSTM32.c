int val = 1;
void setup() {
  
  Serial1.begin(9600); //initializing UART port 2 of STM32 with 9600 baud rate
  Serial.begin(9600); //initializing UART port 1 of STM32 with 9600 baud rate

}

void loop() { //Start of the main code
  Serial.println(val); //Print val which is initialized as 1 to serial port 1
  Serial2.println(val); //Print val which is initialized as 1 to serial port 2

}
