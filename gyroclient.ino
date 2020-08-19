#include <ESP8266WiFi.h>
#include <Wire.h>
#include <ITG3205.h>
#include <math.h>
#include <Ticker.h>
ITG3205 itg3205;
Ticker Time;
float deltaGz;
float gz_prev=0;
float degz = 0;
float anglez = 0;
int serverport  = 88;
IPAddress server(192,168,4,1);
WiFiClient client2;
void interrupt()
{
  itg3205.itg3205ReadGyro();
  float gz=itg3205.itg3205GyroZ();
//  deltaGz = gz + gz_prev;
//  anglez = (deltaGz/2)*0.01;
//  if((fabs(gz-gz_prev)/0.01)>1)
//  {
//  degz = degz + anglez;
//  }
//  //X=(fabs(gz-gz_prev))/0.01;
//  gz_prev = gz;
//  //Serial.print(X);
//  Serial.println(degz);
    anglez=gz*0.01;
    degz = degz + anglez;
    gz_prev = gz;
    Serial.println(degz);
    client2.println(degz);
    client2.flush();
}
void setup() {
  // put your setup code here, to run once:
  Wire.begin(); 
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  if(WiFi.status() == WL_CONNECTED)
    {
      WiFi.disconnect();
      WiFi.mode(WIFI_OFF);
      delay(50);
    }
    
WiFi.mode(WIFI_STA);
WiFi.begin("ARADA","123456789");
//check connectivity
while(WiFi.status() != WL_CONNECTED)
    {
      for(int i=0; i < 10; i++)
      {
        digitalWrite(2, !HIGH);
        delay(250);
        digitalWrite(2, !LOW);
        delay(250);
        Serial.print(".");
      }
      Serial.println("");
    }

digitalWrite(2, !HIGH); //Stop Blinking To Indicate Connected 

    Serial.println("!-- Client Device Connected --!");
    Serial.print  ("Server IP Address : ");
    Serial.println(server);
    Serial.print  ("Server Port Num   : ");
    Serial.println(serverport);
  
    client2.stop();

    // If Sucessfully Connected Send Connection Message
    if(client2.connect(server, serverport))
    {
      Serial.println    ("CONNECTED");
      client2.println ("CONNECTED");
    }

  delay(100);
  itg3205.itg3205initGyro();
  delay(100);
  itg3205.itg3205CalGyro();
  delay(100);
   Time.attach(0.01,interrupt);
}

void loop() {
  // put your main code here, to run repeatedly:

}
