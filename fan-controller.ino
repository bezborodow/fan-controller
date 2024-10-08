/**
 * PWM modulation of a computer fan.
 *
 * Connected to pin 9.
 *
 * https://docs.arduino.cc/learn/microcontrollers/analog-output/
 *
 * ABPDRRV600MGAA5 Honeywell Pressure Sensor
 * |  || ||    |||
 * |  || ||    ||\- 5: 5 V DC supply.
 * |  || ||    |\- A: 10% to 90% of Vsupply (analogue), no temperature output, no sleep mode.
 * |  || ||    \- A: Analogue.
 * |  || |\- 600MG: Gauge: 0 bar to 600 mbar.
 * |  || \- V: Liquid media, silicone gel, diagnostics on.
 * |  |\- RR: Dual radial barbed ports, same side.
 * |  \- D: Dual Inline Pin (DIP)
 * \- ABP: Amplified Basic
 */
#include <Adafruit_BMP085.h>

#define PIN_LED 13
#define PIN_FAN 9
#define PIN_PRESSURE A0

#define HONEYWELL_PRESSURE_MAX 600
#define PRESSURE_DIFFERENCE 20

Adafruit_BMP085 bmp;
int32_t init_pressure = 0;
int32_t set_pressure = 0;
int32_t pressure = 0;
int32_t error = 0;
int32_t integral = 0;
int32_t actuating_signal = 0;

#define K_P 5
#define K_I 0.2

void setup()
{
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_FAN, OUTPUT);
  pinMode(PIN_PRESSURE, INPUT);

  Serial.begin(9600);

  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1) {}
  }

  // Read atmosphere.
  delay(2000);
  analogWrite(PIN_FAN, 0);
  init_pressure = bmp.readPressure();
  set_pressure = init_pressure + PRESSURE_DIFFERENCE;
}

void loop()
{
  pressure = bmp.readPressure();

  error = set_pressure - pressure;
  integral += error;
  if (integral > 1500) {
    integral = 1500;
  }

  actuating_signal = K_P*error + K_I*integral;
  if (actuating_signal > 255) {
    actuating_signal = 255;
  }
  if (actuating_signal < 0) {
    actuating_signal = 0;
  }

  analogWrite(PIN_FAN, actuating_signal);
  Serial.print("Error: ");
  Serial.print(error);
  Serial.print("; integral: ");
  Serial.print(integral);
  Serial.print("; actuating signal: ");
  Serial.print(actuating_signal);
  Serial.println(".");

  delay(50);
}





  /*
   * This is for the Honeywell.
  // From 0-1023.
  digitalWrite(PIN_LED, HIGH);
  analogWrite(PIN_FAN, 255);
  digitalWrite(PIN_LED, LOW);
  delay(2000);

  int p_digital = analogRead(PIN_PRESSURE);
  // Convert to pressure.
  // 600MG
  //Serial.println(p_digital);
  float p_mbar = (p_digital - 104.3) * (HONEYWELL_PRESSURE_MAX / 0.8 / 1023);
  Serial.println(p_mbar);
  */
