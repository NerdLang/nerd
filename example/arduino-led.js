var arduino = require("arduino");

var PIN_LED = LED_BUILTIN;

function setup()
{
	arduino.pinMode(PIN_LED, arduino.output); // works also with OUTPUT
}

function loop()
{
	//HIGH = 10; // Error: HIGH is read only in package.json of arduino
	arduino.digitalWrite(PIN_LED, HIGH);
	arduino.delay(1000);
	arduino.digitalWrite(PIN_LED, LOW);
	arduino.delay(500);
}
