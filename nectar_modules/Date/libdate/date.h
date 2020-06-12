#include <ctime>

function __NJS_NATIVE_DATE_NOW(_format)
{

   time_t now = time(0);
   if(_format && _format == "UTC")
   {
      var _ret = ctime(&now);
      return _ret;
   }
   var _ret = (int)now;
   return _ret;
}
