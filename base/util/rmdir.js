var rmdir = function(dir, callback)
{
	  fs.readdir(dir, function(err, list)
    {
        if(err)
        {
            try
            {
                fs.unlink(dir, function(err)
                {
                    callback(err);
                });
            }
            catch(e){}
        }
        else
        {
            var i = 0;
            var j = list.length;
            var cb = function(){ fs.rmdir(dir, function(err){if(callback && typeof callback == "function") callback(err);});};
            recursiveRm(dir, i, j, list, cb);
            return;
        }
    });

    function recursiveRm(from, i, j, list, cb)
    {

        function nextFile()
        {
            i++;
            if(i < j)
            {
                recursiveRm(from, i, j, list, cb);
            }
            else
            {
                if(cb && typeof cb == "function")
                    cb();
            }
        }
        var filename = "";

        try
        {
          filename = path.join(from, list[i]);
        }
        catch(e)
        {
          nextFile();
          return;
        }

        fs.stat(filename, function(err, stat)
        {
          if(err)
          {
            nextFile();
          }
          else if(stat.isDirectory())
          {
            if(filename)
            {
              rmdir(filename, nextFile);
            }
            else
            {
              nextFile();
            }
          }
          else
          {
            fs.unlink(filename, nextFile);
          }
        });
    }
};

module.exports = rmdir;