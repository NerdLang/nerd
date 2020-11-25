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

const FLAGS = {
    none: ["O1"],
    size: ["Os", "fno-rtti", "fno-stack-protector", "fomit-frame-pointer"],
    speed: ["O3"]
};

module.exports = {
    name: "std",
    main: "std.cpp",
    compiler: "g++",
    stdlib: ["console", {
        bind: "performance",
        module: "Performance"
    }, "RegExp", "Number", "Object", "Math", "JSON", "Array", "Date"],
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
            "JSON": false,
            "Object": false,
            "isNaN": false,
            "Array": false,
        },
    },
    cli: function (compiler, preset, out, _in, option) {
        const cachePath = path.join(process.cwd(), "..", `cached_${COMPILER.ENV.name}_${VERSION}`);
        const precompiled = path.join(cachePath, "nectar.o");
        const stackSize = CLI.cli["--stack"] ? +CLI.cli["--stack"].argument : 0;
        if (isNaN(stackSize)) {
            console.log("[!] Error: --stack flags required a number, received -> " + CLI.cli["--stack"].argument);
            process.exit(1);
        }

        if (!fs.existsSync(_precompiled)) {
            console.log(`[+] Creating Nectar binary lib for ${COMPILER.ENV.name + "_" + VERSION}`);
            try {
                fs.mkdirSync(_cachePath);
            } catch (e) {}
            execSync(`${compiler} -std=c++17 -c nectar.cpp -Ofast -o "${_precompiled}"`);
            console.log("[+] Compiling with precompiled Nectar lib");
        }

        if (compiler == "cl" || compiler.indexOf("cl ") == 0) {
            console.log("[!] cl is not supported, please use g++, clang++, em++ or avr-g++");
            process.exit(1);
        }

        const _hashmap = CLI.cli['--no-object-hashmap'] ? "" : "-D__NJS__OBJECT_HASHMAP";
        const _stack = stackSize ? `-Wl,--stack,${stackSize}` : "";
        const _sysVNetLibs = os.platform() === "sunos" ? "-lsocket -lnsl" : "";
        const _cliOption = CLI.cli["--option"] ? CLI.cli["--option"].argument : "";

        if (CLI.cli["--profile"]) {
            const profile = CLI.cli["--profile"].argument;
            if (!CLI.cli["--conserve"]) CLI.cli["--conserve"] = true;
            if (profile === "gen") {
                _cliOption += " -fprofile-generate";
                console.log(`[*] Profiling data will be stored in: ${COMPILER.TMP_FOLDER}`);
            } else if (profile === "use") {
                _cliOption += " -fprofile-use";
                console.log(`[*] Using profile data from: ${COMPILER.TMP_FOLDER}`);
            } else {
                console.log("[!] Please use --profile with gen or use");
            }
        }

        const opt = (FLAGS[preset] || []).map(v => `-${v}`).join(" ");
        return `${compiler} ${_hashmap} ${_stack} -std=c++17 "${_in}" "${precompiled}" ${opt} -s ${COMPILER.LIBS} -o "${out}" ${_sysVNetLibs} ${_cliOption}`
    },
    write: function (content, input) {
        if (CLI.cli["--profile"] && CLI.cli["--profile"].argument == "use") return;
        fs.writeFileSync(input, content);
    }
};
