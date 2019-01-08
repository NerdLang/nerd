const PIN_LED = 10;

function setup()
{
  arduino_pinMode(PIN_LED, arduino_HIGH);
}

function loop()
{
  arduino_digitalWrite(PIN_LED, arduino_HIGH);
  arduino_delay(500);
  arduino_digitalWrite(PIN_LED, arduino_LOW);
  arduino_delay(100);
}
