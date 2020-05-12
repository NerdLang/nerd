var arduino = require("arduino");

var PIN_LED = arduino.led_builtin;

function setup()
{
	 arduino.pinMode(PIN_LED, arduino.high);
}

function loop()
{
	arduino.digitalWrite(PIN_LED, arduino.high);
	arduino.delay(500);
	arduino.digitalWrite(PIN_LED, arduino.low);
	arduino.delay(100);
}
