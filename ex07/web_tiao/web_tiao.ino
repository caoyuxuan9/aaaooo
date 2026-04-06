#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "cao";
const char* password = "cao666666";
const int LED_PIN = 2;

WebServer server(80);

String makePage() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>LED 亮度控制</title>
</head>
<body style="font-family:Arial; text-align:center; margin-top:50px;">
  <h1>滑动条控制 LED 亮度</h1>
  <p>当前亮度：<span id="brightness">0</span></p>
  <input type="range" min="0" max="255" value="0" id="slider" style="width:80%;">
  
  <script>
    const slider = document.getElementById('slider');
    const brightness = document.getElementById('brightness');

    slider.addEventListener('input', function() {
      let val = this.value;
      brightness.textContent = val;
      fetch('/set?val=' + val);
    });
  </script>
</body>
</html>
)rawliteral";
  return html;
}

void handleRoot() {
  server.send(200, "text/html; charset=UTF-8", makePage());
}

void handleSet() {
  if (server.hasArg("val")) {
    int value = server.arg("val").toInt();
    value = constrain(value, 0, 255);
    analogWrite(LED_PIN, value);
  }
  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  analogWrite(LED_PIN, 0);

  WiFi.begin(ssid, password);
  Serial.print("连接WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n连接成功");
  Serial.print("访问地址: http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.begin();
}

void loop() {
  server.handleClient();
}