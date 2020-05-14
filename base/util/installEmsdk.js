function installEmsdk()
{
    var tools = path.join(NECTAR_PATH, "tools");
    try { fs.mkdirSync( tools );}catch(e){}
    process.chdir(tools);
    console.log("[+] Cloning EMSDK");

    try 
    {
        execSync("git clone https://github.com/emscripten-core/emsdk.git");
    }
    catch(e)
    {
        console.log("[!] Error: it seem Git is not installed on this system.\n\n-> please, verify that Git is installed on your system and accessible with this shell")
        process.exit(0);
    }
    process.chdir("emsdk");

    console.log("[+] Updating EMSDK");
    execSync("git pull");

    var _prefix = "./";
    if(os.platform() == "win32") _prefix = "";

    console.log("[+] Installing EMSDK, wait a few moment");
    
    try 
    {
        execSync(_prefix + "emsdk install latest");
    }
    catch(e)
    {
        console.log("[!] Error: it seem Python is not installed on this system.\n\n-> please, verify that Python is installed on your system and accessible with this shell");
        process.exit(0);
    }

    console.log("[+] Activating EMSDK");
    execSync(_prefix + "emsdk activate latest");

}

module.exports = installEmsdk;