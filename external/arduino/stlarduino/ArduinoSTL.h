/*---------------------
 * 
 * ArduinoSTL Core Library
 *
 * This header has some glue to make STL and Streams work from a sketch.
 * 
 */

#ifndef ARDUINOSTL_M_H
#define ARDUINOSTL_M_H

#include <serstream>

// Create cout and cin.. there doesn't seem to be a way
// to control what serial device at runtime. Grr.
namespace std
{
  extern ohserialstream cout;
  extern ihserialstream cin;
}

#if defined(ARDUINO_ARCH_AVR)

class ArduinoSTL_STDIO {
public:
  // Initialize STDIO using a pointer to whatever Serial is. 
  // Serial.begin() must be called at some point. 
  ArduinoSTL_STDIO(Stream *u) : file(NULL) {
    connect(u);
  }

  ArduinoSTL_STDIO(Stream &u) : file(NULL) {
    connect(u);
  }
  
  Stream *getUart() {
    return uart;
  }

  void connect(Stream *u);

  inline void connect(Stream &u) {
    connect(static_cast<Stream*>(&u));
  }
  
private:
  Stream *uart;
  FILE *file; 
};

extern ArduinoSTL_STDIO ArduinoSTL_Serial;

#endif // ARDUINO_ARCH_AVR

#endif // ARDUINOSTL_M_H
