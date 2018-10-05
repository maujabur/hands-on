// DHT sensor library - Version: Latest 
// https://github.com/adafruit/DHT-sensor-library
// instalar também 
// https://github.com/adafruit/Adafruit_Sensor
#include <Adafruit_Sensor.h>
#include <DHT.h>
//#include <DHT_U.h>

#define DHTPIN A1         // Pin which is connected to the DHT sensor.
// Uncomment the type of sensor in use:
#define DHTTYPE           DHT11     // DHT 11 
//#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

// biblioteca do sensor mq-7
// https://github.com/swatish17/MQ7-Library
#include "MQ7.h"
MQ7 co_sensor(A0, 5.0);

const long t_ciclo = 1000;
long ultima_vez;

const int LED_R = 9;
const int LED_G = 10;
const int LED_B = 11;
const int aceso = 60;

int estado_co, estado_ur;

void setup() {
  Serial.begin(115200);
  
  dht.begin();

  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  
  roxo();
  delay(300);
  vermelho();
  delay(300);
  laranja();
  delay(300);
  amarelo();
  delay(300);
  verde();
  delay(300);
  preto();
  delay(300);
  
  ultima_vez = millis();
}
  float minimo = 100;

void loop() {
  
  float co_ppm = co_sensor.getPPM();

  if (co_ppm < 9.0) {
    estado_co = 0;
    //verde();
  }
  else if (co_ppm < 11.0) {
    estado_co = 1;
    //amarelo();
  }
  else if (co_ppm < 13.0) {
    estado_co = 2;
    //laranja();
  }
  else if (co_ppm < 15.0) {
    estado_co = 3;
    //vermelho();
  }
  else {
    estado_co = 4;
    //roxo();
  }
  
   // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    h=101;
    //Serial.println("Failed to read from DHT sensor!");
    //return;
  }
  minimo = min(minimo,h);
  if (h >40.0) {
    estado_ur = 0;
    // verde();
  }
   else if (h > 30.0) {
    estado_ur = 1;
    //amarelo();
  }
  else if (h > 20.0) {
    estado_ur = 2;
    //laranja();
  }
  else if (h > 12.0) {
    estado_ur = 3;
    //vermelho();
  }
  else {
    estado_ur = 4;
    //roxo();
  }
 
  switch (max(estado_co,estado_ur)) {
    case 0:
      verde();
      break;
    case 1:
      amarelo();
      break;
    case 2:
      laranja();
      break;
    case 3:
      vermelho();
      break;
    case 4:
      roxo();
      break;
    default:
      preto();
      break;
  }

  Serial.print(co_ppm);
  Serial.print(", ");
  Serial.print(h);
  Serial.print(", ");
  Serial.print(minimo);
  Serial.println();

  // delay(t_ciclo);
  while (millis() - ultima_vez < t_ciclo) {
    delay(10);
  }
  ultima_vez = millis();
}


void preto() {
  analogWrite (LED_R, 0.0 * aceso);
  analogWrite (LED_G, 0.0 * aceso);
  analogWrite (LED_B, 0.0 * aceso);
}
void verde() {
  analogWrite (LED_R, 0.0 * aceso);
  analogWrite (LED_G, 1.0 * aceso);
  analogWrite (LED_B, 0.0 * aceso);
}
void amarelo() {
  analogWrite (LED_R, 0.6 * aceso);
  analogWrite (LED_G, 0.8 * aceso);
  analogWrite (LED_B, 0.0 * aceso);
}
void laranja() {
  analogWrite (LED_R, 0.9 * aceso);
  analogWrite (LED_G, 0.3 * aceso);
  analogWrite (LED_B, 0.0 * aceso);
}
void vermelho() {
  analogWrite (LED_R, 1.0 * aceso);
  analogWrite (LED_G, 0.0 * aceso);
  analogWrite (LED_B, 0.0 * aceso);
}
void roxo() {
  analogWrite (LED_R, 0.6 * aceso);
  analogWrite (LED_G, 0.0 * aceso);
  analogWrite (LED_B, 0.8 * aceso);
}
