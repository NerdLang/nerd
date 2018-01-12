# Check syntax

You can only check syntax without compilation with argument `--check`.

# Project management

if `--single` is not specified, NectarJS will create a `project.json` file in the project directory.

You can create a `project.json` file without compilation with : `nectar --prepare file.js`

To show a project configuration : `nectar --project` in the project folder or `nectar --project /path/to/projet.json`

To compile a project, simply call `nectar project.json`

# Tips

you can enable tips by using `--tips`.

Example :

```
nectar --target arduino-uno --tips arduino.js
```

It will print :

```
[*] Tips : avrdude -p ATMEGA328P -c arduino -P [COMPORT] -b 19200 -F -U flash:w:arduino-arduino-uno.hex
```
