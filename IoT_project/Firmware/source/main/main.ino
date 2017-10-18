/*
 *  This sketch sends a message to a TCP server
 *
 */

#include <ESP8266WiFi.h>
#include <WiFiManager.h>

unsigned long value = 0;
const char* host = "express-app.azurewebsites.net";
String url = "/api/getStatus";

void wifi_manager()
{
  WiFiManager wifiManager;
  wifiManager.autoConnect("AutoConnectAP");
}
// setup() is to intialize hardware status
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
    pinMode(D1, OUTPUT); 
    Serial.begin(115200);
    delay(10);
   
    Serial.println();
    Serial.println();
    Serial.println("Start connecting WIFI");

    wifi_manager();
    
    Serial.println("");
    Serial.print("WiFi connected: ");
    Serial.println(WiFi.SSID().c_str());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    delay(500);
}
// loop() is running as a Main()
void loop() 
{
    const int httpPort = 80;
    
    Serial.print("connecting to ");
    Serial.println(host);
    
    WiFiClient client;
    if (!client.connect(host, httpPort)) 
    {
       Serial.println("connection failed");
       return;
    }
    
    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");

    unsigned long timeout = millis();
    while (!client.available()) 
    {
      if (millis() - timeout > 1000) 
      {
        Serial.println(" Client Timeout !!!!!!");
        client.stop();
        return;
      }
    }

    while(client.available())
    {
      String line = client.readStringUntil('\n');
      if (line == "\r") 
      {
        Serial.println("==>> Header received ");
        Serial.print(line);
        break;
      }
    }
    
    timeout = millis();
    String line = client.readStringUntil('}');
    unsigned long deltaTime = millis() - timeout;
    Serial.println(deltaTime);
    Serial.print("data content: ");
    Serial.println(line);
    
    if(line.equals("{\"status\":4"))
    {
      digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
      digitalWrite(D1, LOW);
    }
    else if (line.equals("{\"status\":2"))
    {
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(D1, LOW);
    }
    else if(line.equals("{\"status\":3"))
    {
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(D1, HIGH);
    }
    else if(line.equals("{\"status\":1"))
    {
      digitalWrite(LED_BUILTIN, LOW);
      digitalWrite(D1, HIGH);
    }
    else
    {
      Serial.println("Invalid response !!!");
    }
    value++;
    Serial.println(value);
    delay(1000);
    return;
}

