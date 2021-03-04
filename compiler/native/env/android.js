var os = require("os");

var ANDROID =
{
    name: "android",
    main: "android.cpp",
    compiler: "gradlew",
    stdlib: [{bind: "Nectar", module: "android"}, "Object", "Math", "JSON"],
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
            "JSON": false,
            "Object": false,
            "isNaN": false,
			"Array": false,
        },
    },
    cli: function(compiler, preset, out, _in, option)
    {

        var _pre = "./";
        if(os.platform() == "win32") _pre = "";
        var apkOut = "";
        
        if(CLI.cli["--target"] && CLI.cli["--target"].argument)
        {
            if(CLI.cli["--target"].argument == "release")
            {
                apkOut =  path.join(COMPILER.TMP_FOLDER, "app", "build", "outputs", "apk", "release", "app-release-unsigned.apk");
            }
            else if(CLI.cli["--target"].argument == "debug")
            {
                apkOut =  path.join(COMPILER.TMP_FOLDER, "app", "build", "outputs", "apk", "debug", "app-debug.apk");
            }
            else 
            {
                console.log("[!] Error: accepted target are: debug or release");
            }

        }
       else 
       {
        apkOut =  path.join(COMPILER.TMP_FOLDER, "app", "build", "outputs", "apk", "debug", "app-debug.apk");
       }

        return `${_pre}${compiler} build && cp ${apkOut} ${out}`;
    },
    out: function(_name)
    {
        return _name + ".apk";
    },
    init: function(_folder)
    {
        copyDirSync(path.join(COMPILER.MAIN_PATH, "platform", "android"), _folder, true);
    },
    prepare: function(_folder)
    {
		var _www = path.join(path.resolve(path.dirname(COMPILER.IN)), "www");
		if(fs.existsSync(_www))
		{
			copyDirSync(_www, path.join(_folder, "app", "src", "main", "assets", "raw"), true);
		}
        var _name = path.basename(COMPILER.IN).split(".")[0];
        fs.writeFileSync(path.join(_folder, "local.properties"), `ndk.dir=${CONFIG.ndk}\nsdk.dir=${CONFIG.sdk}\ngradle=build -x lint -x lintVitalRelease\n`);
        fs.writeFileSync(path.join(_folder, "settings.gradle"), `rootProject.name='nectar_android_app'\ninclude ':app'\n`);
        
        return path.join(_folder, "app", "src", "main", "cpp");
    },
    write: function(_content)
    {
        fs.writeFileSync(path.join(COMPILER.TMP_FOLDER, "app", "src", "main", "cpp", "native-lib.cpp"), _content);
    }

}

module.exports = ANDROID;
