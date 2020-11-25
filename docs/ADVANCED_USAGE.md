# Advanced usage

## Table of contents

* [Presets](#presets)
* [Environments](#environments)
* [Requirements and compilation](#requirements-and-compilation)
* - [Android](#android)
* - [iOS](#ios)
* - [Arduino](#arduino)
* - [STM32](#stm32)
* [Optimization](#optimization)
* - [Profiling](#profiling)
* [Compatibility Targets / Platforms](#compatibility-targetsplatforms)

# Presets

Select a compilation preset with `--preset [name]`

It's recommended to use any of presets below instead 
of passing optimization flags to compiler directly

| Preset | Optimize for          |
|--------|-----------------------|
| `speed`| Performance [default] |
| `size` | Output size           |
| `none` | Compilation speed     |

# Environments

Select a compilation environment with `--env [name]`

NectarJS supports various compilation environments
and some of them provides global variables and APIs 

| Name      | Environment       |
|-----------|-------------------|
| `std`     | *None* [default]  |
| `node`    | NodeJS            |
| `arduino` | Arduino firmware* |
| `wasm`    | WebAssembly file  |
| `android` | Android APK*      | 

* Some environments also need to specify compilation target with `--target [target]`

# Requirements and compilation

## Android

1. Install Java, Android SDK (19+) and Android NDK (21+)

2. Set path to SDK and NDK:

`nectar --setsdk path_to_sdk --setndk path_to_ndk`

> You can show your configuration with `nectar --config`

3. Compile to Android APK file:

`nectar app.js --env android`

4. (Optional) Select your compilation target with `--target [release|debug]`

## iOS

1. Install Xcode

2. Compile iOS app:

`nectar app.js --env ios`

3. (Optional) Compile and run app in device simulator with `--target 'iPhone-8, 13.5' --run`

## Arduino

1. Install a latest `avr-gcc` compiler that supports c++17 (download it [here](https://blog.zakkemble.net/avr-gcc-builds/))

2. Compile firmware for selected target: 

`nectar example/arduino-led.js --env arduino --target nano`

3. (Optional) Flash new firmware to a connected board with `--flash`

# STM32

1. Install `mbed-cli` and [set up environment](https://os.mbed.com/docs/mbed-os/v6.0/build-tools/install-and-set-up.html)

2. Compile for selected target: 

`nectar example/stm32.js --env stm32 --target NUCLEO_F446RE`



# Optimization

## Profiling
 
Profiling is a functionnality that improve the speed of your app by detecting the hot spots and improving their compilation. You have to compile your app twice: once before executing, and once after executing.
 
These are the steps:
 
1. Compile your app with the flags: `--profile gen --tmp perf`. --tmp value could be what you want, it's the target folder.
2. Execute your app
3. Recompile your app with the flags: `--profile use --tmp perf`. --tmp has to be the same value as step 1.
4. Enjoy your app get ~15% faster


# Compatibility targets/platforms

Tests are made with GCC 7 and Clang 6

* All supported GCC platforms
* All supported Clang platforms
* All supported AVR-GCC platforms
