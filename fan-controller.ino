/**
 * PWM modulation of a computer fan.
 *
 * Connected to pin 9.
 *
 * https://docs.arduino.cc/learn/microcontrollers/analog-output/
 *
 * ABPDRRV600MGAA5
 * |  || ||    |||
 * |  || ||    ||\- 5: 5 V DC supply.
 * |  || ||    |\- A: 10% to 90% of Vsupply (analogue), no temperature output, no sleep mode.
 * |  || ||    \- A: Analogue.
 * |  || |\- 600MG: Gauge: 0 bar to 600 mbar.
 * |  || \- V: Liquid media, silicone gel, diagnostics on.
 * |  |\- RR: Dual radial barbed ports, same side.
 * |  \- D: Dual Inline Pin (DIP)
 * \- ABP: Amplified Basic
 * 600MBAR, 5VDC
 */

#define PIN_LED 13
#define PIN_FAN 9
#define PIN_PRESSURE A0

#define PRESSURE_MAX 600

void setup()
{
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_FAN, OUTPUT);
  pinMode(PIN_PRESSURE, INPUT);

  Serial.begin(9600);
}

void loop()
{
  /*
  digitalWrite(PIN_LED, HIGH);
  analogWrite(PIN_FAN, 255);
  delay(2000);
  */

  digitalWrite(PIN_LED, LOW);
  analogWrite(PIN_FAN, 127);
  delay(200);

  // From 0-1023.
  int p_digital = analogRead(PIN_PRESSURE);

  // Convert to pressure.
  // 600MG
  //Serial.println(p_digital);
  float p_mbar = (p_digital - 102.3) * (PRESSURE_MAX / 0.8 / 1023);
  Serial.println(p_mbar);
}
