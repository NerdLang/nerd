#include <ArduinoSTL.h>
#include <Arduino.h>

//
// Configuration Help 
//
// If you're using a serial port that's statically declared somewhere in
// Arduino (e.g. Serial1 on Leonardo)
//   1. Set ARDUINOSTL_SERIAL_DEVICE to your device
//   2. Uncomment the ARDUINOSTL_DEFAULT_CIN_COUT flag.
//
// If you're using a sofware serial port:
//   1. Set ARDUINOSTL_DEFAULT_SERIAL to NULL
//   2. Comment out ARDUINOSTL_DEFAULT_CIN_COUT
// Your sketch must contain delarations of cin and cout, and a call to
// ArduinoSTL_serial.connect().
//

#define ARDUINOSTL_DEFAULT_SERIAL Serial
#define ARDUINOSTL_DEFAULT_CIN_COUT

using namespace std; 

#ifdef ARDUINOSTL_DEFAULT_CIN_COUT
// Create cout and cin.. there doesn't seem to be a way
// to control what serial device at runtime. Grr.
namespace std
{
  ohserialstream cout(ARDUINOSTL_DEFAULT_SERIAL);
  ihserialstream cin(ARDUINOSTL_DEFAULT_SERIAL);
}
#endif // ARDUINOSTL_DEFAULT_CIN_COUT

/*
 * Implementation of printf() is highly libc dependent.
 *
 * This implementation is tested on:
 *
 *   ARDUINO_ARCH_AVR (Classic Arduinos) - Working
 *   TEENSYDUINO (ARM-based Teensy) - cin/cout work, printf doesn't
 *   ARDUINO_ARCH_* - ARMs are probably the same as above.
 */
#if defined(ARDUINO_ARCH_AVR)

ArduinoSTL_STDIO ArduinoSTL_Serial(ARDUINOSTL_DEFAULT_SERIAL);

// arduino_putchar(char, FILE*) 
//   Output a single character to the serial port. 
//   returns: 0 on success, 1 on error
//   note:
//     To maintain serial port compatibility this function
//     automatically addes a \r when it sees a \n
// 
static int arduino_putchar(char c, FILE* f) {
  Stream *uart = ArduinoSTL_Serial.getUart();
  if (c == '\n') uart->write('\r');
  return uart->write(c) == 1? 0 : 1;
}

// arduino_getchar(FILE*) 
//   Take a character from the serial port. This function
//   must block until a character is ready. 
//   returns: The character or -1 on a read error
//
static int arduino_getchar(FILE *f) {
  Stream *uart = ArduinoSTL_Serial.getUart();
  while (! uart->available()) { /* wait */ }
  return uart->read();
}

void ArduinoSTL_STDIO::connect(Stream *u) {
  if (file != NULL)
    free (file);
  uart = u;
  file = fdevopen(arduino_putchar, arduino_getchar); 
}

#else
#warning "printf() will not be functional on this platform."
#endif
