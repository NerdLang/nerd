var WASM =
{
  name: "wasm",
  main: "wasm.cpp",
  compiler: "em++",
  out: function(_name)
  {
		if(CLI.cli["--target"])
		{
			if(CLI.cli["--target"].argument == "js")  return _name + ".asm.js";
			else if(CLI.cli["--target"].argument == "wasm") return _name + ".wasm";
			else if(CLI.cli["--target"].argument == "html") return _name + ".html";
			else 
			{
				console.log("[!] Invalid target, expected js, wasm, html");
				process.exit(1);
			}
		}
	    return _name + ".wasm";
  },
  cli: function(compiler, preset, out, _in, option)
  {
	  /*
	  var _cachePath = path.join(process.cwd(), "..", "cached_" + COMPILER.ENV.name + "_" + VERSION);
	  var _precompiled = path.join(_cachePath, "nerd.o");		
		
	  if(!fs.existsSync(_precompiled))
	  {
	    console.log(`[+] Creating Nerd binary lib for ${COMPILER.ENV.name + "_" + VERSION}`);
		try { fs.mkdirSync(_cachePath); } catch(e){};
		execSync(`${compiler} -std=c++17 -c nerd.cpp -O3 -o "${_precompiled}"`);
		console.log("[+] Compiling with precompiled Nerd lib");
	  }
	  */
	  var _cliOption = "";
	  if(CLI.cli["--option"]) _cliOption = CLI.cli["--option"].argument;
		
		if(preset == "none")
		{
			return `${compiler} nerdcore/src/nerd.cpp -D__NJS_REGISTER_SIZE=${COMPILER.REGISTER} ${_in} -O1 -w -s TOTAL_MEMORY=33554432 ${COMPILER.LIBS} -o ${out} ${_cliOption}`;
		}
		else if(preset == "size")
		{
			return `${compiler} nerdcore/src/nerd.cpp -D__NJS_REGISTER_SIZE=${COMPILER.REGISTER} ${_in} -Os -fno-rtti -fno-stack-protector -fomit-frame-pointer -w -s TOTAL_MEMORY=33554432 ${COMPILER.LIBS} -o ${out} ${_cliOption}`;
		}
		else
		{
			return `${compiler} nerdcore/src/nerd.cpp -D__NJS_REGISTER_SIZE=${COMPILER.REGISTER} ${_in} -O3 -w -s TOTAL_MEMORY=33554432 ${COMPILER.LIBS} -o ${out} ${_cliOption}`;
		}
  }
}

module.exports = WASM;
