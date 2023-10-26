/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/SerialEvent
*/

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
int relay_pin = 12;

void setup() {
  // initialize serial:
  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
   pinMode(relay_pin,OUTPUT);
   digitalWrite(relay_pin,HIGH);
   delay(5000);
   Serial.println("AT\r");
   delay(500);
   Serial.println("AT+CMGF=1\r");
   delay(500);
   Serial.println("AT+CNMI=2,2,0,0,0\r");
   delay(500);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete ) {
    if(inputString.indexOf("Switch On Pump")>=0){
      digitalWrite(relay_pin,HIGH);
      Serial.write("ON: ");
      Serial.println(inputString.indexOf("Switch On Pump"));
    }
    else if(inputString.indexOf("Switch Off Pump")){
      digitalWrite(relay_pin,LOW);
      // Serial.write("Off: ");
      Serial.println(inputString.indexOf("Switch Off Pump")>=0);
    }
    //Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
