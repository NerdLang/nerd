module.exports = Flash;

function Flash(from, to, target, verb)
{
  switch(target)
  {
    case "arduino-uno":
      execFlash(from, to, "ATMEGA328P", "arduino", "19200", verb)
      break;
    case "arduino-mega1280":
      execFlash(from, to, "m1280", "arduino", "57600", verb)
      break;
    case "arduino-mega2560":
      execFlash(from, to, "m2560", "wiring", "115200", verb)
      break;
    default:
      console.log("Nothing to do for target : " + target);
      break;
  }
}

function execFlash(from, to, model, driver, bauds, verb)
{
  var spawn = require('child_process').spawn;
  var _flash = spawn('avrdude', ['-p', model, "-c", driver, "-P", to, "-b", bauds, "-F", "-U", "flash:w:"+from]);

  _flash.stdout.on('data', function(data)
  {
    if(verb) process.stdout.write(data.toString());
  });

  _flash.stderr.on('data', function(data)
  {
    if(verb) process.stdout.write(data.toString());
  });

  _flash.on('close', function(code)
  {
    console.log("[+] Flashed")
  });
}
