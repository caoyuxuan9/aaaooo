// 定义触摸引脚 (T0对应GPIO4)
#define TOUCH_PIN 4
// 定义LED引脚 (ESP32 DevKit板载LED通常是GPIO2)
#define LED_PIN   2
// 中断阈值（ESP32中断阈值范围0~255，数值越小越灵敏）
#define THRESHOLD 500  

// LED状态变量
bool ledState = false;

// 触摸中断服务函数 (ISR)
void touchTriggered() {
  // 翻转LED状态
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(LED_PIN, OUTPUT);
  
  // 上电自检：LED闪烁一下
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);

  // 绑定触摸中断：引脚 -> 回调函数 -> 阈值
  touchAttachInterrupt(TOUCH_PIN, touchTriggered, THRESHOLD);
}

void loop() {
  int val = touchRead(TOUCH_PIN);
  Serial.println(val);
  delay(100);
}