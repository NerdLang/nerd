var arduino = require("arduino");

var ledPin = 11;
arduino.pinMode(ledPin, arduino.OUTPUT);
while(1)
{
	arduino.digitalWrite(ledPin, 1);
	arduino.delay(1);
	arduino.digitalWrite(ledPin, 0);
	arduino.delay(1);
}
