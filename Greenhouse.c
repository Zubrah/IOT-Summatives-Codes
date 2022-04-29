#include <DHT.h>  // Including the DHT library

##include <ESP8266WiFi.h> //Library that provides ESP8266 Wi-Fi routines to connect to the network.

 
String apiKey = "JC6OVDVENPD89SRQ";     //  Write API key from ThingSpeak

const char *ssid =  "CasaKeza";     //  wifi ssid
const char *pass =  "tapasandsangria";//wifi password
const char* server = "api.thingspeak.com";

#define DHTTYPE DHT11
#define DHTPIN 13 //datapin for the dht sensor

int soilmoisture_pin= A0;

DHT dht(DHTPIN, DHT11);

WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);
       dht.begin();
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
  
   
      float t = dht.readTemperature();
      float moisture_percentage;

      float percentage = 0.0;
      //Analog pin reading output by  soil moisture sensor
      float reading = analogRead(soilmoisture_pin);     
      percentage = (reading/1024) * 100; 
      moisture_percentage= (percentage-100) * (-1);//the percentage of moisture in the soil
      
             if (isnan(t)||isnan(h)) 
                 {   //error  message if  failed  to read  from  dht sensor
                     Serial.println("Unable to read from DHT sensor!");
                      return;
                 }
                else{
                          if (temp>27){
                            digitalWrite(RELAY_PIN, LOW);// when relay pin is low, fan turns on
                            }
                            else{
                              digitalWrite(RELAY_PIN, HIGH);// when relay pin is high, fan turns off
                              }
                          } 



                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(moisture_percentage);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print("Soil moisture(%): ");
                             Serial.print(moisture_percentage);
                             Serial.print("Soil moisture(%) : ");
                             Serial.print(reading);
                             
                            // Serial.print(" degrees Celsius,");
//                             Serial.print(h);
                             Serial.println("%. Sending values to Thingspeak.");
                             
                        }
          client.stop();
          
 
          Serial.println("Loading...");
  

  delay(15000);//15 second delay as required by thingspeak for time between updates

}
