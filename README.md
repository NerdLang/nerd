# NectarJS
Javascript's God Mode

# Basic compilation

The simplest way to use NectarJS is :

```
nectar file.js
```

You can select a target for compilation with `--target [THE TARGET]`


# Project management

if --single is not specified, NectarJS will create a project.json file in the project directory.

You can create a project.json file without compilation with : nectar --prepare file.js

To show a project configuration : 'nectar --projet' in the project folder or 'nectar --project /path/to/projet.json'

To compile a project, simply call nectar project.json

# Available targets

* wasm
-> WebAssembly

* asm-js
-> ASM.js

* wast
-> WebAssembly AST

* linux-x86-32
-> Linux x86 32 bits

* linux-x86-64
-> Linux x86 64 bits

* linux-arm32v7
-> Linux arm 32 v7 bits, compatible with Android and Raspberry

* win-x86-32
-> Windows x86 32 bits

* win-x86-64
-> Windows x86 64 bits

* arduino-uno
-> Arduino UNO

* arduino-mega1280
-> Arduino Mega with Atmega 1280

* arduino-mega2560
-> Arduino Mega with Atmega 2560
