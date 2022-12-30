/*
	Copyright (c) 2021 NerdLang - Adrien THIERRY and contributors

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

*/
var _debug = " -g ";
var STD =
{
    name: "std",
    main: "std.cpp",
    compiler: "g++",
    stdlib: [],
    cli: function(compiler, preset, out, _in, option)
    {
		var _cachePath = path.join(process.cwd(), "..", "cached_" + COMPILER.ENV.name + "_" + os.platform + "_" + VERSION);
		var _precompiled = path.join(_cachePath, "nerd.o");

        var _stack = 0;
        if(CLI.cli["--stack"])
        {
            try 
            {
                _stack = parseInt(CLI.cli["--stack"].argument);
            }
            catch(e)
            {
                console.log("[!] Error: --stack flags required a number, received -> " + CLI.cli["--stack"].argument);
                process.exit(1);
            }
        }
		
		if(!fs.existsSync(_precompiled))
		{
			
			var _args = " -flto -Ofast ";
			if(preset == "debug")
			{
				console.log("Building core with debug");
				_args = _debug;
			}
			
			console.log(`[+] Creating Nerd binary lib for ${COMPILER.ENV.name + "_" + os.platform + "_" + VERSION}`);
			console.log(`${compiler} -std=c++17 ${_args}  -c nerdcore/src/nerd.cpp -o "${_precompiled}"`);
			try { fs.mkdirSync(_cachePath); } catch(e){};
			execSync(`${compiler} -std=c++17 ${_args}  -c nerdcore/src/nerd.cpp -o "${_precompiled}"`);
			console.log("[+] Compiling with precompiled Nerd lib");
		}
		
        if(compiler == "cl" || compiler.indexOf("cl ") == 0)
        {
			console.log("[!] cl is not supported, please use g++, clang++, em++ or avr-g++");
			process.exit(1);
        }

		var _hashmap = "";
		if(CLI.cli['--no-object-hashmap']) _hashmap = "-D__NERD__OBJECT_VECTOR";
		
        if(_stack) _stack = "-Wl,--stack," + _stack;
        else _stack = "";
        
        var _sysVNetLibs = "";
        if(os.platform() == "sunos") _sysVNetLibs = "-lsocket -lnsl";

		var _cliOption = "";
		if(CLI.cli["--option"]) _cliOption = CLI.cli["--option"].argument;
		
		
		if(CLI.cli["--profile"])
		{
			if(!CLI.cli["--conserve"]) CLI.cli["--conserve"] = true;
			if(CLI.cli["--profile"].argument == "gen")
			{
				_cliOption += " -fprofile-generate";
				console.log("[*] Profiling data will be stored in: " + COMPILER.TMP_FOLDER);
			}
			else if(CLI.cli["--profile"].argument == "use")
			{
				_cliOption += " -fprofile-use";
				console.log("[*] Using profile data from: " + COMPILER.TMP_FOLDER);
			}
			else 
			{
				console.log("[!] Please use --profile with gen or use");
			}
		}
		
		var _files = `"${_precompiled}" "${_in}"`;
		if(os.platform == "win32") _files = `"${_in}" "${_precompiled}"`;
		
        if(preset == "none")
        {
            return `${compiler} ${_stack} -std=c++17 ${_files} -g -s ${COMPILER.LIBS} -pthread -o "${out}" ${_sysVNetLibs} ${_cliOption}`;
        }
		else if(preset == "debug")
        {
			console.log(`${compiler} ${_stack} -std=c++17 ${_files} ${_debug} -s ${COMPILER.LIBS} -pthread -o "${out}" ${_sysVNetLibs} ${_cliOption}`);
            return `${compiler} ${_stack} -std=c++17 ${_files} ${_debug} -s ${COMPILER.LIBS} -pthread -o "${out}" ${_sysVNetLibs} ${_cliOption}`;
        }
        else if(preset == "size")
        {
            return `${compiler} ${_stack} -std=c++17 ${_files} -pthread -Os -fno-rtti -fno-stack-protector -fomit-frame-pointer -s ${COMPILER.LIBS} -o "${out}" ${_sysVNetLibs} ${_cliOption}`;
        }
        else
        {   
            var _opt = "-O";
            if(os.platform() == "darwin" || compiler.indexOf("clang") > -1) _opt += "3";
            else _opt += "fast";
			_opt += "  -flto";
			return `${compiler} ${_stack} -std=c++17 ${_files} ${_opt} -pthread -s ${COMPILER.LIBS}  -o "${out}" ${_sysVNetLibs} ${_cliOption}`;
        }
    },
	write: function(_content, _in)
    {
		if(CLI.cli["--profile"] && CLI.cli["--profile"].argument == "use")
		{
			return;
		}
		
        fs.writeFileSync(_in, _content);
    }

}

module.exports = STD;
