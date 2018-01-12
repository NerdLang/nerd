# Flash

You can enable auto-flashing with `--flash`.

To do that, you need avrdude.

## Installing avrdude

On Debian or Ubuntu, just launch :

```
sudo apt-get update && sudo apt-get install avrdude
```

On Windows, download and install the latest version of Arduino IDE : https://www.arduino.cc/en/Main/Software

## Using --flash

The `--flash` option requires the COM port.

Windows example, with USB cable plugged on an Arduino Mega 2560 :

```
nectar --target arduino-mega2560 --flash COM0 arduino.js
```

Debian example, with USB cable plugged on an Arduino Mega 2560 :

```
nectar --target arduino-mega2560 --flash /dev/ttyACM0 arduino.js
```

You can get more information using `--verbose`
