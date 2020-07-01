var led = require("stm32_led");

var i = 1;
while (true)
{
        led.ledState(1, i);
        Nectar.wait(1);
        i = !i;
}
