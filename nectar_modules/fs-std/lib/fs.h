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

  size_t _ret = fread(buffer, fsize+1, 1, fp);

  buffer[fsize] = '\0';
  fclose(fp);
  return __NJS_Create_String(buffer);
};


function __NJS_fs_writeFileSync(_name, _content)
{
  std::ofstream myfile(__NJS_Get_String(_name), std::ios::out | std::ios::trunc | std::ios::binary);
  if(!myfile)
  {
    return __NJS_Create_Boolean(0);
  }
  myfile.write(((NJS::Class::String*)_content._ptr)->value.c_str(), ((NJS::Class::String*)_content._ptr)->value.size());
  myfile.close();

  return __NJS_Create_Boolean(1);
};

function __NJS_fs_appendFileSync(_name, _content)
{
  std::ofstream myfile(__NJS_Get_String(_name), std::ios::out | std::ios::app | std::ios::binary);
  if(!myfile)
  {
    return __NJS_Create_Boolean(0);
  }
  myfile.write(((NJS::Class::String*)_content._ptr)->value.c_str(), ((NJS::Class::String*)_content._ptr)->value.size());
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

function __NJS_fs_renameSync(_old, _new)
{
  rename(__NJS_Get_String(_old), __NJS_Get_String(_new));
  return __NJS_Create_Boolean(1);
};

function __NJS_fs_mkdirSync(_path)
{
	mkdir( ((std::string)_path).c_str() );
	return __NJS_Create_Boolean(1);
}
