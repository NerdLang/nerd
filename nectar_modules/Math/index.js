/* Math std module */

var _Math = 
{
    abs: function(i)
    {
        if(i < 0) return -i;
        return i;
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
            return 0;   
        }
        return i;
    },
    PI: 3.141592653589793,
};


module.exports = _Math;
