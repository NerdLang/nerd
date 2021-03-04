var STM32 =
{
  name: "stm32",
  main: "stm32.cpp",
  cli: function(compiler, preset, out, _in, option)
  {
    if(!COMPILER.TARGET) 
    {
      console.log("[!] Error: please specify a target with --target");
      process.exit(1);
    }
    
    var _mbosSrc = path.join(extern, "stm32", "mbed-os", "nectar");
    copyDirSync(COMPILER.TMP_FOLDER, _mbosSrc, true);

    var _profile = "SIZE";
    if(COMPILER.preset == "speed") _profile = "SPEED";

	  return `cd ${path.join(extern, "stm32")} && ${compiler} compile -m ${COMPILER.TARGET} --profile ${path.join(extern, "stm32", "profile", _profile + ".json")} -t GCC_ARM > stm32_debug_res.txt && mv ${path.join(extern, "stm32", "BUILD", COMPILER.TARGET, "GCC_ARM-" + _profile)}/stm32.bin ${out}`;
  },
  clean: function()
  {
    var _mbosSrc = path.join(extern, "stm32", "mbed-os", "nectar");
    rmdir(_mbosSrc);
  },
  compiler: "mbed",
  stdlib:[{bind: "Nectar", module: "stm32"}],
  check: {
      "env": {
          "node": true
      },
      "extends": "eslint:recommended",
      "rules": {
          "no-console": "off",
          "indent": "off",
          "linebreak-style": "off",
          "no-unused-vars": ["warn", { "vars": "all", "args": "after-used", "ignoreRestSiblings": false }],
		  "no-const-assign": "error",
      },
      "globals":
      {
		"undefined": false,
			"eval": false,
            "__njs_typeof": false,
            "console": false,
            "module": false,
            "require": false,
            "__Nectar_Log_Console": false,
			"__Nectar_InitVar": false,
            "__Nectar_Object_Keys": false,
            "__Nectar_Object_Stringify": false,
            "__Nectar_Call_Function": false,
            "__NJS_ARGS": false,
            "__NJS_ENV": false,
            "__NJS_PLATFORM": false,
			"__Nectar_typeof": false,
			"__Nectar_THIS": false,
			"__Nectar_instanceof": false,
			"__Nectar_delete": false,
			"__Nectar_EQUAL_VALUE_AND_TYPE": false,
			"__Nectar_NOT_EQUAL_VALUE_AND_TYPE": false,
            "JSON": false,
            "Object": false,
            "isNaN": false,
			"Array": false,
      }
  }
}

module.exports = STM32;
