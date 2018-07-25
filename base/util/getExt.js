module.exports = getExt;

function getExt(target)
{
  switch(target)
  {
    case "wasm":
      return ".wasm";
      break;
    case "asm-js":
      return ".asm.js";
      break;
    case "wast":
      return ".wast";
      break;
    case "win-x86-32":
    case "win-x86-64":
      return "-" + target + ".exe";
      break;
    case "mac-osw":
    case "linux-x86-32":
    case "linux-x86-64":
    case "linux-arm32v7":
      return "-" + target + ".bin";
      break;
    case "arduino-uno":
      return "-" + target + ".hex";
      break;
    case "arduino-mega1280":
      return "-" + target + ".hex";
      break;
    case "arduino-mega2560":
      return "-" + target + ".hex";
      break;
    default:
      return ".bin";
      break;
  }
}
