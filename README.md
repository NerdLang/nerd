# NectarJS
Javascript's God Mode : one language to rule them all. Code everything, everywhere, for everything, in JS, TS, CS and more.

[![Uptime](https://img.shields.io/badge/dynamic/json.svg?label=API%20Uptime&url=https%3A%2F%2Fapi.uptimerobot.com%2FgetMonitors%3FapiKey%3Dm780802413-76e2ae897675f9ab020aa79f%26responseTimes%3D0%26logs%3D1%26format%3Djson%26noJsonCallback%3D1&query=%24.monitors.monitor%5B0%5D.alltimeuptimeratio&colorB=green&suffix=%25)](https://status.nectarjs.com)
[![Compilations](https://img.shields.io/badge/dynamic/json.svg?label=Compilations%20&url=https%3A%2F%2Fapi.nectarjs.com%2Fcount.json&query=%24.data.count&colorB=blue)](https://nectarjs.com)
[![users](https://img.shields.io/badge/dynamic/json.svg?label=Registered%20Users&colorB=ffa500&prefix=&suffix=&query=$.data&uri=http://nectar-lang.com/stats/users.json)](http://nectar-lang.com/key) [![Slack](https://img.shields.io/badge/dynamic/json.svg?label=Slack%20Users&colorB=blue&prefix=&suffix=&query=$.data&uri=http://nectar-lang.com/stats/slack.json)](https://join.slack.com/t/nectarjs/shared_invite/enQtNDA4MDMwNzE1MjA3LTc1NmVjNGRiMmYwOGRjNDg0M2IwYTAyZDM2MDY4MjllNjcxNDU2NzhiNTgzNDQxZjI2NDcxNzA5MTBlNjE1NDc) [![Contribute](https://img.shields.io/badge/Contribution-Open-brightgreen.svg)](http://nectar-lang.com/contribute/) [![Sandbox](https://img.shields.io/badge/Sandbox-Beta_v0.1-green.svg)](http://nectar-lang.com)

[![NPM](https://nodei.co/npm/nectarjs.png?downloads=true&downloadRank=true&stars=true)](https://nodei.co/npm/nectarjs/)

Join us on Slack : [NectarJS' Slack](https://join.slack.com/t/nectarjs/shared_invite/enQtNDA4MDMwNzE1MjA3LTc1NmVjNGRiMmYwOGRjNDg0M2IwYTAyZDM2MDY4MjllNjcxNDU2NzhiNTgzNDQxZjI2NDcxNzA5MTBlNjE1NDc)

Get your free key here : [NectarJS free Key](http://nectar-lang.com/key/)

Full documentation is here : [NetcarJS Doc](https://doc.nectarjs.com/)

# Current NectarScript version

Current : [**NS-0.1**](https://github.com/NectarJS/nectarscript/blob/master/nectarscript-0.1.MD)

# Install

You need `NodeJS` to install `NectarJS` : `https://nodejs.org/en/download/`.

Once done, install NectarJS : `npm install -g nectarjs`

Verify that NectarJS is installed with : `nectar --help`

# Configuration

You need to enter your id and you security key. Code is encrypted in AES during compilation.

To set your id, use `--setid myid`

To set your key, use `--setkey mykey`

# Basic compilation

The simplest way to use NectarJS is :

```
nectar file.js
```

The output file name will be automatically choosen regarding the target. You can specify another output with `-o something.out`

You can select a target for compilation with `--target [THE TARGET]`

The `--single` argument launch the compilation of the file in argument. If you need to `require('')` file in your current folder, you need to remove `--single` to switch to project mode.

NectarJS can run directly your application after compilation if you specify `--run`. The program will be executed only if the `--target` match your system.

For more informations about compilation output, use `--verbose`

For help, use `--help`

# Check syntax

You can only check syntax without compilation with argument `--check`.

# Project management

if `--single` is not specified, NectarJS will create a `project.json` file in the project directory.

You can create a `project.json` file without compilation with : `nectar --prepare file.js`

To show a project configuration : `nectar --project` in the project folder or `nectar --project /path/to/projet.json`

To compile a project, simply call `nectar project.json`

# Coding with your smartphone or tablet

If you want to code with your smartphone or tablet, you can download `Termux`, a console app that let you install `nodejs` for your device. Simply install NectarJS with `npm install -g nectarjs`, and you can start coding with your smartphone for all other platforms.

# Available targets

* wasm -> WebAssembly

* asm-js -> ASM.js

* wast -> WebAssembly AST

* linux-x86-32 -> Linux x86 32 bits

* linux-x86-64 -> Linux x86 64 bits

* linux-arm32v7 -> Linux arm 32 v7 bits, compatible with Android and Raspberry

* win-x86-32 -> Windows x86 32 bits

* win-x86-64 -> Windows x86 64 bits

* arduino-uno -> Arduino UNO

* arduino-mega1280 -> Arduino Mega with Atmega 1280

* arduino-mega2560 -> Arduino Mega with Atmega 2560
