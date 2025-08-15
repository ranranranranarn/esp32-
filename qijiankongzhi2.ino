#include <WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

String comdata = "";
char myjson[250] = "";

// 添加网络通信控制标志
bool shouldCheckNetwork = false;
unsigned long lastNetworkCheck = 0;
const unsigned long networkCheckInterval = 5000; // 每5秒检查一次网络

int relay1 = 15;    
int relay2 = 4;  
int relay3 = 16;
int relay4 = 17;
int relay5 = 5;
int relay6 = 18;
int relay7 = 19;
int relay8 = 22;
int relay9 = 13;
int relay10 = 12;
int relay11 = 14;    
int relay12 = 27; 
int relay13 = 26;

const char *ssid = "";
const char *password = "";
const char* server_host = "";
const int server_port = ;

WiFiClient client;
String response;

// 新增：串口命令处理函数声明
void handleSerialCommand(String command);

void setup() {
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  pinMode(relay5, OUTPUT);
  pinMode(relay6, OUTPUT);
  pinMode(relay7, OUTPUT);
  pinMode(relay8, OUTPUT);
  pinMode(relay9, OUTPUT);
  pinMode(relay10, OUTPUT);
  pinMode(relay11, OUTPUT);
  pinMode(relay12, OUTPUT);
  pinMode(relay13, OUTPUT);

  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  digitalWrite(relay5, LOW);
  digitalWrite(relay6, LOW);
  digitalWrite(relay7, LOW);
  digitalWrite(relay8, LOW);
  digitalWrite(relay9, LOW);
  digitalWrite(relay10,LOW);
  digitalWrite(relay11,LOW);
  digitalWrite(relay12,LOW);
  digitalWrite(relay13,LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to the WiFi network");
  Serial.print("IPAddr: ");
  Serial.println(WiFi.localIP());
  
  // 新增：串口控制使用说明
  Serial.println("\n===== 串口控制命令格式 =====");
  Serial.println("ON<设备号>  - 打开设备，例如：ON1 打开设备1");
  Serial.println("OFF<设备号> - 关闭设备，例如：OFF2 关闭设备2");
  Serial.println("STATUS     - 查看所有设备状态");
  Serial.println("HELP       - 显示此帮助信息");
  Serial.println("设备号范围：1-13");
  Serial.println("===========================");
}

void loop() {
  // 新增：检查串口输入
  if (Serial.available() > 0) {
    String serialCommand = Serial.readStringUntil('\n');
    serialCommand.trim(); // 去除首尾空白字符
    handleSerialCommand(serialCommand); // 处理串口命令
    shouldCheckNetwork = true; // 收到串口命令后检查网络
  }

  // 定时检查网络，避免频繁连接
  unsigned long currentMillis = millis();
  if (currentMillis - lastNetworkCheck >= networkCheckInterval) {
    shouldCheckNetwork = true;
    lastNetworkCheck = currentMillis;
  }

  // 只有在需要时才执行网络通信
  if (shouldCheckNetwork) {
    // 网络通信代码
    if (!client.connected()) {
      Serial.print("Connecting to ");
      Serial.print(server_host);
      Serial.print(":");
      Serial.println(server_port);

      if (client.connect(server_host, server_port)) {
        Serial.println("Connected to server");
      } else {
        Serial.println("Connection failed");
        shouldCheckNetwork = false; // 连接失败，重置标志
        return;
      }
    }
    
    client.print("d10f1a91-6760-4fe4-810a-38b51b80e6bd");
    delay(100);

    while (client.available()) {
      comdata += char(client.read());
      delay(5);
    }
    
    shouldCheckNetwork = false; // 重置网络检查标志
  }
  
  if (comdata.length() > 0) {
    comdata.toCharArray(myjson, comdata.length() + 1);
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, myjson);

    if (error) {
      Serial.print(F("JSON解析错误: "));
      Serial.println(error.c_str());
      comdata = "";
      return;
    }

    // 读取Json数据
    int data = doc["data"];
    String command = doc["command"];
    // 根据data值控制继电器
    if (command == "@!4powerOn#%") {
      digitalWrite(relay4, HIGH);
      Serial.println("限时1已开启");
    }
    else if (command == "@!4powerOff#%") {
      digitalWrite(relay4, LOW);
      Serial.println("限时1已关闭");
    }
    switch (data) {
      case 1:
        digitalWrite(relay1, HIGH);  
        Serial.println("设备1已开启");
        break;
      case 2:
        digitalWrite(relay1, LOW); 
        Serial.println("设备1已关闭");
        break;
      case 3:
        digitalWrite(relay2, HIGH);  
        Serial.println("设备2已开启");
        break;
      case 4:
        digitalWrite(relay2, LOW); 
        Serial.println("设备2已关闭");
        break;
      case 5:
        digitalWrite(relay3, HIGH); 
        Serial.println("设备3已开启");
        break;
      case 6:
        digitalWrite(relay3, LOW); 
        Serial.println("设备3已关闭");
        break;
      case 7:
        digitalWrite(relay4, HIGH);  
        Serial.println("设备4已开启");
        break;
      case 8:
        digitalWrite(relay4, LOW); 
        Serial.println("设备4已关闭");
        break;
      case 9:
        digitalWrite(relay5, HIGH);  
        Serial.println("设备5已开启");
        break;
      case 10:
        digitalWrite(relay5, LOW); 
        Serial.println("设备5已关闭");
        break;
      case 11:
        digitalWrite(relay6,  HIGH); 
        Serial.println("设备6已开启");
        break;
      case 12:
        digitalWrite(relay6, LOW); 
        Serial.println("设备6已关闭");
        break;
      case 13:
        digitalWrite(relay7,  HIGH);
        Serial.println("设备7已开启");
        break;
      case 14:
        digitalWrite(relay7, LOW);
        Serial.println("设备7已关闭");
        break;
      case 15:
        digitalWrite(relay8,  HIGH); 
        Serial.println("设备8已开启");
        break;
      case 16:
        digitalWrite(relay8, LOW); 
        Serial.println("设备8已关闭");
        break;
      case 17:
        digitalWrite(relay9,  HIGH);  
        Serial.println("设备9已开启");
        break;
      case 18:
        digitalWrite(relay9, LOW);
        Serial.println("设备9已关闭");
        break;
      case 19:
        digitalWrite(relay10,  HIGH); 
        Serial.println("设备10已开启");
        break;
      case 20:
        digitalWrite(relay10, LOW);
        Serial.println("设备10已关闭");
        break;
      case 21:
        digitalWrite(relay11,  HIGH); 
        Serial.println("设备10已开启");
        break;
      case 22:
        digitalWrite(relay11, LOW);
        Serial.println("设备10已关闭");
        break;
      case 23:
        digitalWrite(relay12,  HIGH); 
        Serial.println("设备10已开启");
        break;
      case 24:
        digitalWrite(relay12, LOW);
        Serial.println("设备10已关闭");
        break;
      case 25:
        digitalWrite(relay13,  HIGH); 
        Serial.println("设备10已开启");
        break;
      case 26:
        digitalWrite(relay13, LOW);
        Serial.println("设备10已关闭");
        break;
      default:
        Serial.println("未知的指令.");
        break;
    }
    comdata = ""; // 清空字符串
  }
}

