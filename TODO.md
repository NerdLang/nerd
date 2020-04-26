* Add import

* Add babel visitors for missing

* function templates with varargs ?

* Memory cleaning for array properties and object properties

* Add Date Object

* Add RegExp Object

* Add NectarJS REPL

* Add ESLint to check syntax

// AVR: 

 avr-g++ -I ../../extern/avr/ -I ../../extern/arduino/avr/cores/arduino/  -I ../../extern/avrlib/variants/standard/ -I ../../extern/avr/include/ ../../extern/arduino/avr/cores/arduino/abi.cpp  arduino-led.cpp -w -fpermissive -DF_CPU=16000000UL -mmcu=atmega2560
 
 avr-g++ -I ../../extern/avr/ -I ../../extern/arduino/avr/cores/arduino/  -I ../../extern/avrlib/variants/standard/ -I ../../extern/avr/include/ ../../extern/arduino/avr/cores/arduino/abi.cpp  arduino-led.cpp -w -fpermissive -DF_CPU=16000000UL -mmcu=atmega2560 -std=c++14 -fno-threadsafe-statics -I ../../extern/stlport/ -ffunction-sections -fdata-sections  -fPIC -O2 -fno-rtti -fno-exceptions -fuse-cxa-atexit -std=gnu++0x  -fvisibility=hidden
 
 
 avr-g++ -I ../../extern/avr/  -I ../../extern/avrlib/variants/standard/ -I ../../extern/avr/include/ arduino-led.cpp -w -fpermissive -DF_CPU=16000000UL -mmcu=atmega2560 -std=c++14  -I ../../extern/arduino/avr/cores/arduino/ -fno-threadsafe-statics -I ../../extern/nlib/ -ffunction-sections -fdata-sections  ../../extern/arduino/avr/cores/arduino/abi.cpp -Os