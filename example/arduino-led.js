var arduino = require("arduino");

var PIN_LED = LED_BUILTIN;

function setup()
{
	arduino.pinMode(PIN_LED, arduino.output); // works also with OUTPUT
}

function loop()
{
	arduino.digitalWrite(PIN_LED, HIGH);
	arduino.delay(1000);
	arduino.digitalWrite(PIN_LED, LOW);
	arduino.delay(500);
}
