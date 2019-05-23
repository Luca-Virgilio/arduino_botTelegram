#include "arduino_secrets.h"
#include <WiFi101.h> 
#include <SPI.h>  
#include <UniversalTelegramBot.h>
#include "bot_telegram_esp.h"

IPAddress ip(149, 132, 182, 71);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(149, 132, 2, 3);
IPAddress gateway(149, 132, 182, 1);
 
// Initialize Wifi connection to the router  
char ssid[] = SECRET_SSID;             // your network SSID (name)  
char pass[] = SECRET_PASS;            // your network key 

int status = WL_IDLE_STATUS;

void setup() {  
 Serial.begin(9600);   
 // setta la connessione wifi:  
  WiFi.config(ip, dns, gateway, subnet);
 NetworkConnection();
 printWifiStatus();
  
// bot.begin();  
}  

void loop() {  
 NetworkConnection(); 
 botMessage();
sendMessageToBot("ciao");
}  


/***************************************************************************************************************/
  
// connessione alla rete WIFI
void NetworkConnection() {
// attesa per la connessione Wifi
  while ( status != WL_CONNECTED) {
    Serial.print("In attesa di connessione a SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    // ritardo di 5 sec per permettere la connessione iniziale alla rete Wifi:
    delay(5000);
  }
}
void printWifiStatus() {
  // stampa SSID della rete Wifi
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // stampa IP della scheda Wifi dell'Arduino MKR1000
  IPAddress ip = WiFi.localIP();
  Serial.print("Indirizzo IP: ");
  Serial.println(ip);

  // stampa il valore dell'intensità del segnale Wifi
  long rssi = WiFi.RSSI();
  Serial.print("Potenza segnale (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
