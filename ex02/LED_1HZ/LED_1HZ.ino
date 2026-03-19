// 定义板载LED引脚，避免使用"魔法数字"
#define LED_PIN 2
#define LED_PIN_CAO 26

// 记录上次LED状态翻转的时间
unsigned long previousMillis = 0;
// 闪烁间隔：500ms（1Hz = 1秒/次，高低电平各500ms）
const long interval = 500;
// 记录LED当前状态
int ledState = LOW;

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  // 初始化板载LED引脚为输出模式
  pinMode(LED_PIN, OUTPUT); 
  pinMode(LED_PIN_CAO, OUTPUT);
}

void loop() {
  Serial.println("Hello ESP32!");
  
  // 获取当前时间（毫秒）
  unsigned long currentMillis = millis();

  // 判断是否达到闪烁间隔
  if (currentMillis - previousMillis >= interval) {
    // 更新上次翻转时间
    previousMillis = currentMillis;
    // 翻转LED状态
    ledState = !ledState;
    // 设置两个LED的电平
    digitalWrite(LED_PIN, ledState);
    digitalWrite(LED_PIN_CAO, ledState);
  }
}