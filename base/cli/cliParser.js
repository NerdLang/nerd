module.exports = parseCLI;
function parseCLI(args)
{
  var result = {error: false, msg: "", cli:{}, stack: [], useless: []};
  var useless = [0, 1];
  var withArgs = ["--target", "-o", "--preset"];
  var noArgs = ["--debug", "--build", "--run", "--check", "--verbose", "-v", "--version", "--help", "-h", "--release", "--single"];

  if(!args || !args.length)
  {
    result.error = true;
    result.msg = "Missing argument for " + args[i];
    return;
  }

  for(var i = 0; i < args.length; i++)
  {
    if( useless.indexOf(i) > -1 )
    {
     result.useless.push(args[i]);
    }
    else if( withArgs.indexOf(args[i]) > -1)
    {
      if(args[i+1])
      {
        result.cli[args[i]] =
        {
          state: true,
          argument: args[i+1],
        };
        i++;
      }
      else
      {
        result.error = true;
        result.msg = "Missing argument for " + args[i];
        break;
      }
    }
    else if(noArgs.indexOf(args[i]) > -1)
    {
      result.cli[args[i]] =
      {
        state: true,
      };
    }
    else result.stack.push(args[i]);
  }
  return result;
}
