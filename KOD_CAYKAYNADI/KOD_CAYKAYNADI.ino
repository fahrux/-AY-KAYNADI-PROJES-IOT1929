
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = "Ly2vPZgABkviydB8jt0mHRjQz3lfPwEm";

char ssid[] = "TurkTelekom_T9585";
char pass[] = "EWNj2avv";

#define DHTPIN 2
#define DHTTYPE DHT11    


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}


void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  
  dht.begin();
  

  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
 
  
}
