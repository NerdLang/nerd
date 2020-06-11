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

var IOS =
{
    name: "ios",
    main: "ios.hpp",
    compiler: "clang++",
    stdlib: ["iOS", "console", "Object", "Math", "JSON" ],
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
            "iOS": false,
            "console": false,
            "module": false,
            "require": false,
            "__NJS_Log_Console": false,
            "__NJS_Object_Keys": false,
            "__NJS_Object_Stringify": false,
            "__NJS_ARGS": false,
            "__NJS_ENV": false,
            "__NJS_PLATFORM": false,
            "JSON": false,
            "Object": false,
        },
    },
    cli: function(compiler, preset, out, _in, option)
    {
        var _xcode = CONFIG.xcode;
        var _userLib = os.homedir();
        var _build = path.join(COMPILER.TMP_FOLDER, "build");
        console.dir(COMPILER.TMP_FOLDER); process.exit(0);
        var _compile = `${_xcode}/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang -x objective-c++ -target x86_64-apple-ios13.5-simulator -fmessage-length=0 -fdiagnostics-show-note-include-stack -fmacro-backtrace-limit=0 -std=gnu++11 -stdlib=libc++ -fobjc-arc -fobjc-weak -fmodules -gmodules -fmodules-cache-path=${_userLib}/Library/Developer/Xcode/DerivedData/ModuleCache.noindex -fmodules-prune-interval=86400 -fmodules-prune-after=345600 -fbuild-session-file=${_userLib}/Library/Developer/Xcode/DerivedData/ModuleCache.noindex/Session.modulevalidation -fmodules-validate-once-per-build-session -Wnon-modular-include-in-framework-module -Werror=non-modular-include-in-framework-module -Wno-trigraphs -fpascal-strings -Ofast -flto=thin -fno-common -mdynamic-no-pic -Wno-missing-field-initializers -Wno-missing-prototypes -Werror=return-type -Wdocumentation -Wunreachable-code -Wno-implicit-atomic-properties -Werror=deprecated-objc-isa-usage -Wno-objc-interface-ivars -Werror=objc-root-class -Wno-arc-repeated-use-of-weak -Wimplicit-retain-self -Wno-non-virtual-dtor -Wno-overloaded-virtual -Wno-exit-time-destructors -Wduplicate-method-match -Wno-missing-braces -Wparentheses -Wswitch -Wunused-function -Wno-unused-label -Wno-unused-parameter -Wunused-variable -Wunused-value -Wempty-body -Wuninitialized -Wconditional-uninitialized -Wno-unknown-pragmas -Wno-shadow -Wno-four-char-constants -Wno-conversion -Wconstant-conversion -Wint-conversion -Wbool-conversion -Wenum-conversion -Wno-float-conversion -Wnon-literal-null-conversion -Wobjc-literal-conversion -Wshorten-64-to-32 -Wno-newline-eof -Wno-selector -Wno-strict-selector-match -Wundeclared-selector -Wdeprecated-implementations -Wno-c++11-extensions -DNS_BLOCK_ASSERTIONS=1 -DOBJC_OLD_DISPATCH_PROTOTYPES=0 -isysroot ${_xcode}/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator13.5.sdk -fasm-blocks -fstrict-aliasing -Wprotocol -Wdeprecated-declarations -Winvalid-offsetof -g -fvisibility=hidden -Wno-sign-conversion -Winfinite-recursion -Wmove -Wcomma -Wblock-capture-autoreleasing -Wstrict-prototypes -Wrange-loop-analysis -Wno-semicolon-before-method-body -Wunguarded-availability -fobjc-abi-version=2 -fobjc-legacy-dispatch -iquote ${_build}/Intermediates.noindex/NectarIOS.build/Release-iphonesimulator/NectarIOS.build/NectarIOS-generated-files.hmap -I${_build}/Intermediates.noindex/NectarIOS.build/Release-iphonesimulator/NectarIOS.build/NectarIOS-own-target-headers.hmap -I${_build}/Intermediates.noindex/NectarIOS.build/Release-iphonesimulator/NectarIOS.build/NectarIOS-all-target-headers.hmap -iquote ${_build}/Intermediates.noindex/NectarIOS.build/Release-iphonesimulator/NectarIOS.build/NectarIOS-project-headers.hmap -I${_build}/Products/Release-iphonesimulator/include -I${_build}/Intermediates.noindex/NectarIOS.build/Release-iphonesimulator/NectarIOS.build/DerivedSources-normal/x86_64 -I${_build}/Intermediates.noindex/NectarIOS.build/Release-iphonesimulator/NectarIOS.build/DerivedSources/x86_64 -I${_build}/Intermediates.noindex/NectarIOS.build/Release-iphonesimulator/NectarIOS.build/DerivedSources -F${_build}/Products/Release-iphonesimulator -MMD -MT dependencies -MF ${_build}/Intermediates.noindex/NectarIOS.build/Release-iphonesimulator/NectarIOS.build/Objects-normal/x86_64/ViewController.d --serialize-diagnostics ${_build}/Intermediates.noindex/NectarIOS.build/Release-iphonesimulator/NectarIOS.build/Objects-normal/x86_64/ViewController.dia -c ${COMPILER.TMP_FOLDER}/NectarIOS/ViewController.mm -o ${_build}/Intermediates.noindex/NectarIOS.build/Release-iphonesimulator/NectarIOS.build/Objects-normal/x86_64/ViewController.o`;
        var _link = `${_xcode}/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++ -target x86_64-apple-ios13.5-simulator -isysroot ${_xcode}/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs/iPhoneSimulator13.5.sdk -L${_build}/Products/Release-iphonesimulator -L${_xcode}/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/include/c++/v1 -F${_build}/Products/Release-iphonesimulator -filelist ${_build}/Intermediates.noindex/NectarIOS.build/Release-iphonesimulator/NectarIOS.build/Objects-normal/x86_64/NectarIOS.LinkFileList -Xlinker -rpath -Xlinker @executable_path/Frameworks -dead_strip -Xlinker -object_path_lto -Xlinker ${_build}/Intermediates.noindex/NectarIOS.build/Release-iphonesimulator/NectarIOS.build/Objects-normal/x86_64/NectarIOS_lto.o -Xlinker -objc_abi_version -Xlinker 2 -stdlib=libc++ -fobjc-arc -fobjc-link-runtime -flto=thin -Xlinker -cache_path_lto -Xlinker ${_build}/Intermediates.noindex/LTOCache -Xlinker -sectcreate -Xlinker __TEXT -Xlinker __entitlements -Xlinker ${_build}/Intermediates.noindex/NectarIOS.build/Release-iphonesimulator/NectarIOS.build/NectarIOS.app-Simulated.xcent -framework WebKit -lc++ -Xlinker -dependency_info -Xlinker ${_build}/Intermediates.noindex/NectarIOS.build/Release-iphonesimulator/NectarIOS.build/Objects-normal/x86_64/NectarIOS_dependency_info.dat -o ${_build}/Products/Release-iphonesimulator/NectarIOS.app/NectarIOS`;
        var _sign = "/usr/bin/codesign --force --sign - --entitlements ${_build}/Intermediates.noindex/NectarIOS.build/Release-iphonesimulator/NectarIOS.build/NectarIOS.app.xcent --timestamp=none ${_build}/Products/Release-iphonesimulator/NectarIOS.app";


        return `${_compile} && ${_link}`;
    }

}

module.exports = IOS;
