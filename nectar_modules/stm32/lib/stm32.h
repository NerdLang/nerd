#include "mbed.h"

void __NJS_STM32_WAIT(var _time)
{
  wait(__NJS_Get_Int(_time));
}
