<p>
 
<img height="64" src="https://i.imgur.com/oXRdycNl.png">[![Tweet](https://img.shields.io/twitter/url/http/shields.io.svg?style=social)](https://twitter.com/intent/tweet?text=Compile%20JavaScript%20into%20native%20binaries%20for%20Windows,Mac,Linux,iOS,Android,Arduino%20and%20more&url=https://github.com/NectarJS/nectarjs/&via=nectarjs&hashtags=javascript,js,native,compiler,nectarjs,nectar)

<br>

Javascript's God Mode: one language to rule them all.

Code everything, everywhere, for everything, in JavaScript.

No VM. No Bytecode. No packaging. No Garbage Collector. Fully compiled to native binaries.

# Table of contents

* [What is NectarJS](#what-is-nectarjs)
* [Efficiency](#efficiency)
* [Install](#install)
* [Main objectives](#main-objectives)
* [EcmaScript Support](#ecmascript-support)
* [Using Native Compiler](#using-native-compiler)
  - [Testing Your Installation](#testing-your-installation)
  - [Windows](#windows)
  - [Linux / FreeBSD](#linux--freebsd)
  - [Apple](#apple-ios)
  - [First Compilation](#first-compilation)
* [Starting with compilation](#starting-with-compilation)
* [Using Compiler Environmants](#using-compiler-environments)
* [Android Compilation](#android-compilation)
* [iOS Compilation](#ios-compilation)
* [Arduino Compilation](#arduino-compilation)
* [STM32 Compilation](#stm32-compilation)
* [Compatibility Targets / Platforms](#compatibility-targetsplatforms)
* [Linking C/C++ librariesr](#linking-cc-libraries)
  - [Meta functions in C++ libs](#meta-functions-in-c-libs)
  - [Adding external lib and .c/.cpp files](#adding-external-lib-and-ccpp-files)
* [Optimization](#optimization)
* [Stores](#stores)
* [Actively Tested For](#actively-tested-for)



# What is NectarJS

**NectarJS** is a **JavaScript native compiler** aiming to make JavaScript universal, NectarJS is able to compile native apps for Windows, Mac, Linux, iOS, Android, Raspberry, STM32 and more.

> **NectarJS** is in active development, join us on [Discord](https://discord.gg/cpe2UuN) or [IRC](https://kiwiirc.com/client/irc.freenode.net/#nectarjs) if you need more information.

- [Roadmap on Trello](https://trello.com/invite/b/6F4rvEj2/9d7677f9dc6b5bf2f5b33e45fc794182/nectarjs)

- [Quick Start](https://nectarjs.com/docs/nectarjs/quick-start/)

- [Quick Hack](https://nectarjs.com/docs/contribute/quick-hack/)

- [NectarJS Documentation (WIP)](https://nectarjs.com/documentation/)

</p>

# Efficiency

Some benchmarks with the file example/fibo.js and differents fibos arguments:

|           | NodeJS v12.8.1 | QuickJS 2020-07-05 | NectarJS v0.6.104 |
|-----------|----------------|--------------------|-------------------|
| sort(1e6) [No preset]                                               |
| - Time:   |      0.33s     |         -          |     **0.33s**     |
| - Memory: |      7.0Mb     |         -          |     **1.0Mb**     |
|- Filesize:|     28.6Mb     |         -          |     **424Kb**     |
| sort(1e6) [+Size preset]                                            |
|- Filesize:|     28.6Mb     |         -          |     **260Kb**     |
| sort(1e6) [+Speed preset]                                           |
| - Time:   |      0.33s     |         -          |     **0.20s**     |
| matrix(256) [No preset]                                             |
| - Time:   |      0.33s     |         -          |     **0.21s**     |
| - Memory: |      7.0Mb     |         -          |     **1.0Mb**     |
|- Filesize:|     28.6Mb     |         -          |     **405Kb**     |
| matrix(256) [+Size preset]                                          |
|- Filesize:|     28.6Mb     |         -          |     **251Kb**     |
| matrix(1e6) [+Speed preset]                                         |
| - Time:   |      0.33s     |         -          |     **0.11s**     |

* _Some code can be evaluated compile-time_

# EcmaScript Support

NectarJS already supports more than 80% of ES3.


<details>
<summary>Prototype</summary>
<br>
 
* .call()

* .bind()

</details>

<details>
<summary>Array</summary>
<br>
 
* .length

* .push(value)

</details>

<details>
<summary>Class</summary>
<br>
 
* constructor

* methods

* static methods

</details>

<details>
<summary>Console</summary>
<br>
 
* .log(variadic)

</details>

<details>
<summary>JSON</summary>
<br>
 
* .parse(str)
 
* .stringify(obj)

</details>

<details>
<summary>Math</summary>
<br>
 
* [All static methods and constants]

</details>

<details>
<summary>Object</summary>
<br>
 
* .keys

</details>

<details>
<summary>performance</summary>
<br>
 
* timeOrigin

* .now()

</details>

<details>
<summary>String</summary>
<br>

* .length

* .toString()

* .indexOf(needle)

* .lastIndexOf(needle)

* .search(needle)

* .slice(start, end)

* .substring(start, end)

* .substr(start, end)

* .replace(needle, str)

</details>

<details>
<summary>Syntax</summary>
<br>
 
* for
 
* while / do while

* if / else if / else

* try / catch / finally

* function / lambda

* class

* new

* typeof

* instanceof

* undefined

* null

* Infinite

* NaN / isNaN

* true / false

</details>

# Main objectives
* Supporting EcmaScript 3 standard (then 5, 6 ...)
* Supporting NodeJS and NPM ecosystem
* Supporting a maximum of platforms (Windows, Mac, Linux, Android, Arduino, ...)
* Being secure
* Embeding debuging tools
* Compile everything that can be transpiled in JS : Ruby (Opal), Python (Transcript, Brython, JavaScrypthon), TypeScript ...

# Install
 
```
npm install -g nectarjs
```

# Using native compiler

* You need to have GCC installed on your machine and registered in your PATH to compile.

## Testing your installation

You can test your installation by running `npm run njs_test` 

You can also test ES3 support with `npm run es3_test`

## Windows

You can install Mingw and Clang for Windows here : http://winlibs.com/ or Clang here: https://releases.llvm.org/

You can also install Linux for Windows and use a linux system on Windows

You need MinGW with POSIX threads

## Linux / FreeBSD

On Linux or FreeBSD, you can install it with your distro (apt install gcc, yum install gcc, ...). You can use GCC, CLANG, or any derivative of those compilers (arm-gcc ...)

## Apple iOS

You can install xCode and you are ready.

## First compilation

```
nectar -b native file.js
or
nectar file.js
```

You can select a preset (speed or size):

```
nectar file.js --preset [speed|size]
```

You can also run the compiled executable just after compilation using --run:

```
nectar file.js --run
```

You can enable the quiet mode with --quiet:

```
nectar file.js --quiet
```

# Starting with compilation

The simplest way to use NectarJS is :

```
nectar file.js
```

The output file name will be automatically chosen regarding the target. You can specify another output with `-o something.out`

To show more compilation infos :

```
nectar --verbose file.js
```

Changing the stack size (usefull on Windows) :

```
nectar --stack 10000000 flood.js
```

For more informations about compilation output, use `--verbose`

For help, use `--help`


# Using compiler environments

NectarJS supports various compilation env:
* std
* node
* arduino
* wasm
* android

To compile a file using an env, you can use the --env switch :

```
nectar arduino-led.js --env arduino --target mega2560
```

# Android compilation

First step, you have to install Android SDK and Android NDK.

Second step, you need to setup NectarJS with the paths of the SDK and the NDK :

```
nectar --setsdk path_to_sdk --setndk path_to_ndk
```

You can show your configuration with: `nectar --config`

Third step: compile your JS app for Android using :

`nectar file.js --env android`

The result file is an Android APK.

You can select your target with `--target release|debug`.

Need: SDK Android-19 and Android-28
NDK: tested with NDK 21

# iOS compilation

You need Xcode to be able to compiler applications with NectarJS.

To compile a iOS app, select the iOS env with the flag --env ios :

`nectar app.js --env ios`

You can also target a plateform for running simulation :

`nectar app.js --env ios --target 'iPhone-8, 13.5' --run`

NectarJS will then compile your app and launch it with the simulator.

To test your configuration, you can compile example/ios.js app.

# Arduino compilation

To compile an Arduino firmware, you need a recent avr-gcc compiler that supports c++17 (8 or 10 for example).

You can download it here: https://blog.zakkemble.net/avr-gcc-builds/

Once done, compile your code by selecting the arduino env, and choosing a target: 

`nectar example/arduino-led.js --env arduino --target nano`

You can select a preset (speed or size) with:

`--preset speed` or `--preset size`

You can then flash the new firmware to a connected board with `--flash`

# STM32 compilation

To compile SMT32 firmware with NectarJS, you need first to instal mbed-cli and to setup your environment:

`https://os.mbed.com/docs/mbed-os/v6.0/build-tools/install-and-set-up.html`

Once done, compile your code by selecting the stm32 env, and choosing a target: 

`nectar example/stm32.js --env stm32 --target NUCLEO_F446RE`

You can select a preset (speed or size) with:

`--preset speed` or `--preset size`

# Compatibility targets/platforms

Tests are made with GCC 7 and Clang 6

* All supported GCC platforms

* All supported Clang platforms

* All supported AVR-GCC platforms

# Linking C/C++ libraries

C/C++ libraries linking can be done with this statement in your JS code :

`"!_ffi_include my/lib.h";`

NectarJS will then import your lib into the compilation folder.

## Meta functions in C++ libs 

In your C++ code, you can create functions as if you were in a JS env :

``` function cppMeta(arg1, arg2)
{
	return arg1 + arg2;
}
```

As in a JS env, NectarJS will create a variadic var function for you. It means that calling your function like this will be possible:

```
cppMeta()
cppMeta(1)
cppMeta(1,2)
cppMeta("a", "b", "c", "d")
``` 

## Adding external lib and .c/.cpp files

To add files to compile to GCC, or libraries, you will need to create a module and to fill the `lib` propery of `nectar` in your package.json file.

An example:

```
{
  "name": "my_module",
  "description": "My module",
  "main": "index.js",
  "nectar":
  {
    "env": ["std", "node", "arduino", "whatever..."],
	"lib":
	[
		"my/file1.cpp",
		"my/file2.cpp",
		"-lmylib"
	]
  }
}
```

# Optimization

 ## Profiling
 
 Profiling is a functionnality that improve the speed of your app by detecting the hot spots and improving their compilation. You have to compile your app twice: once before executing, and once after executing.
 
 These are the steps:
 
 1. Compile your app with the flags: `--profile gen --tmp perf`. --tmp value could be what you want, it's the target folder.
 2. Execute your app
 3. Recompile your app with the flags: `--profile use --tmp perf`. --tmp has to be the same value as step 1.
 4. Enjoy your app 15% faster.

# Stores 

NectarJS compiled apps are tested to be publishable on :

* Apple Store
    * https://apps.apple.com/fr/app/hiphen-plant/id1523867733

# Actively tested for

* android

* wasm

* asm-js

* wast

* mac-osx

* linux-x86-32

* linux-x86-64

* linux-arm32v7

* win-x86-32

* win-x86-64

* Sun OS

* arduino-nano

* arduino-uno

* arduino-mega1280

* arduino-mega2560

* nucleo-l152re

* nucleo-l432kc

* nucleo-f446re
