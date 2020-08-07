#include <chrono>

using namespace std::chrono;

function __NJS_NATIVE_DATE_NOW()
{
   return __NJS_VAR((int)duration_cast<milliseconds>(
      system_clock::now().time_since_epoch()
   ).count());
};
