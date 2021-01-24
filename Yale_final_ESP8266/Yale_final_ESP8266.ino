#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FirebaseESP8266.h>


#include <ArduinoJson.h>

FirebaseData fbdo;
// Define the FirebaseConfig data for config data
#define FIREBASE_HOST "smartpad-19f1b-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "85wAWNNUehdrxbdclcRg20YoRKZeGDoIlp0Q1TOF"

ESP8266WebServer server;
char* ssid = "FiOS-WR4SP";
char* password = "fit2272ads953inane";

void setup()
{
  WiFi.begin(ssid,password);
  Serial.begin(9600);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Setting up Firebase...");
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  //Optional, set AP reconnection in setup()
  Firebase.reconnectWiFi(true);
  
  //Optional, set number of error retry
  Firebase.setMaxRetry(fbdo, 3);
  
  //Optional, set number of error resumable queues
  Firebase.setMaxErrorQueue(fbdo, 30);
  
  //Optional, use classic HTTP GET and POST requests. 
  //This option allows get and delete functions (PUT and DELETE HTTP requests) works for 
  //device connected behind the Firewall that allows only GET and POST requests.   
  Firebase.enableClassicRequest(fbdo, true);
  
  //Optional, set the size of BearSSL WiFi to receive and transmit buffers
  //Firebase may not support the data transfer fragmentation, you may need to reserve the buffer to match
  //the data to transport.
  fbdo.setBSSLBufferSize(1024, 1024); //minimum size is 512 bytes, maximum size is 16384 bytes
  
  //Optional, set the size of HTTP response buffer
  //Prevent out of memory for large payload but data may be truncated and can't determine its type.
  fbdo.setResponseSize(1024); //minimum size is 1024 bytes
}

void loop()
{
 handleIndex();
 delay(1000);
}

void handleIndex()
{
  // Send a JSON-formatted request with key "type" and value "request"
  // then parse the JSON-formatted response with keys "gas" and "distance"
  DynamicJsonDocument doc(1024);
  
  // Sending the request
//  doc["type"] = "request";
//  serializeJson(doc,Serial);
  // Reading the response
//  boolean messageReady = false;
  // Attempt to deserialize the JSON-formatted message
  DeserializationError error = deserializeJson(doc,Serial);
  if(error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }
  int piezovibration1 = doc["Piezovibration1"];
  FirebaseJson piez1;
  piez1.set("clotting", piezovibration1);
  if(Firebase.updateNode(fbdo, "users/edHzTjKydhTuKsQnD8159G0Lgzl2/periods/1611360000000/days/1611360000000/hourlyInstances/1611360000000/", piez1-900)){
    Serial.println("clotting updated...");
  }else{
    Serial.println(fbdo.errorReason());
  }
  int photovalue1 = doc["Photovalue1"];
  FirebaseJson phoval1;
  phoval1.set("saturation", photovalue1);
  if(Firebase.updateNode(fbdo, "users/edHzTjKydhTuKsQnD8159G0Lgzl2/periods/1611360000000/days/1611360000000/hourlyInstances/1611360000000/", phoval1)){
    Serial.println("saturation updated...");
  }else{
    Serial.println(fbdo.errorReason());
  }
  //int piezovibration2 = doc["Piezovibration2"];
  //int photovalue2 = doc["Photovalue2"];
  int RGB = doc["RGB"];
  FirebaseJson rgbval;
  rgbval.set("red", RGB);
  if(Firebase.updateNode(fbdo, "users/edHzTjKydhTuKsQnD8159G0Lgzl2/periods/1611360000000/days/1611360000000/hourlyInstances/1611360000000/color/", rgbval)){
    Serial.println("red updated...");
  }else{
    Serial.println(fbdo.errorReason());
  }
  
  // Prepare the data for serving it over HTTP
//  String output = "piezovibration1: " + String(piezovibration1) + "\n";
//  
//  output += "photovalue1: " + String(photovalue1);
//  output += "piezovibration2: " + String(piezovibration2);
//  output += "photovalue2: " + String(photovalue2);
//  output += "RGB: " + String(RGB);

  Serial.println("Updated!");
  // Serve the data as plain text, for example
//  server.send(200,"text/plain",output);
}
