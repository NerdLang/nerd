/*
 * This file is part of NectarJS
 * Copyright (c) 2017 - 2020 Adrien THIERRY
 * http://nectarjs.com - https://seraum.com/
 *
 * sources : https://github.com/nectarjs/nectarjs
 * 
 * NectarJS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * NectarJS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with NectarJS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
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