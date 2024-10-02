/**
 *
 * PWM modulation of a computer fan.
 *
 * Connected to pin 9.
 *
 * https://docs.arduino.cc/learn/microcontrollers/analog-output/
 */
void setup()
{
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  digitalWrite(13, HIGH);
  analogWrite(9, 255);
  delay(20000);

  digitalWrite(13, LOW);
  analogWrite(9, 127);
  delay(20000);
}
