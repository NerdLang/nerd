require("arduino");

var ledPin = 13;
arduino.pinMode(ledPin, arduino.OUTPUT);
while(1)
{
	arduino.digitalWrite(ledPin, arduino.HIGH);
	arduino.delay(1000);
	arduino.digitalWrite(ledPin, arduino.LOW);
	arduino.delay(1000);
}
