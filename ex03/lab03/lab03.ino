// 定义两个LED引脚
const int ledPin1 = 2;  
const int ledPin2 = 5;  

// 设置PWM属性
const int freq = 5000;          // 频率 5000Hz
const int resolution = 8;       // 分辨率 8位 (0-255)

void setup() {
  Serial.begin(115200);
  ledcAttach(ledPin1, freq, resolution);
  ledcAttach(ledPin2, freq, resolution);
}

void loop() {
  // LED1变亮时LED2变暗
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    ledcWrite(ledPin1, dutyCycle);          // LED1变亮
    ledcWrite(ledPin2, 255 - dutyCycle);    // LED2变暗
    delay(5);
  }

  // LED1变暗时LED2变亮
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    ledcWrite(ledPin1, dutyCycle);          // LED1变暗
    ledcWrite(ledPin2, 255 - dutyCycle);    // LED2变亮
    delay(5);
  }
  
  Serial.println("Breathing cycle completed");
}