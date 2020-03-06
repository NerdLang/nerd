<p align="center" style="margin:auto";>
  
<img height="64" src="https://i.imgur.com/oXRdycNl.png">

<br>

Javascript's God Mode : one language to rule them all. Code everything, everywhere, for everything, in JavaScript.

Any questions or ideas, join us : [![NectarJS' Discord](https://img.shields.io/badge/Discord-Join-brightgreen.svg)](https://discord.gg/cpe2UuN)   [![Trello](https://img.shields.io/badge/Trello-Join-brightgreen.svg)](https://trello.com/invite/b/6F4rvEj2/9d7677f9dc6b5bf2f5b33e45fc794182/nectarjs)

<hr></hr>

[![Metrics](https://img.shields.io/badge/Metrics-ON-green.svg)](https://app.databox.com/datawall/1584c72f8ba105f7c7435fbcdf0921c405b6bdf4b)
[![Uptime](https://img.shields.io/badge/dynamic/json.svg?label=API%20Uptime&url=https%3A%2F%2Fapi.uptimerobot.com%2FgetMonitors%3FapiKey%3Dm780802413-76e2ae897675f9ab020aa79f%26responseTimes%3D0%26logs%3D1%26format%3Djson%26noJsonCallback%3D1&query=%24.monitors.monitor%5B0%5D.alltimeuptimeratio&colorB=green&suffix=%25)](https://status.nectarjs.com)

[![NPM](https://nodei.co/npm/nectarjs.png?downloads=true&downloadRank=true&stars=true)](https://nodei.co/npm/nectarjs/)

Full documentation is here : [NetcarJS Doc](https://doc.nectarjs.com/)

</p>

# Install

npm install -g nectarjs

To reinstall, use nectar --install

# Basic bytecode compilation

The simplest way to use NectarJS is :

```
nectar -c bc file.js
```

The output file name will be automatically choosen regarding the target. You can specify another output with `-o something.out`

You can run any JS or BIN file like this :

```
nectar file.[js|bin]
```

For more informations about compilation output, use `--verbose`

For help, use `--help`

# Using C/GCC

* You need to have GCC installed on your machine and registered in your path.

```
nectar -c c file.js
```

You can select a preset (speed or size):

```
nectar -c bc file.js --preset size
```

You can also run the compiled executable just after compilation using --run:

```
nectar -c bc file.js --run
```

You can enable the quiet mode with --quiet:

```
nectar -c bc file.js --quiet
```

# Available targets (DEPRECATED)

* wasm -> WebAssembly

* asm-js -> ASM.js

* wast -> WebAssembly AST

* mac-osx -> Mac OSX

* linux-x86-32 -> Linux x86 32 bits

* linux-x86-64 -> Linux x86 64 bits

* linux-arm32v7 -> Linux arm 32 v7 bits, compatible with Android and Raspberry

* win-x86-32 -> Windows x86 32 bits

* win-x86-64 -> Windows x86 64 bits

* arduino-uno -> Arduino UNO

* arduino-mega1280 -> Arduino Mega with Atmega 1280

* arduino-mega2560 -> Arduino Mega with Atmega 2560

* nucleo-l152re -> STM32 Nucleo L152RE

* nucleo-l432kc -> STM32 Nucleo L432KC

