/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

const { platform } = require("os");
const fs = require("fs");
const dir = require("path");

module.exports = {
    name: "android",
    main: "android.cpp",
    compiler: "gradlew",
    stdlib: [{ bind: "Nectar", module: "android" }, "Object", "Math", "JSON"],
    check: {
        "env": {
            "es6": true
        },
        "extends": "eslint:recommended",
        "rules": {
            "strict": "global",
            "no-console": "off",
            "indent": "off",
            "linebreak-style": "off",
            "no-unused-vars": ["warn", {
                "vars": "all",
                "args": "after-used",
                "ignoreRestSiblings": false
            }],
			"no-const-assign": "error",
        },
        "globals": {
			"undefined": false,
			"eval": false,
            "__njs_typeof": false,
            "Nectar": false,
            "module": false,
            "require": false,
            "__NJS_Log_Console": false,
            "__NJS_Object_Keys": false,
            "__NJS_ARGS": false,
            "__NJS_Call_Function": false,
            "JSON": false,
            "Object": false,
        }
    },
    cli: function(compiler, preset, output, _input, option) {
        const prefix = platform() === "win32" ? "./" : "";
        const target = CLI.cli["--target"] ? CLI.cli["--target"].argument : "debug";
        if (target !== "release" && target !== "debug") {
            console.log("[!] Error: accepted target are: debug or release");
        }
        const apkOut = path.join(COMPILER.TMP_FOLDER, "app", "build", "outputs", "apk", target, `app-${target}-unsigned.apk`);
        return `${prefix}${compiler} build && cp ${apkOut} ${output}`;
    },
    out: name => `${name}.apk`,
    init: dir => copyDirSync(path.join(COMPILER.MAIN_PATH, "platform", "android"), dir, true),
    prepare: function(dir) {
		const _www = path.join(path.resolve(path.dirname(COMPILER.IN)), "www");
		if(fs.existsSync(_www))
		{
			copyDirSync(_www, path.join(dir, "app", "src", "main", "assets", "raw"), true);
		}
        // var _name = path.basename(COMPILER.IN).split(".")[0];
        fs.writeFileSync(path.join(dir, "local.properties"), `ndk.dir=${CONFIG.ndk}\nsdk.dir=${CONFIG.sdk}\ngradle=build -x lint -x lintVitalRelease\n`);
        fs.writeFileSync(path.join(dir, "settings.gradle"), `rootProject.name='nectar_android_app'\ninclude ':app'\n`);
        return path.join(dir, "app", "src", "main", "cpp");
    },
    write: content => fs.writeFileSync(path.join(COMPILER.TMP_FOLDER, "app", "src", "main", "cpp", "native-lib.cpp"), content)
};
