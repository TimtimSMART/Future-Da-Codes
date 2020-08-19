#include <ESP8266WiFi.h>

WiFiServer server(88); // ประกาศสร้าง TCP Server ที่พอร์ต 88

void setup() {
  Serial.begin(115200); // เปิดใช้การ Debug ผ่าน 
  WiFi.mode(WIFI_AP_STA); // ใช้งาน WiFi ในโหมด AP
  WiFi.softAP("ARADA","123456789"); // ตั้งให้ชื่อ WiFi เป็น ESP_IOXhop
  delay(1000);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AccessPoint IP : ");
    Serial.println(IP);
//Serial.print("AccessPoint MC : ");
//    Serial.println(String(WiFi.softAPmacAddress()));
  server.begin(); // เริ่มต้นใช้ TCP Server
  server.setNoDelay(true);
  Serial.println("Server Started");
}

void loop() 
{
    WiFiClient client = server.available();  //รอรับ การเชื่อมต่อจาก Client
    if (!client) // ถ้าไม่มีการเชื่อมต่อมาใหม่
        return; // ส่งลับค่าว่าง ทำให้ลูปนี้ถูกยกเลิก
        
    Serial.println("New client"); // ส่งข้อความว่า New client ไปที่ Serial Monitor
    while (client.connected()) // วนรอบไปเรื่อย ๆ หากยังมีการเชื่อมต่ออยู่
    { 
        if (client.available())
        { // ถ้ามีการส่งข้อมูลเข้ามา
            uint16_t data = client.read();  //อ่าน Data จาก Buffer
            Serial.write(data); //แสดงผล Data ทาง Serial
        }            
    }
    client.stop(); // ปิดการเชื่อมต่อกับ Client
  Serial.println("Client disconnect"); // ส่งข้อความว่า Client disconnect ไปที่ Serial Monitor 
}
