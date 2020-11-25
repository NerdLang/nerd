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
#include <dirent.h>

#ifndef WIN32
    #include <sys/types.h>
#endif

/*** Sync ***/
function __Nectar_fs_readFileSync(_name)
{ 
	FILE* fp;

  int resultat = 1;

  fp = fopen(__Nectar_Get_String(_name), "r");

  if(fp == NULL)
  {
    return __Nectar_Create_String("");
  }

  fseek(fp, 0L, SEEK_END);
  long fsize = ftell(fp);
  fseek(fp, SEEK_SET, 0);

  char* buffer = (char*)malloc((fsize + 1) * sizeof(char));

  size_t _ret = fread(buffer, fsize+1, 1, fp);

  buffer[fsize] = '\0';
  fclose(fp);
  return __Nectar_Create_String(buffer);
};


function __Nectar_fs_writeFileSync(_name, _content)
{
  std::ofstream myfile(__Nectar_Get_String(_name), std::ios::out | std::ios::trunc | std::ios::binary);
  if(!myfile)
  {
    return __Nectar_Create_Boolean(0);
  }
  myfile.write(((NectarCore::Class::String*)_content.data.ptr)->value.c_str(), ((NectarCore::Class::String*)_content.data.ptr)->value.size());
  myfile.close();

  return __Nectar_Create_Boolean(1);
};

function __Nectar_fs_appendFileSync(_name, _content)
{
  std::ofstream myfile(__Nectar_Get_String(_name), std::ios::out | std::ios::app | std::ios::binary);
  if(!myfile)
  {
    return __Nectar_Create_Boolean(0);
  }
  myfile.write(((NectarCore::Class::String*)_content.data.ptr)->value.c_str(), ((NectarCore::Class::String*)_content.data.ptr)->value.size());
  myfile.close();

  return __Nectar_Create_Boolean(1);
};

function __Nectar_fs_unlinkSync(_name)
{
  unlink(__Nectar_Get_String(_name));
  return __Nectar_Create_Boolean(1);
};

function __Nectar_fs_rmdirSync(_name)
{
  rmdir(__Nectar_Get_String(_name));
  return __Nectar_Create_Boolean(1);
};

function __Nectar_fs_removeSync(_name)
{
  remove(__Nectar_Get_String(_name));
  return __Nectar_Create_Boolean(1);
};

function __Nectar_fs_renameSync(_old, _new)
{
  rename(__Nectar_Get_String(_old), __Nectar_Get_String(_new));
  return __Nectar_Create_Boolean(1);
};

function __Nectar_fs_mkdirSync(_path)
{
	#ifndef __linux__ 
	mkdir( ((std::string)_path).c_str() );
	#endif
	return __Nectar_Create_Boolean(1);
}
/* END SYNC */

/*** Async ***/
function __Nectar_fs_readFile(_name, _cb)
{ 
	FILE* fp;

  int resultat = 1;

  fp = fopen(__Nectar_Get_String(_name), "r");

  if(fp == NULL)
  {
	if(_cb) _cb(null, "");
    return NectarCore::Global::undefined;
  }

  fseek(fp, 0L, SEEK_END);
  long fsize = ftell(fp);
  fseek(fp, SEEK_SET, 0);

  char* buffer = (char*)malloc((fsize + 1) * sizeof(char));

  size_t _ret = fread(buffer, fsize+1, 1, fp);

  buffer[fsize] = '\0';
  fclose(fp);
  if(_cb) _cb(null, __Nectar_Create_String(buffer));
};


function __Nectar_fs_writeFile(_name, _content, _cb)
{
  std::ofstream myfile(__Nectar_Get_String(_name), std::ios::out | std::ios::trunc | std::ios::binary);
  if(!myfile)
  {
	if(_cb) _cb(null, __Nectar_Boolean_FALSE);
    return NectarCore::Global::undefined;
  }
  myfile.write(((NectarCore::Class::String*)_content.data.ptr)->value.c_str(), ((NectarCore::Class::String*)_content.data.ptr)->value.size());
  myfile.close();

  if(_cb) _cb(null, __Nectar_Boolean_TRUE);
};

function __Nectar_fs_appendFile(_name, _content, _cb)
{
  std::ofstream myfile(__Nectar_Get_String(_name), std::ios::out | std::ios::app | std::ios::binary);
  if(!myfile)
  {
	if(_cb) _cb(null, __Nectar_Boolean_FALSE);
    return NectarCore::Global::undefined;
  }
  myfile.write(((NectarCore::Class::String*)_content.data.ptr)->value.c_str(), ((NectarCore::Class::String*)_content.data.ptr)->value.size());
  myfile.close();

  if(_cb) _cb(null, __Nectar_Boolean_TRUE);
};

function __Nectar_fs_unlink(_name, _cb)
{
  unlink(__Nectar_Get_String(_name));
  
  if(_cb) _cb(null, __Nectar_Boolean_TRUE);
};

function __Nectar_fs_rmdir(_name, _cb)
{
  rmdir(__Nectar_Get_String(_name));
  
  if(_cb) _cb(null, __Nectar_Boolean_TRUE);
};

function __Nectar_fs_remove(_name, _cb)
{
  remove(__Nectar_Get_String(_name));
  
  if(_cb) _cb(null, __Nectar_Boolean_TRUE);
};

function __Nectar_fs_rename(_old, _new, _cb)
{
  rename(__Nectar_Get_String(_old), __Nectar_Get_String(_new));
  
  if(_cb) _cb(null, __Nectar_Boolean_TRUE);
};

function __Nectar_fs_mkdir(_path, _cb)
{
	#ifndef __linux__ 
	mkdir( ((std::string)_path).c_str() );
	#endif
	if(_cb) _cb(null, __Nectar_Boolean_TRUE);
}
/* END ASYNC */
