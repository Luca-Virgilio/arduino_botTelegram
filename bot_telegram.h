#include <UniversalTelegramBot.h>
/*****
*
* chiamare la funzione botMessage()
* definire queste variabili

const char BotToken[] = "734383558:AAE3lbrrnyJLeSrOVCB_pNIzzNxx7fm8U6I"; // Token Bot

String response;
String chat_id;
int status = WL_IDLE_STATUS;
const int Bot_mtbs = 3000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done


WiFiSSLClient clientBot;  
UniversalTelegramBot bot(BotToken,clientBot);

*
*/


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
/*********************************************************************************************/  
void sensorMessage(String chat_id, String sensor, long value){
    Serial.print("----> send value of ");
    Serial.println(sensor);  
    response=sensor;
    response.concat(": ");
    response.concat(value);
    bot.sendMessage(chat_id,response); 
    
  }