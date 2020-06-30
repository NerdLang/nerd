#include "mbed.h"

DigitalOut __NJS_STM32_led1(LED1);
DigitalOut __NJS_STM32_led2(LED2);

void __NJS_STM32_ledState(var _led, var _state)
{
  int _power = __NJS_Get_Int(_state);
  if(_power > 1) _power = 1;
  if(__NJS_Get_Int(_led) == 1)
  {
    __NJS_STM32_led1 = _power;
  }
  else if(__NJS_Get_Int(_led) == 2)
  {
    __NJS_STM32_led2 = _power;
  }
}

void __NJS_STM32_ledBlink(var _led)
{
  if(__NJS_Get_Int(_led) == 1)
  {
    __NJS_STM32_led1 = !__NJS_STM32_led1;
  }
  else if(__NJS_Get_Int(_led) == 2)
  {
    __NJS_STM32_led2 = !__NJS_STM32_led2;
  }
}
