// 定义两个LED引脚
const int ledPinA = 2;  // LED A → D2
const int ledPinB = 5;  // LED B → D5

// PWM属性
const int freq = 5000;
const int resolution = 8;

void setup() {
  Serial.begin(115200);

  // 绑定两个独立PWM通道
  ledcAttach(ledPinA, freq, resolution);
  ledcAttach(ledPinB, freq, resolution);
}

void loop() {
  // A 从 0 → 255，B 从 255 → 0
  for(int duty = 0; duty <= 255; duty++){
    ledcWrite(ledPinA, duty);
    ledcWrite(ledPinB, 255 - duty);
    delay(8);
  }

  // A 从 255 → 0，B 从 0 → 255
  for(int duty = 255; duty >= 0; duty--){
    ledcWrite(ledPinA, duty);
    ledcWrite(ledPinB, 255 - duty);
    delay(8);
  }
}