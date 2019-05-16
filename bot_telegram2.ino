#include "arduino_secrets.h"
#include <WiFi101.h> 
#include <SPI.h>  
#include <UniversalTelegramBot.h>

IPAddress ip(149, 132, 182, 71);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(149, 132, 2, 3);
IPAddress gateway(149, 132, 182, 1);
 
// Initialize Wifi connection to the router  
char ssid[] = SECRET_SSID;             // your network SSID (name)  
char pass[] = SECRET_PASS;            // your network key 

// Initialize Telegram BOT
const char BotToken[] = "824668381:AAEa7TmxzxDLouxR42FHUt29XUrhW5md6c4"; // Token Bot



String response;
String chat_id;
int status = WL_IDLE_STATUS;
//prova1
const int Bot_mtbs = 3000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done

String startMessage="Scegliere monitoring system per accedere alla pagina web. Status permette di interagire direttamente con i sensori ";


//prova2
// manage bot message
int botScanInterval=10;
long botLastScan;
long nowMillis;


WiFiSSLClient clientBot;  
UniversalTelegramBot bot(BotToken,clientBot);
//variabili finte
long distance=1;
long light= 2;
long sound=3;
long wifi=-4;
int flame = 0;
float temperature=5;  

void setup() 
{  
 Serial.begin(9600);   
 // setta la connessione wifi:  
  WiFi.config(ip, dns, gateway, subnet);
 NetworkConnection();
 printWifiStatus();
  
// bot.begin();  

}  

void loop() 
{  
 NetworkConnection(); 
 botMessage();
}  
/********
 * 
 * 
 *
 */


/***********************************************************************************************/
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
    
    if (text == "/start") {
        String keyboardJson = "[[{ \"text\" : \"Monitoring system\", \"url\" : \"https://www.google.com\" }],[{ \"text\" : \"status\", \"callback_data\" : \"sensor\" }]]";
        bot.sendMessageWithInlineKeyboard(chat_id, startMessage, "", keyboardJson);
      }
    
    if (text == "sensor") {
         Serial.println("---new version---");
         String keyboardJson = "[[\"status\"],[\"temperature\", \"wifi\"],[\"sound\", \"flame\"],[\"distance\", \"light\"]]";
         bot.sendMessageWithReplyKeyboard(chat_id, "Status ritorna i valori di tutti i sensori. Altrimenti premere su un singolo sensore", "", keyboardJson, true);
      }

    if (text =="status"){
      statusMessage(chat_id);
      }
     else if (text=="temperature"){
     // temperatureMessage(chat_id);
     sensorMessage(chat_id, "temperature", temperature);
      }
     else if (text=="wifi"){
      //wifiMessage(chat_id);
      sensorMessage(chat_id, "wifi", wifi);
      }
     else if (text=="flame"){
      //flameMessage(chat_id);
      sensorMessage(chat_id, "flame", flame);
      }
     else if (text=="sound"){
      //soundMessage(chat_id);
      sensorMessage(chat_id, "sound", sound);
      }
     else if (text=="light"){
      //lightMessage(chat_id);
      sensorMessage(chat_id, "light", light);
      } 
     else if (text=="distance"){
     //distanceMessage(chat_id);
     sensorMessage(chat_id, "distance", distance);
      }
    }
}

void botMessage (){
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}
/******************************************************************************
 * 
 */
void statusMessage(String chat_id){
       Serial.println("send status message");
       response="Temperature: ";
       response.concat(temperature);
       response.concat("\n");
       response.concat("Wifi: ");
       response.concat(wifi);
       response.concat("\n");
       response.concat("Distance: ");
       response.concat(distance);
       response.concat("\n");
       response.concat("Flame: ");
       response.concat(flame);
       response.concat("\n");
       response.concat("Sound: ");
       response.concat(sound);
       response.concat("\n");
       response.concat("light: ");
       response.concat(light);
       response.concat("\n");
       bot.sendMessage(chat_id,response); 
  }
void sensorMessage(String chat_id, String sensor, long value){
    Serial.print("----> send value of ");
    Serial.println(sensor);  
    response=sensor;
    response.concat(": ");
    response.concat(value);
    bot.sendMessage(chat_id,response); 
    
  }
  
void temperatureMessage(String chat_id){
       Serial.println("send temperature value");
       response="Temperature: ";
       response.concat(temperature);
      
       bot.sendMessage(chat_id,response); 
  }

void wifiMessage(String chat_id){
       Serial.println("send wifi value");
       response="wifi: ";
       response.concat(wifi);
      
       bot.sendMessage(chat_id,response); 
  }

 void lightMessage(String chat_id){
       Serial.println("send light value");
       response="light: ";
       response.concat(light);
      
       bot.sendMessage(chat_id,response); 
  }
  
void soundMessage(String chat_id){
       Serial.println("send sound value");
       response="sound: ";
       response.concat(sound);
      
       bot.sendMessage(chat_id,response); 
  }
void distanceMessage(String chat_id){
       Serial.println("send distance value");
       response="distance: ";
       response.concat(distance);
      
       bot.sendMessage(chat_id,response); 
  }
void flameMessage(String chat_id){
       Serial.println("send flame value");
       response="flame: ";
       response.concat(flame);
      
       bot.sendMessage(chat_id,response); 
  }
/******************************************************************************************************************************
// prova2-non va
//check if bot received any message
void handleBotMessage(){
  nowMillis = millis();
  if(nowMillis > botLastScan + (botScanInterval*1000)){
    
    botLastScan = millis();
    
    bot.getUpdates(bot.message[0][1]);   // launch API GetUpdates up to xxx message

    // loop at messages received
    for (int i = 1; i < bot.message[0][0].toInt() + 1; i++)      {
      String message = bot.message[i][5].text; 
      handleBotCommands(message);
    }
    bot.message[0][0] = "";   // All messages have been replied - reset new messages
  }
  }


void handleBotCommands(String message) {
  //m = bot.message[line][5]; // message reiceived  

  if (message.equals("status")) 
 {  
   response="Temperature: ";
   response.concat(temperature);
   response.concat("\n");
   response.concat("Wifi: ");
   response.concat(wifi);
   response.concat("\n");
   response.concat("Distance: ");
   response.concat(distance);
   response.concat("\n");
   response.concat("Flame: ");
   response.concat(flame);
   response.concat("\n");
   response.concat("Sound: ");
   response.concat(sound);
   response.concat("\n");
   response.concat("light: ");
   response.concat(light);
   response.concat("\n");
   
   bot.sendMessage(m.chat_id,response); 

   }
}
*/
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
