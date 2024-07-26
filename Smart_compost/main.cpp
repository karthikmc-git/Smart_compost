#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Define sensor types and pins
#define DHTTYPE DHT22
#define DHTPIN 2
#define O2_PIN A0
#define PH_PIN A1
#define GAS_PIN A2
#define MOTOR_PIN 3

// Threshold values for sensor readings
#define TEMP_THRESHOLD 40.0    // Temperature threshold in °C
#define HUMIDITY_THRESHOLD 70.0 // Humidity threshold in %
#define PH_LOW_THRESHOLD 6.0    // Lower pH threshold
#define PH_HIGH_THRESHOLD 8.0   // Upper pH threshold
#define GAS_THRESHOLD 300       // Gas threshold (adjust based on sensor specs)
#define O2_THRESHOLD 300        // O2 threshold (adjust based on sensor specs)

// Sensor objects
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize DHT sensor
  dht.begin();
  
  // Set motor pin as output
  pinMode(MOTOR_PIN, OUTPUT);
}

void loop() {
  // Read sensors
  float o2 = analogRead(O2_PIN);
  float ph = analogRead(PH_PIN);
  float gas = analogRead(GAS_PIN);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Print sensor values to Serial Monitor
  Serial.print("O2: ");
  Serial.println(o2);
  Serial.print("pH: ");
  Serial.println(ph);
  Serial.print("Gas: ");
  Serial.println(gas);
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Check conditions and control motor
  if (temperature > TEMP_THRESHOLD || 
      humidity > HUMIDITY_THRESHOLD || 
      ph < PH_LOW_THRESHOLD || 
      ph > PH_HIGH_THRESHOLD || 
      gas > GAS_THRESHOLD || 
      o2 < O2_THRESHOLD) {
    digitalWrite(MOTOR_PIN, HIGH);  // Turn motor ON
    Serial.println("Motor ON");
  } else {
    digitalWrite(MOTOR_PIN, LOW);   // Turn motor OFF
    Serial.println("Motor OFF");
  }

  // Delay before next reading
  delay(2000);
}
