

void initWifi() {
  //Configuracao Wifi
  WiFi.mode(WIFI_STA);
  char ssid[] = "ESPnetwork"; 
  char pass[] = "ESPPassword"; 
  IPAddress ip(192, 168, 1, 100);
  IPAddress gat(192, 168, 1, 1);
  IPAddress sub(255, 255, 255, 0);
  WiFi.config(ip, gat, sub);
  WiFi.begin(ssid, pass);  

   while (WiFi.status() != WL_CONNECTED) {
      delay(500);
   }
} 

