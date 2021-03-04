module.exports = getTips;

function getTips(target, file)
{
  switch(target)
  {
    case "wasm":
      return "";
      break;
    case "asm-js":
      return "[*] Tips : run this file with node : 'node " + file + "', or embed it in a .html page with <script src=\"" + file + "\"></script>"
      break;
    case "wast":
      return "";
      break;
    case "win-x86-32":
    case "win-x86-64":
      return "[*] Tips : on Linux, you can run this .exe with Wine : 'wine " + file + "'"
      break;
    case "linux-x86-32":
    case "linux-x86-64":
    case "linux-arm32v7":
      return "[*] Tips : on Linux, don't forget to : 'chmod +x " + file + "'."
      break;
    case "arduino-uno":
      return "[*] Tips : avrdude -p ATMEGA328P -c arduino -P [COMPORT] -b 19200 -F -U flash:w:" + file;
      break;
    case "arduino-mega1280":
      return "[*] Tips : avrdude -p m1280 -c arduino -P [COMPORT] -b 57600 -F -U flash:w:" + file;
      break;
    case "arduino-mega2560":
      return "[*] Tips : avrdude -p m2560 -c wiring -P [COMPORT] -b 115200 -F -U flash:w:" + file;
      break;
    case "nucleo-l152re":
    case "nucleo-l432kc":
      return "[*] Connect your nucleo on your computer, and symple copy/paste " + file + " on the nucleo drive"
    default:
      return "";
      break;
  }
}
