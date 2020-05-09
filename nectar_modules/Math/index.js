/* Math std module */

var _Math = 
{
    abs: function(i){return i;},
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
            j--;
            while(j)
            {
                i/=i;
                j--;
            }
        }
        return i;
    },
};


module.exports = _Math;
