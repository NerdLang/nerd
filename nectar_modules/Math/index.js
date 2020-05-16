/* Math std module */

var _Math = 
{
    /*** PROPERTIES ***/
    
    E: 2.718,
    LN2: 2.302,
    LOG2E: 1.442,
    LOG10E: 0.434,
    PI: 3.141592653589793,
    SQRT1_2: 0.707,
    SQRT2: 1.414,

    /*** END PROPERTIES ***/

    /*** METHODS ***/

    abs: function(i)
    {
        if(i < 0) return -i;
        return i;
    },
    imul: function(x, y)
    {
        var _res = 0;
        _res = (x * y);
        return _res;
    },
    max: function(_array)
    {
        var _res;
        for(var i = 0; i < _array.length; i++)
        {
            if(typeof _array[i] == "number")
            {
                if(typeof _res == "undefined") _res = _array[i];
                if(_array[i] > _res) _res = _array[i];
            } 
        }
        if(typeof _res == "undefined") _res = 0;
        return _res;
    },
    min: function(_array)
    {
        var _res;
        for(var i = 0; i < _array.length; i++)
        {
            if(typeof _array[i] == "number")
            {
                if(typeof _res == "undefined") _res = _array[i];
                if(_array[i] < _res) _res = _array[i];
            } 
        }
        if(typeof _res == "undefined") _res = 0;
        return _res;
    },
    pow: function(i, j)
    {
        if(j == 0) return 1;
        else if(j > 0)
        {
            j--;
            while(j)
            {
                i*=i;
                j--;
            }
        }
        else if(j < 0)
        {
            i = 1 / _Math.pow(i, _Math.abs(j));
        }
        return i;
    },
    
    /*** END METHODS ***/

};


module.exports = _Math;
