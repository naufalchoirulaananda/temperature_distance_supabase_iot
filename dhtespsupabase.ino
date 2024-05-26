#include <DHT.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <NewPing.h>

#define DHTPIN 18
#define DHTTYPE DHT11

#define TRIG_PIN 26  // Define trigger pin for ultrasonic sensor
#define ECHO_PIN 25  // Define echo pin for ultrasonic sensor

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Supabase Configuration
String API_URL = "https://your_supabase_project_url";
String API_KEY = "your_supabase_api_key";
String TableName = "datasensor";
const int httpsPort = 443;

HTTPClient https;
WiFiClientSecure client;
DHT dht(DHTPIN, DHTTYPE);

float temperature;
float humidity;
long duration;
int distance;
float plantHeight;

void setup() {
  // HTTPS Checking Credentials
  client.setInsecure();

  // Connect WiFi
  Serial.begin(115200);
  dht.begin();
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print local IP address
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Read all sensors
    temperature = dht.readTemperature();
    humidity = dht.readHumidity();

    // Read distance using ultrasonic sensor
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);

    distance = duration * 0.034 / 2;

    plantHeight = 100.0 - distance;
    
    https.begin(client, API_URL + "/rest/v1/" + TableName);
    https.addHeader("Content-Type", "application/json");
    https.addHeader("Prefer", "return=representation");
    https.addHeader("apikey", API_KEY);
    https.addHeader("Authorization", "Bearer " + API_KEY);
    int httpCode = https.POST("{\"temperature\":" + String(temperature)+ ",\"humidity\":"+ String(humidity) + ",\"distance\":"+ String(distance) + ",\"plantHeight\":"+ String(plantHeight) +  "}" );   //Send the request
    String payload = https.getString(); 
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
    https.end();
  } else {
    Serial.println("Error in WiFi connection");
  }
  delay(60000);  // Wait 1 minute before sending the next request
}
