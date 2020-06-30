//!_ffi_include "lib/stm32.h"

var STM32 =
{
  wait: function(_num) { __NJS_STM32_WAIT(_num); }
};

module.exports = STM32;
