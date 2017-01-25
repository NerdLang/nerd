# NectarJS
Javascript's God Mode

# Install

You need `NodeJS` to install `NectarJS` : `https://nodejs.org/en/download/`.

Once done, install NectarJS : `npm install -g nectarjs`

Verify that NectarJS is installed with : `nectar --help`

# Basic compilation

The simplest way to use NectarJS is :

```
nectar file.js
```

The output file name will be automatically choosen regarding the target. You can specify another output with `-o something.out`

You can select a target for compilation with `--target [THE TARGET]`

The `--single` argument launch the compilation of the file in argument. If you need to `require('')` file in your current folder, you need to remove `--single` to switch to porject mode.

NectarJS can run directly your application after compilation if you specify `--run`. The program will be executed only if the `--target` match your system.

For more informations about compilation output, use `--verbose`

For help, use `--help`

# Project management

if `--single` is not specified, NectarJS will create a `project.json` file in the project directory.

You can create a `project.json` file without compilation with : `nectar --prepare file.js`

To show a project configuration : `nectar --projet` in the project folder or `nectar --project /path/to/projet.json`

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
