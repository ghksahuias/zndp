#include <WiFi.h>
#include <PubSubClient.h>
#include <Ticker.h>
 
const char* ssid = "醉翁之意不在酒";
const char* password = "1234567890";
const char* mqttServer = "test.ranye-iot.net";
/********************###定义###********************/
Ticker ticker;
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

int count; 
bool state;
bool mode=0;
 
/********************###程序初始化###********************/
void setup()
{
  pinMode(18, OUTPUT);

  pinMode(19, OUTPUT);

  pinMode(21, OUTPUT);

  pinMode(22, OUTPUT);

  pinMode(23, OUTPUT);

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  
  // 连接WiFi
  connectWifi();
  
  // 设置MQTT服务器和端口号
  mqttClient.setServer(mqttServer, 1883);
    // 设置MQTT订阅回调函数
  mqttClient.setCallback(receiveCallback);
 
  // 连接MQTT服务器
  connectMQTTServer();
 
  // Ticker定时对象
  ticker.attach(1, tickerCount);  
}
 
/********************###主函数###********************/
void loop()
{
if (mqttClient.connected()) { // 如果开发板成功连接服务器 
    // 保持心跳
    mqttClient.loop();
  } else {                  // 如果开发板未能成功连接服务器
    connectMQTTServer();    // 则尝试连接服务器
  }
}

void tickerCount(){
  count++;
}

void connectMQTTServer(){
  // 根据ESP8266的MAC地址生成客户端ID（避免与其它ESP8266的客户端ID重名）
  String clientId = "esp32-" + WiFi.macAddress();
 
  // 连接MQTT服务器
  if (mqttClient.connect(clientId.c_str())) { 
    Serial.println("MQTT Server Connected.");
    Serial.println("Server Address: ");
    Serial.println(mqttServer);
    Serial.println("ClientId:");
    Serial.println(clientId);
    subscribeTopic(); // 订阅指定主题
  } else {
    Serial.print("MQTT Server Connect Failed. Client State:");
    Serial.println(mqttClient.state());
    delay(3000);
  }   
}

