var arduino = require("arduino");

var ledPin = 11; // LED PIN
var low = arduino.LOW;
var high = arduino.HIGH;

arduino.pinMode(ledPin, arduino.OUTPUT); // Set pin on OUTPUT mode

while(1)
{
	arduino.digitalWrite(ledPin, high); // ON
	arduino.delay(1000);
	arduino.digitalWrite(ledPin, low); // OFF
	arduino.delay(1000);
}
