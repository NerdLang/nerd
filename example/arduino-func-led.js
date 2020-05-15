require("arduino-func");

var PIN_LED = LED_BUILTIN;

function setup()
{
	arduino_pinMode(PIN_LED, OUTPUT);
}

function loop()
{
	arduino_digitalWrite(PIN_LED, HIGH);
	arduino_delay(1000);
	arduino_digitalWrite(PIN_LED, LOW);
	arduino_delay(500);
}