void receiveCallback(char* topic, byte* payload, unsigned int length){
  Serial.print("Message Received [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println("");
  Serial.print("Message Length(Bytes) ");
  Serial.println(length);
  if ((char)payload[0] == '5')
  mode = 0;
  if ((char)payload[0] == '6')
  mode = 1;
  if(mode == 0)
  {
    state = LOW;
    if ((char)payload[0] == '1')
  {
    if ((char)payload[1] == '1') {     // 如果收到的信息以“1”为开始
    state = HIGH;
    digitalWrite(18, state);
    digitalWrite(19, state);
    Serial.println("ON");  
    } else if((char)payload[1] == '0')  {         
      state = LOW;          
    digitalWrite(18, state);
    digitalWrite(19, state);      
    Serial.println("OFF");
   }
  }
     if ((char)payload[0] == '2')
  {
    if ((char)payload[1] == '1') {     // 如果收到的信息以“1”为开始
    state = HIGH;
    digitalWrite(21, state);
    Serial.println("ON");  
    } else if((char)payload[1] == '0')  {         
      state = LOW;     
      digitalWrite(21, state);            
    Serial.println("OFF");
   }
  }
    if ((char)payload[0] == '3')
  {
    if ((char)payload[1] == '1') {     // 如果收到的信息以“1”为开始
    state = HIGH;
    digitalWrite(22, state);
    Serial.println("ON");  
    } else if((char)payload[1] == '0')  {         
      state = LOW;          
      digitalWrite(22, state);       
    Serial.println("OFF");
   }
  }
     if ((char)payload[0] == '4')
  {
    if ((char)payload[1] == '1') {     // 如果收到的信息以“1”为开始
    state = HIGH;
    digitalWrite(23, state);
    Serial.println("ON");  
    } else if((char)payload[1] == '0')  {         
      state = LOW;     
      digitalWrite(23, state);            
    Serial.println("OFF");
   }
  }
}

if(mode == 1)
  {
    state = LOW;
    if ((char)payload[0] == '1')
  {
    if ((char)payload[1] == '2') {     // 如果收到的信息以“1”为开始
    state = HIGH;
    digitalWrite(18, state);
    digitalWrite(19, state);
    Serial.println("ON");  
    } else if((char)payload[1] == '3')  {         
      state = LOW;     
    digitalWrite(18, state);
    digitalWrite(19, state);            
    Serial.println("OFF");
   }
  }
     if ((char)payload[0] == '2')
  {
    if ((char)payload[1] == '2') {     // 如果收到的信息以“1”为开始
    state = HIGH;
    digitalWrite(21, state);
    Serial.println("ON");  
    } else if((char)payload[1] == '3')  {         
      state = LOW;    
      digitalWrite(21, state);             
    Serial.println("OFF");
   }
  }
    if ((char)payload[0] == '3')
  {
    if ((char)payload[1] == '2') {     // 如果收到的信息以“1”为开始
    state = HIGH;
    digitalWrite(22, state);
    Serial.println("ON");  
    } else if((char)payload[1] == '3')  {         
      state = LOW;     
      digitalWrite(22, state);            
    Serial.println("OFF");
   }
  }
     if ((char)payload[0] == '4')
  {
    if ((char)payload[1] == '2') {     // 如果收到的信息以“1”为开始
    state = HIGH;
    digitalWrite(23, state);
    Serial.println("ON");  
    } else if((char)payload[1] == '3')  {         
      state = LOW;    
      digitalWrite(23, state);             
    Serial.println("OFF");
   }
  }
}
}

// 订阅指定主题
void subscribeTopic(){
 
  // 建立订阅主题。主题名称以Taichi-Maker-Sub为前缀，后面添加设备的MAC地址。
  // 这么做是为确保不同设备使用同一个MQTT服务器测试消息订阅时，所订阅的主题名称不同
    String topicString1 = "Pub-Close168:B6:B3:3E:48:90";
  char subTopic1[topicString1.length() + 1];  
  strcpy(subTopic1, topicString1.c_str());
  
  String topicString2 = "Pub-Close268:B6:B3:3E:48:90";
  char subTopic2[topicString2.length() + 1];  
  strcpy(subTopic2, topicString2.c_str());

  String topicString3 = "Pub-Close368:B6:B3:3E:48:90";
  char subTopic3[topicString3.length() + 1];  
  strcpy(subTopic3, topicString3.c_str());
  
  String topicString4 = "Pub-Close468:B6:B3:3E:48:90";
  char subTopic4[topicString4.length() + 1];  
  strcpy(subTopic4, topicString4.c_str());

  String topicString5 = "Pub-StateD4:D4:DA:E4:CF:80";
  char subTopic5[topicString5.length() + 1];  
  strcpy(subTopic5, topicString5.c_str());
 /* String topicString3 = "Pub-Close368:B6:B3:3E:4F:D8";
  char subTopic2[topicString3.length() + 1];  
  strcpy(subTopic3, topicString3.c_str());

  String topicString4 = "Pub-Close468:B6:B3:3E:4F:D8";
  char subTopic2[topicString4.length() + 1];  
  strcpy(subTopic4, topicString4.c_str());*/

  // 通过串口监视器输出是否成功订阅主题以及订阅的主题名称
  if(mqttClient.subscribe(subTopic1)){
    Serial.println("Subscrib Topic:");
    Serial.println(subTopic1);
  } else {
    Serial.print("Subscribe Fail...");
  } 
  if(mqttClient.subscribe(subTopic2)){
    Serial.println("Subscrib Topic:");
    Serial.println(subTopic2);
  } else {
    Serial.print("Subscribe Fail...");
  } 
  if(mqttClient.subscribe(subTopic3)){
    Serial.println("Subscrib Topic:");
    Serial.println(subTopic3);
  } else {
    Serial.print("Subscribe Fail...");
  } 
  if(mqttClient.subscribe(subTopic4)){
    Serial.println("Subscrib Topic:");
    Serial.println(subTopic4);
  } else {
    Serial.print("Subscribe Fail...");
  } 
  if(mqttClient.subscribe(subTopic5)){
    Serial.println("Subscrib Topic:");
    Serial.println(subTopic5);
  } else {
    Serial.print("Subscribe Fail...");
  } 
 /* if(mqttClient.subscribe(subTopic3)){
    Serial.println("Subscrib Topic:");
    Serial.println(subTopic3);
  } else {
    Serial.print("Subscribe Fail...");
  } 
  if(mqttClient.subscribe(subTopic4)){
    Serial.println("Subscrib Topic:");
    Serial.println(subTopic4);
  } else {
    Serial.print("Subscribe Fail...");
  } */
}

// ESP8266连接wifi
void connectWifi(){
 
  WiFi.begin(ssid, password);
 
  //等待WiFi连接,成功连接后输出成功信息
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected!");  
  Serial.println(""); 
}