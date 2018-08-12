var led = require("stm32_led");

var i = 1;
while (true)
{
        led.ledState(1, i);
        stm32.wait(1); // stm32 is a global object in stm32 env
        i = !i;
}
