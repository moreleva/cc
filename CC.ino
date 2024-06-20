
/* Librairies part */
#include <DHT.h>
#include <Wire.h>
#include "MQ7.h"

/* Macros definition */
#define SERIAL_BAUD_RATE 115200
#define DHTPIN 7
#define DHTTYPE DHT11
#define PIN_MQ2 A0

/* NanoEdgeAI defines part */
#define NEAI_MODE 0
#define SENSOR_SAMPLES 32
#define AXIS 4

/* Create instances of sensors */
DHT dht(DHTPIN, DHTTYPE);
MQ7 mq7(A1, 5.0);

/* Global variables definitions */
static uint8_t drdy = 0;
static uint16_t neai_ptr = 0;
static float neai_buffer[SENSOR_SAMPLES * AXIS] = {0.0};
static float mq2_value;
static float humidity = 0.0;

/* NEAI library variables */
static uint8_t neai_code = 0, similarity = 0;
static uint16_t neai_cnt = 0;

/* Initialization function */
void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  dht.begin();
  pinMode(PIN_MQ2, INPUT);

  pinMode(SCL, OUTPUT);
  for (uint8_t i = 0; i < 20; i++) {
    digitalWrite(SCL, !digitalRead(SCL));
    delay(1);
  }
  delay(100);

  /* Initalize NanoEdgeAI AI */
  /*neai_code = neai_anomalydetection_init();
    if (neai_code != NEAI_OK) {
    Serial.print("Not supported board.\n");
    } */

}

/* Main function */
void loop() {
  static unsigned long lastReadTime = 0;
  if (millis() - lastReadTime >= 4000) {
    lastReadTime = millis();
    while (neai_ptr < SENSOR_SAMPLES) {
      neai_buffer[AXIS * neai_ptr] = analogRead(PIN_MQ2);
      neai_buffer[(AXIS * neai_ptr) + 1] = mq7.getPPM();
      neai_buffer[(AXIS * neai_ptr) + 2] = dht.readHumidity();
      neai_buffer[(AXIS * neai_ptr) + 3] = dht.readTemperature(); 
      neai_ptr++;
    }

    neai_ptr = 0;

    if (NEAI_MODE) {
      /*   if(neai_cnt < MINIMUM_ITERATION_CALLS_FOR_EFFICIENT_LEARNING) {
           neai_anomalydetection_learn(neai_buffer);
           Serial.print((String)"Learn: " + neai_cnt + "/" + MINIMUM_ITERATION_CALLS_FOR_EFFICIENT_LEARNING + ".\n");
           neai_cnt++;
         }
         else {
           neai_anomalydetection_detect(neai_buffer, &similarity);
           Serial.print((String)"Detect: " + similarity + "/100.\n");
         }
        }

        neai_classification(neai_buffer, output_class_buffer, &id_class);
      */
    }
    else {
      /* Print the whole buffer to the serial */
      for (uint16_t i = 0; i < AXIS * SENSOR_SAMPLES; i++) {
        Serial.print((String)neai_buffer[i] + " ");
      }
      Serial.print("\n");
    }
    memset(neai_buffer, 0.0, AXIS * SENSOR_SAMPLES * sizeof(float));
  }
}
