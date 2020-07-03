<p>
 
<img height="64" src="https://i.imgur.com/oXRdycNl.png">

<br>

Javascript's God Mode : one language to rule them all. Code everything, everywhere, for everything, in JavaScript.

No VM. No Bytecode. No Garbage Collector. Full Compiled and Native binaries.

Any questions or ideas, join us : [![NectarJS' Discord](https://img.shields.io/badge/Discord-Join-brightgreen.svg)](https://discord.gg/cpe2UuN)   [![Trello](https://img.shields.io/badge/Trello-Join-brightgreen.svg)](https://trello.com/invite/b/6F4rvEj2/9d7677f9dc6b5bf2f5b33e45fc794182/nectarjs)

<hr>

[![NPM](https://nodei.co/npm/nectarjs.png?downloads=true&downloadRank=true&stars=true)](https://nodei.co/npm/nectarjs/)

Full documentation is here (WIP) : [NectarJS Doc](https://doc.nectarjs.com/)

</p>

# Main objectives
* Supporting EcmaScript standard
* Supporting NodeJS and NPM ecosystem
* Supporting a maximum of platforms (Windows, Mac, Linux, Android, Arduino, ...)

# Install

```
npm install -g nectarjs
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

# Using native compiler

* You need to have GCC installed on your machine and registered in your path to compile.

You can install Mingw for Windows here : https://osdn.net/projects/mingw/downloads/68260/mingw-get-setup.exe/

On linux, you can install it with your distro (apt install gcc, yum install gcc, ...)

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

# STM32 compilation

To compile SMT32 firmware with NectarJS, you need first to instal mbed-cli and to setup your environment:

`https://os.mbed.com/docs/mbed-os/v6.0/build-tools/install-and-set-up.html`

Once done, compile your code by selecting the stm32 env, and choosing a target: 

`nectar example/stm32.js --env stm32 --target NUCLEO_F446RE`

You can select a preset (speed or size) with:

`--preset speed` or `--preset size`

# Compatibility targets/platforms :

* All supported GCC platforms

* All supported Clang platforms

* All supported AVR-GCC platforms


# Actively tested for :

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

* arduino-nano

* arduino-uno

* arduino-mega1280

* arduino-mega2560

* nucleo-l152re

* nucleo-l432kc

* nucleo-f446re

# String

* .length
* .toString()
* .indexOf(needle)
* .lastIndexOf(needle)
* .search(needle)
* .slice(start, end)
* .substring(start, end)
* .substr(start, end)
* .replace(needle, str)

# Array

* .length
* .push(value)
