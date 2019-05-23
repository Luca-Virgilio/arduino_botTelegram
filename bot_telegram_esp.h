#include <UniversalTelegramBot.h>
/*****
*
* chiamare la funzione botMessage()
* definire queste variabili

const char BotToken[] = "897346175:AAGiIsvCv0ONge2waxZum8ImKCEk90BWTOU"; // Token Bot

String response;
String chat_id;
int status = WL_IDLE_STATUS;
const int Bot_mtbs = 3000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done

String startMessage="Bot per health care system. Qui vengono visualizzati eventuali problemi ";

WiFiSSLClient clientBot;  
UniversalTelegramBot bot(BotToken,clientBot);

*
*/
/***********************************************************************************************/

const char BotToken[] = "897346175:AAGiIsvCv0ONge2waxZum8ImKCEk90BWTOU"; // Token Bot

String response;
String chat_id;

const int Bot_mtbs = 3000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done

String startMessage="Bot per health care system. Qui vengono visualizzati eventuali problemi ";

WiFiClientSecure clientBot;  

UniversalTelegramBot bot(BotToken,clientBot);
/***********************************************************************************************/
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;
    
    if (text == "/start") {
       bot.sendMessage(chat_id, startMessage);
      }

    else {
        bot.sendMessage(chat_id, "il bot non risponde a nessun messaggio");
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

void sendMessageToBot(String msg){
  msg.concat("\n");
  bot.sendMessage(chat_id, msg);
  }
