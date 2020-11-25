/*
 * This file is part of NectarJS
 * Copyright (c) 2017-2018 Adrien THIERRY
 * http://nectarjs.com - https://www.linkedin.com/in/adrien-thierry-fr/
 *
 * sources : https://github.com/nectarjs/nectar_modules/
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

function __Nectar_CHILD_PROCESS_EXEC_SYNC(_cmd)
{
  FILE *fp;
  const int pSize = 64;
  int bSize = pSize;
  int now = 0;
  char* buffer = (char*)malloc(pSize * sizeof(char));

  buffer[0] = 0;
  char pChar[pSize];

  fp = popen(((std::string)_cmd).c_str(), "r");
  
  if (fp == NULL)
  {
    printf("Failed to run command\n" );
    return NectarCore::VAR();
  }

  while (fgets(pChar, sizeof(pChar), fp) != NULL)
  {
    now += strlen(pChar);
    if(now > bSize)
    {
      bSize += (now) * 1.5;
      buffer = (char*)realloc(buffer, bSize);
    }
    strcat(buffer, pChar);
  }

	pclose(fp);

  NectarCore::VAR _return = buffer;
  free(buffer);
  return _return;
}
