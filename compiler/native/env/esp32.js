var os = require("os");

var ESP32 =
{
    name: "esp32",
    main: "esp32.cpp",
    compiler: "idf.py",
    stdlib: [],
    check: 
    {
        "env": 
        {
            "es6": true
        },
        "extends": "eslint:recommended",
        "rules": 
        {
            "strict": "global",
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
        },
    },
    cli: function(compiler, preset, out, _in, option)
    {
		var bin =  path.join(COMPILER.TMP_FOLDER, "build", "njs.bin");
        return `${compiler} build && cp ${bin} ${out}`;
    },
    out: function(_name)
    {
        return _name + ".bin";
    },
    init: function(_folder)
    {
        copyDirSync(path.join(COMPILER.MAIN_PATH, "platform", "esp32"), _folder, true);
    },
    write: function(_content)
    {
        fs.writeFileSync(path.join(COMPILER.TMP_FOLDER, "esp32.cpp"), _content);
    }

}

module.exports = ESP32;
