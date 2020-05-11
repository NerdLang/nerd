/* Math std module */

function __POWER(i, j)
{
    j--;
    while(j)
    {
        i*=i;
        j--;
    }
    return i;
}

function __ABS(i)
{
    if(i < 0) return -i;
    return i;
}

var _Math = 
{
    abs: function(i)
    {
        return __ABS(i);
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
            i = 1 / __POWER(i, __ABS(j));
        }
        return i;
    },
    PI: 3.141592653589793,
};


module.exports = _Math;
