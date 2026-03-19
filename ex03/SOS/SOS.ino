#define LED_PIN 2

unsigned long prevMillis = 0;
int step = 0;      // 控制SOS步骤
int count = 0;      // 记录闪了几次

// 时间配置
const int dot = 200;    // 短亮
const int dash = 1000;   // 长亮
const int gap = 200;    // 闪之间间隔
const int letter = 500; // 字母间隔
const int endPause = 3000; // 一轮结束长停顿

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  unsigned long now = millis();

  switch (step) {

    // S: 3短
    case 0:
      if (now - prevMillis >= dot) {
        digitalWrite(LED_PIN, LOW);
        if (now - prevMillis >= dot + gap) {
          prevMillis = now;
          count++;
          if (count >= 3) {
            count = 0;
            step = 1; // 进入字母间隔
          }
        }
      } else {
        digitalWrite(LED_PIN, HIGH);
      }
      break;

    // 字母间隔
    case 1:
      digitalWrite(LED_PIN, LOW);
      if (now - prevMillis >= letter) {
        prevMillis = now;
        step = 2;
      }
      break;

    // O: 3次长闪
    case 2:
      if (now - prevMillis >= dash) {
        digitalWrite(LED_PIN, LOW);
        if (now - prevMillis >= dash + gap) {
          prevMillis = now;
          count++;
          if (count >= 3) {
            count = 0;
            step = 3;
          }
        }
      } else {
        digitalWrite(LED_PIN, HIGH);
      }
      break;

    // 字母间隔
    case 3:
      digitalWrite(LED_PIN, LOW);
      if (now - prevMillis >= letter) {
        prevMillis = now;
        step = 4;
      }
      break;

    // S: 3次短闪
    case 4:
      if (now - prevMillis >= dot) {
        digitalWrite(LED_PIN, LOW);
        if (now - prevMillis >= dot + gap) {
          prevMillis = now;
          count++;
          if (count >= 3) {
            count = 0;
            step = 5; // 进入结束长停顿
          }
        }
      } else {
        digitalWrite(LED_PIN, HIGH);
      }
      break;

    // 一轮结束，长停顿
    case 5:
      digitalWrite(LED_PIN, LOW);
      if (now - prevMillis >= endPause) {
        prevMillis = now;
        step = 0; // 重新开始SOS
      }
      break;
  }
}