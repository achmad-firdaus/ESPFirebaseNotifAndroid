//Bre semangat bre, by achmad

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "FREE1";
const char* password = "cabebawang_5";

const char* host = "http://thirtyseven-api.herokuapp.com";

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(5000);
  if (Serial.available() > 0) {
    int inByte = Serial.read();
    switch (inByte) {
      case 'a':
        POST();
        Serial.println("Type a");
        break;
      case 'b':
        Serial.println("Type b");
        GET();
    }
  }
}

void POST() {
  WiFiClient client;

  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  String postData = "U=buluburung&T=buluburungtoken";
  String address = "http://thirtyseven-api.herokuapp.com/apiv1";
  HTTPClient http;
  http.begin(address);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST(postData);
  Serial.println(httpCode);
  String payload = http.getString();
  Serial.println(payload);
  http.end();
  delay(9000);
}

void GET() {
  HTTPClient http;
  http.begin("http://thirtyseven-api.herokuapp.com/apiv1-2/buluburung/buluburungtoken");  
  int httpCode = http.GET();
  if (httpCode > 0) {
    String payload = http.getString();
    Serial.println(payload);
  }
  http.end();
  delay(9000);
}
