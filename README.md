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

# Tested on this targets/platforms :

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

