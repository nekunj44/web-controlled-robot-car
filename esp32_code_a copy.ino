#include <WiFi.h>
#include <WebServer.h>

// Replace with your Wi-Fi credentials
const char* ssid = "Merc44";
const char* password = "654654654";

// Web server on port 80
WebServer server(80);

// Use UART2: TX = GPIO17, RX = GPIO16
HardwareSerial ArduinoSerial(2);

void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>ESP32 RC Car</title>
      <style>
        body {
          font-family: 'Segoe UI', sans-serif;
          text-align: center;
          background: linear-gradient(to right, #0f2027, #203a43, #2c5364);
          color: #fff;
          margin: 0;
          padding: 0;
        }

        h2 {
          margin-top: 40px;
          font-size: 2.5em;
          color: #00e0ff;
        }

        .controls {
          margin-top: 50px;
        }

        button {
          background-color: #00e0ff;
          border: none;
          border-radius: 12px;
          padding: 18px 36px;
          margin: 10px;
          font-size: 20px;
          font-weight: bold;
          color: #000;
          cursor: pointer;
          transition: transform 0.2s ease, box-shadow 0.2s ease;
        }

        button:hover {
          transform: scale(1.1);
          box-shadow: 0 8px 15px rgba(0, 224, 255, 0.4);
        }

        footer {
          margin-top: 60px;
          padding: 15px;
          font-size: 14px;
          background-color: #1a1a1a;
          color: #aaa;
        }

        footer a {
          color: #00e0ff;
          text-decoration: none;
        }
      </style>
      <script>
        function sendCommand(cmd) {
          fetch('/cmd?value=' + cmd);
        }
      </script>
    </head>
    <body>
      <h2>ESP32 RC Car Controller</h2>
      <div class="controls">
        <button onclick="sendCommand('F')">Forward</button><br>
        <button onclick="sendCommand('L')">Left</button>
        <button onclick="sendCommand('S')">Stop</button>
        <button onclick="sendCommand('R')">Right</button><br>
        <button onclick="sendCommand('B')">Backward</button>
      </div>

      <footer>
        Created by <strong>Nekunj</strong> · 
        <a href="https://github.com/nekunj44" target="_blank">GitHub: @nekunj44</a>
      </footer>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}


void setup() {
  Serial.begin(115200);
  ArduinoSerial.begin(9600, SERIAL_8N1, 16, 17);  // RX2 = GPIO16, TX2 = GPIO17

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected! IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/cmd", []() {
    if (server.hasArg("value")) {
      char c = server.arg("value")[0];
      ArduinoSerial.write(c);
      Serial.print("Command sent: ");
      Serial.println(c);
      server.send(200, "text/plain", "OK");
    } else {
      server.send(400, "text/plain", "Missing command");
    }
  });

  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  server.handleClient();
}
