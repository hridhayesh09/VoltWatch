#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "42-N-Resident";
const char* password = "SimplyExpertMood";
const char* serverURL = "http://172.16.22.218:5000/data";

#define ADC_PIN 34
#define SAMPLES 1000

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi Connected");
}

void loop() {
  long sum = 0;
  int maxVal = 0;
  int minVal = 4095;

  for(int i = 0; i < SAMPLES; i++) {
    int val = analogRead(ADC_PIN);
    sum += val;
    if(val > maxVal) maxVal = val;
    if(val < minVal) minVal = val;
    delayMicroseconds(100);
  }

  int average = sum / SAMPLES;
  int peakToPeak = maxVal - minVal;

  Serial.print("Peak to Peak: ");
  Serial.println(peakToPeak);
  if(peakToPeak > 200) {
  Serial.println("SURGE DETECTED!");
}
  if(WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");
    String payload = "{\"average\":" + String(average) + 
                 ",\"peak_to_peak\":" + String(peakToPeak) + 
                 ",\"surge\":" + String(peakToPeak > 200 ? 1 : 0) + "}";
    http.POST(payload);
    http.end();
  }

  delay(1000);
}