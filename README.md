<p>
No VM. No Bytecode. No packaging. No Garbage Collector. Fully compiled to native binaries.
</p>

# NectarJS becomes Nerd

Compile JavaScript and NerdLang in native binaries.

# What is NerdLang

NerdLang is a substract of JS with some additions, focus on efficiency.

**Nerd** is a **JavaScript native compiler** aiming to make JavaScript universal, Nerd is able to compile native apps for Windows, Mac, Linux, iOS, Android, Raspberry, STM32 and more.

> **Nerd** is in active development, join us on [Discord](https://discord.gg/cpe2UuN) if you need more information.

- [Roadmap on Trello](https://trello.com/invite/b/6F4rvEj2/ATTI8842296bacc92724fa8b4114fe1dc80aA9FA431B/nerd)

## Main objectives
* Supporting EcmaScript 3 standard (then 5, 6 ...)
* Supporting NodeJS and NPM ecosystem
* Supporting a maximum of platforms (Windows, Mac, Linux, Android, Arduino, ...)
* Being secure
* Embeding debuging tools
* Compile everything that can be transpiled in JS: Ruby (Opal), Python (Transcript, Brython, JavaScrypthon), TypeScript ...

# Get started

## Installation

### Install GCC/CLang for your platform

- Windows
Install Mingw and Clang for Windows here: http://winlibs.com/ or Clang here: https://releases.llvm.org/

You can also install Linux for Windows and use a linux system on Windows

You need MinGW with POSIX threads

- Linux / FreeBSD
Install it with your distro (apt install gcc, yum install gcc, ...).
You can use GCC, CLANG, as well as any derivative of those compilers (arm-gcc ...)

- Apple iOS
Install xCode and you are ready.


You can check your installation with `npm start njs_test`

## Usage

Simplest way to use Nerd:
```
nerd file.js / file.ng
```

The output file name will be automatically chosen regarding the target. You can specify another output with `-o something.out`

You can select a preset
```
nerd file.js --preset [none|speed|size]
```

You can also run the compiled executable just after compilation using --run:
```
nerd file.js --run
```

You can enable the quiet mode with --quiet:
```
nerd file.js --quiet
```

Changing the stack size (useful on Windows):
```
nerd --stack 10000000 flood.js
```

For more informations about compilation output, use `--verbose`

For help, use `--help`

# Benchmarks

* _Need update_

Compiled with GCC v10.2.0 on Windows

|           | NodeJS v12.8.1 | QuickJS 2020-07-05 | Nerd v0.6.104 |
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

# Supported platforms

Actively tested for

- Windows
* - win-x86-32
* - win-x86-64
- Linux
* - linux-x86-32
* - linux-x86-64
* - linux-arm32v7
- Arduino
* - arduino-nano
* - arduino-uno
* - arduino-mega1280
* - arduino-mega2560
- STM32 Nucleo
* - nucleo-l152re
* - nucleo-l432kc
* - nucleo-f446re
- Mobile
* - android
- Web
* - wasm
* - wast
* - asm-js
- macOS
- Sun OS

# Development

This project is in heavy development and a lot features are not implemented yet.

## ECMAScript Support

Nerd already supports more than 80% of ES3.

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
<summary>Math **(DONE)**</summary>
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