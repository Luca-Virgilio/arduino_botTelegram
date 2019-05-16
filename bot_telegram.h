#include <UniversalTelegramBot.h>
/*****
*
* chiamare la funzione botMessage()
* definire queste variabili

const char BotToken[] = "824668381:AAEa7TmxzxDLouxR42FHUt29XUrhW5md6c4"; // Token Bot

String response;
String chat_id;
int status = WL_IDLE_STATUS;
const int Bot_mtbs = 3000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done

String startMessage="Scegliere monitoring system per accedere alla pagina web. Status permette di interagire direttamente con i sensori ";

WiFiSSLClient clientBot;  
UniversalTelegramBot bot(BotToken,clientBot);

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
