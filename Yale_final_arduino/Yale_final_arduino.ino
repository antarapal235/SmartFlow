
#include <ArduinoJson.h>

String message = "";
bool messageReady = false;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Monitor serial communication
//  while(Serial.available()) {
//    message = Serial.readString();
//    messageReady = true;
//  }
  // Only process message if there's one
  if(true) {
    // The only messages we'll parse will be formatted in JSON
      DynamicJsonDocument doc(1024); // ArduinoJson version 6+
//    // Attempt to deserialize the message
//    DeserializationError error = deserializeJson(doc,message);
//    if(error) {
//      Serial.print(F("deserializeJson() failed: "));
//      Serial.println(error.c_str());
//      messageReady = false;
//      return;
//    }
    if(true) {
      doc["type"] = "response";
      // Get data from analog sensors
      doc["Piezovibration1"] = analogRead(A0);
      doc["Photovalue1"] = analogRead(A1);
      doc["Piezovibration2"] = analogRead(A2);
      doc["RGB"] = analogRead(A3);
      serializeJson(doc,Serial);
    }
//    messageReady = false;
  }
}
