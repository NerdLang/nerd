/*
 * This file is part of NectarJS
 * Copyright (c) 2017-2020 Adrien THIERRY
 * http://nectarjs.com - https://www.linkedin.com/in/adrien-thierry-fr/
 *
 * sources : https://github.com/nectarjs/nectarjs/
 *
 * this program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * You can be released from the requirements of the license by purchasing
 * a commercial license. Buying such a license is mandatory as soon as you
 * develop commercial activities involving the NectarJS software without
 * disclosing the source code of your own applications. Visit http://seraum.com/
 * and feel free to contact us.
 *
 */
 
 #include <iostream>
 #include <string>
 #include <cstring>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sstream>
 #include <vector>
 #include <memory>

 using namespace std;

 #include "njs.h"
 using namespace NECTAR;
 
/*** $ERROR ***/
function<__NJS_VAR (__NJS_VAR _var)>* __DOLLAR_TEST_ERROR = new function<__NJS_VAR (__NJS_VAR _var)>([&](__NJS_VAR _var){ __NJS_Log_Console(_var); exit(1); return 0; });
__NJS_VAR __NJS_DOLLAR_ERROR = __NJS_VAR(__NJS_FUNCTION, __DOLLAR_TEST_ERROR);
/* end $ERROR */
 
 {INCLUDE}
 
 {DECL}

int main(int argc, char* argv[])
{
	{INIT}

	{CODE}
	return 0;
}
