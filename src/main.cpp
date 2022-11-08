#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>

#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#define DHTTYPE DHT11 // DHT 11
uint8_t DHTPin = 12; 
DHT dht(DHTPin, DHTTYPE); 
float Temperature;
float Humidity;
String formattedDate;
String dayStamp;
String timeStamp;
// Replace with your network credentials
const char* ssid     = "EasyBox-106509";
const char* password = "Pranamayakosha@1";
// Define CS pin for the SD card module
String dataMessage;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
void setup() {
  Serial.begin(115200);
  pinMode(DHTPin, INPUT);
  dht.begin();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  // Initialize a NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(19800);



  
}
void loop() {
    Read_TempHum();
    getTimeStamp();
    delay(1000); 
}


// Function to get temperature
void Read_TempHum()
{
  Temperature = dht.readTemperature(); 
  Humidity = dht.readHumidity(); 
  Serial.print("Temperature = ");
  Serial.println(Temperature);
  Serial.print("Humidity = ");
  Serial.println(Humidity);
}



// Function to get date and time from NTPClient
void getTimeStamp() 
{
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  formattedDate = timeClient.getFormattedTime();
  Serial.println(formattedDate);
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  Serial.println(dayStamp);
  // Extract time
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
  Serial.println(timeStamp);
}