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

The `--single` argument launch the compilation of the file in argument. If you need to `require('')` file in your current folder, you need to remove `--single` to switch to porject mode.

NectarJS can run directly your application after compilation if you specify `--run`. The program will be executed only if the `--target` match your system.

For more informations about compilation output, use `--verbose`

For help, use `--help`
