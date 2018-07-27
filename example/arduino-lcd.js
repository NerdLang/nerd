require("arduino-simple-lcd");

const msg = "Salut Mick !";

function setup()
{
  arduino_LiquidCrystal(8, 9, 4, 5, 6, 7); // set singleton for LiquidCrystal
  arduino_beginLCD(16, 2); // Begin LCD on 16 x 2 screen
  arduino_printLCD(msg);
}

function loop()
{
  arduino_setCursorLCD(0, 1); // put the cursor in left on the second line
  arduino_printLCD("T:" + arduino_seconds() + "s ->" + typeof arduino_millis()); // print number of seconds since arduino start
  arduino_delay(1000); // wait for 1 second
}
