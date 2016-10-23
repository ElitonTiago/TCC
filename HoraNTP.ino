#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUDP;
 
int16_t utc = -2; //UTC -3:00 Brazil
uint32_t currentMillis = 0;
uint32_t previousMillis = 0;
 
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", utc*3600, 60000);

int initTimeNTP(){
  timeClient.begin();
  timeClient.update();
  return getHora();
}

int newHourNTP() {
  currentMillis = millis();
  if (currentMillis - previousMillis > 10000) {
    previousMillis = currentMillis; 
    timeClient.update();    
  }
  return getHora();
}

int getHora(){
  return timeClient.getHours();
}

int getMinuto(){
  return timeClient.getMinutes();
}

int getDia(){
  return timeClient.getDay();
}

