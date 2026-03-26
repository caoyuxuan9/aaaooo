#define TOUCH_PIN 4
#define LED_PIN   2
#define THRESHOLD 500  // 触摸阈值

// 布尔型状态变量
bool ledState = false;
// 记录上一次的触摸状态，用于边缘检测
bool lastTouch = false; 

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState); // 初始化LED状态
}

void loop() {
  // 读取原始触摸值
  int touchValue = touchRead(TOUCH_PIN);
  Serial.print("Touch: ");
  Serial.println(touchValue);

  // 将原始值转换为逻辑状态：小于阈值视为被触摸
  bool currentTouch = (touchValue < THRESHOLD);

  // 边缘检测：判断“上一次未触摸，当前被触摸的瞬间”
  if (currentTouch && !lastTouch) {
    // 翻转LED状态，实现自锁
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);

    // 软件防抖：延时屏蔽抖动
    delay(200); 
  }

  // 更新上一次状态
  lastTouch = currentTouch;
  
  delay(50);
}