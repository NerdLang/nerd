function copyDirSync( source, target ) 
{
    var targetFile = target;
    if ( fs.existsSync( target ) ) 
    {
        if ( fs.lstatSync( target ).isDirectory() ) 
        {
            targetFile = path.join( target, path.basename( source ) );
        }
    }
    fs.copyFileSync(source, targetFile);
}

function copyFolderRecursiveSync( source, target, _root ) 
{
    var files = [];
    var targetFolder = path.join( target, path.basename( source ) );
    if(_root) targetFolder = target;
    if ( !fs.existsSync( targetFolder ) ) 
    {
        fs.mkdirSync( targetFolder );
    }

    if ( fs.lstatSync( source ).isDirectory() ) 
    {
        files = fs.readdirSync( source );
        files.forEach( function ( file ) 
        {
            var curSource = path.join( source, file );
            if ( fs.lstatSync( curSource ).isDirectory() ) 
            {
                copyFolderRecursiveSync( curSource, targetFolder );
            } else 
            {
                copyDirSync( curSource, targetFolder );
            }
        } );
    }
}

module.exports = copyFolderRecursiveSync;