//!_ffi_include "lib/stm32_led.h"

var STM32_LED =
{
  ledState: function(_led, _state){ __NJS_STM32_ledState(_led, _state); },
  ledBlink: function(_led){ __NJS_STM32_ledBlink(_led); }
};

module.exports = STM32_LED;
