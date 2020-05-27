/*
 * This file is part of NectarJS
 * Copyright (c) 2020 Adrien THIERRY
 * http://nectarjs.com - https://nectrium.com
 *
 * sources : https://github.com/nectarjs/nectarjs
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

var os = require("os");

var ANDROID =
{
    name: "android",
    main: "android.cpp",
    compiler: "gradlew",
    stdlib: ["android", "Math"],
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
            "semi": [
                "warn",
                "always"
            ],
            "no-unused-vars": ["warn", { "vars": "all", "args": "after-used", "ignoreRestSiblings": false }],
            "no-use-before-define": ["error"],
            "no-undef": "error",
            "no-redeclare": ["error", { "builtinGlobals": false }],
        },
        "globals":
        {
            "__njs_typeof": false,
            "android": false,
            "module": false,
            "require": false,
            "__NJS_Log_Console": false,
            "__NJS_ARGS": false,
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
