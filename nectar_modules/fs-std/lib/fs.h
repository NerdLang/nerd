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

#include <unistd.h>
#include <stdio.h>
#include <fstream>

function __NJS_fs_readFileSync(_name)
{ 
	FILE* fp;

  int resultat = 1;

  fp = fopen(__NJS_Get_String(_name), "r");

  if(fp == NULL)
  {
    return __NJS_Create_String("");
  }

  fseek(fp, 0L, SEEK_END);
  long fsize = ftell(fp);
  fseek(fp, SEEK_SET, 0);

  char* buffer = (char*)malloc((fsize + 1) * sizeof(char));

  fread(buffer, fsize+1, 1, fp);

  buffer[fsize] = '\0';
  fclose(fp);
  return __NJS_Create_String(buffer);
};


function __NJS_fs_writeFileSync(_name, _content)
{
  std::ofstream myfile;
  myfile.open (__NJS_Get_String(_name), ios::out | ios::trunc);
  if(!myfile.is_open())
  {
    myfile.close();
    return __NJS_Create_Boolean(0);
  }

  myfile << __NJS_Get_String(_content);
  myfile.close();

  return __NJS_Create_Boolean(1);
};

function __NJS_fs_appendFileSync(_name, _content)
{
  std::ofstream myfile;
  myfile.open (__NJS_Get_String(_name), ios::out | ios::app);
  if(!myfile.is_open())
  {
    myfile.close();
    return __NJS_Create_Boolean(0);
  }

  myfile << __NJS_Get_String(_content);
  myfile.close();

  return __NJS_Create_Boolean(1);
};

function __NJS_fs_unlinkSync(_name)
{
  unlink(__NJS_Get_String(_name));
  return __NJS_Create_Boolean(1);
};

function __NJS_fs_rmdirSync(_name)
{
  rmdir(__NJS_Get_String(_name));
  return __NJS_Create_Boolean(1);
};

function __NJS_fs_removeSync(_name)
{
  remove(__NJS_Get_String(_name));
  return __NJS_Create_Boolean(1);
};
