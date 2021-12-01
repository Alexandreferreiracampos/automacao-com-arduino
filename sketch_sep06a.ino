#include <SPI.h>
#include <String.h>
#include <Ethernet.h>
#include <EEPROM.h>


byte mac[] = {0x90, 0xA2, 0x0D, 0x84, 0X89};
IPAddress ip(192,168,0,200);
EthernetServer server(80);

int rele1 = A0;
int rele2 = A1;
int rele3 = A2;
int rele4 = A3;
int rele5 = A4;
int rele6 = A5;
int rele7 = 9;

int relea = 8;
int releb = 7;
int relec = 6;
int reled = 5;
 

String readString = String(30);

String statusrele;
byte esrele1;
byte esrele2;
byte esrele3;
byte esrele4;
byte esrele5;
byte esrele6;
byte esrele7;

void setup()
{
 
  
  esrele1 = EEPROM.read(0);
  esrele2 = EEPROM.read(1);
  esrele3 = EEPROM.read(2);
  esrele4 = EEPROM.read(3);
  esrele5 = EEPROM.read(4);
  esrele6 = EEPROM.read(5);
  esrele7 = EEPROM.read(6);
  
  Serial.begin(9600);
  
  Ethernet.begin(mac, ip);
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);
  pinMode(rele3, OUTPUT);
  pinMode(rele4, OUTPUT);
  pinMode(rele5, OUTPUT);
  pinMode(rele6, OUTPUT);
  pinMode(rele7, OUTPUT);
  pinMode(relea, OUTPUT);
  pinMode(releb, OUTPUT);
  pinMode(relec, OUTPUT);
  pinMode(reled, OUTPUT);

  digitalWrite(rele1, esrele1);
  
  digitalWrite(rele2, esrele2);
  digitalWrite(rele3, esrele3);
  digitalWrite(rele4, esrele4);
  digitalWrite(rele5, esrele5);
  digitalWrite(rele6, esrele6);
  digitalWrite(rele7, esrele7);
  digitalWrite(relea, LOW);
  digitalWrite(releb, LOW);
  digitalWrite(relec, LOW);
  digitalWrite(reled, LOW);

  }
  


  

 void loop()
 {
  EthernetClient client = server.available();
  

  if(client)
  {
    while(client.connected())
    {
      if(client.available())
      {
        char c = client.read();
        if(readString.length() < 30) {
          readString += (c);
          }
         if(c == '\n')
        {

          if(readString.indexOf("rele1") >= 0) {
            digitalWrite(rele1, !digitalRead(rele1));
            esrele1 = digitalRead(rele1);
            EEPROM.write(0, esrele1);
            }
           if(readString.indexOf("rele2") >= 0) {
            digitalWrite(rele2, !digitalRead(rele2));
            esrele2 = digitalRead(rele2);
            EEPROM.write(1, esrele2);   
            }
            if(readString.indexOf("rele3") >= 0) {
            digitalWrite(rele3, !digitalRead(rele3));
            esrele3 = digitalRead(rele3);
            EEPROM.write(2, esrele3); 
            }
            if(readString.indexOf("rele4") >= 0) {
            digitalWrite(rele4, !digitalRead(rele4));
            esrele4 = digitalRead(rele4);
            EEPROM.write(3, esrele4); 
            }
            if(readString.indexOf("rele5") >= 0) {
            digitalWrite(rele5, !digitalRead(rele5));
            esrele5 = digitalRead(rele5);
            EEPROM.write(4, esrele5); 
            }
            if(readString.indexOf("rele6") >= 0) {
            digitalWrite(rele6, !digitalRead(rele6));
            esrele6 = digitalRead(rele6);
            EEPROM.write(5, esrele6); 
            }
            if(readString.indexOf("rele7") >= 0) {
            digitalWrite(rele7, HIGH);
            delay (2000);
            digitalWrite(rele7, LOW);
            }
            if(readString.indexOf("relea") >= 0) {
            digitalWrite(relea, HIGH);
            delay (2000);
            digitalWrite(relea, LOW);
            }
            if(readString.indexOf("releb") >= 0) {
            digitalWrite(releb, !digitalRead(releb));
            }
            if(readString.indexOf("relec") >= 0) {
            digitalWrite(relec, !digitalRead(relec));  
            }
            if(readString.indexOf("reled") >= 0) {
            digitalWrite(reled, !digitalRead(reled));
            }

            //enviar dados pela porta serial
            
            if(readString.indexOf("relee") >= 0) {
            Serial.write('A');
            }
            
            if(readString.indexOf("relef") >= 0) {
            Serial.write('B');
            }
            
            if(readString.indexOf("releg") >= 0) {
            Serial.write('C');
            }
            
            if(readString.indexOf("releh") >= 0) {
            Serial.write('D');
            }
            
            if(readString.indexOf("relei") >= 0) {
            Serial.write('E');
            }
            
            if(readString.indexOf("relej") >= 0) {
            Serial.write('F');
            }
            
            if(readString.indexOf("relek") >= 0) {
            Serial.write('G');
            }
            
            if(readString.indexOf("relel") >= 0) {
            Serial.write('H');
            }
            
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response 
          client.println();
          client.println("<!doctype html>");
          client.println("<html>");
          client.println("<head>");
          client.println("<title>CASA</title>");
          client.println("<meta name=\"viewport\" content=\"width=320\">");
          client.println("<meta name=\"viewport\" content=\"width=device-width\">");
          client.println("<meta charset=\"utf-8\">");
          client.println("<meta name=\"viewport\" content=\"initial-scale=1.0, user-scalable=no\">");
          client.println("</head>");
          client.println("<body>");
          client.println("<center>");
          client.println("<font size=\"5\" face=\"verdana\" color=\"green\">Smart Home</font>");
          client.println("<font size=\"3\" face=\"verdana\" color=\"red\">  </font>");
          client.println("<font size=\"5\" face=\"verdana\" color=\"blue\">Alexandre</font><br />");
          client.println("<form action=\"rele1\" method=\"get\">");
          client.println("<button type=submit style=\"width:200px;\">rele 1 - </button>");
          client.println("</form> <br />");
          client.println("</center>");
          client.println("</body>");
          client.println("</html>");

 

        readString = "";

       client.stop();

           }
      
      }
    }
  }
}