// 新增：串口命令处理函数实现
void handleSerialCommand(String command) {
  // 转换为大写以便不区分大小写
  command.toUpperCase();
  
  // 设置网络检查标志，收到命令后检查网络状态
  shouldCheckNetwork = true;
  
  // 检查帮助命令
  if (command == "HELP") {
    Serial.println("\n===== 串口控制命令格式 =====");
    Serial.println("ON<设备号>  - 打开设备，例如：ON1 打开设备1");
    Serial.println("OFF<设备号> - 关闭设备，例如：OFF2 关闭设备2");
    Serial.println("STATUS     - 查看所有设备状态");
    Serial.println("HELP       - 显示此帮助信息");
    Serial.println("设备号范围：1-13");
    Serial.println("===========================");
    return;
  }
  
  // 检查状态查询命令
  if (command == "STATUS") {
    Serial.println("\n===== 当前设备状态 =====");
    for (int i = 1; i <= 13; i++) {
      Serial.print("设备");
      Serial.print(i);
      Serial.print(": ");
      
      bool status = false;
      switch(i) {
        case 1: status = digitalRead(relay1); break;
        case 2: status = digitalRead(relay2); break;
        case 3: status = digitalRead(relay3); break;
        case 4: status = digitalRead(relay4); break;
        case 5: status = digitalRead(relay5); break;
        case 6: status = digitalRead(relay6); break;
        case 7: status = digitalRead(relay7); break;
        case 8: status = digitalRead(relay8); break;
        case 9: status = digitalRead(relay9); break;
        case 10: status = digitalRead(relay10); break;
        case 11: status = digitalRead(relay11); break;
        case 12: status = digitalRead(relay12); break;
        case 13: status = digitalRead(relay13); break;
      }
      
      Serial.println(status ? "开启" : "关闭");
    }
    Serial.println("=======================\n");
    return;
  }
  
  // 首先检查命令格式是否正确
  if (!command.startsWith("ON") && !command.startsWith("OFF")) {
    Serial.println("错误: 无效命令格式");
    Serial.println("输入 HELP 查看帮助");
    return;
  }
  
  // 解析设备编号
  int deviceNumber = 0;
  if (command.length() >= 3) { // 最短命令如ON1是3个字符
    deviceNumber = command.substring(command.startsWith("OFF") ? 3 : 2).toInt();
  }
  
  // 检查设备编号是否有效 (1-13)
  if (deviceNumber < 1 || deviceNumber > 13) {
    Serial.println("错误: 设备编号必须在1-13之间");
    Serial.println("输入 HELP 查看帮助");
    return;
  }
  
  // 获取对应的继电器引脚
  int relayPin = -1;
  switch(deviceNumber) {
    case 1: relayPin = relay1; break;
    case 2: relayPin = relay2; break;
    case 3: relayPin = relay3; break;
    case 4: relayPin = relay4; break;
    case 5: relayPin = relay5; break;
    case 6: relayPin = relay6; break;
    case 7: relayPin = relay7; break;
    case 8: relayPin = relay8; break;
    case 9: relayPin = relay9; break;
    case 10: relayPin = relay10; break;
    case 11: relayPin = relay11; break;
    case 12: relayPin = relay12; break;
    case 13: relayPin = relay13; break;
  }
  
  // 根据命令类型执行操作
  if (command.startsWith("ON")) {
    // 打开指定设备
    digitalWrite(relayPin, HIGH);
    Serial.print("设备");
    Serial.print(deviceNumber);
    Serial.println("已开启");
  } 
  else { // 此时只可能是OFF命令
    // 关闭指定设备
    digitalWrite(relayPin, LOW);
    Serial.print("设备");
    Serial.print(deviceNumber);
    Serial.println("已关闭");
  }
}
