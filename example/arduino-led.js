var arduino = require("arduino");

var PIN_LED = 10;

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
