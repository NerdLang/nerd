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

'!_ffi_include lib/fs.h';

var fs =
{
  readFile : __Nectar_fs_readFile,
  writeFile : __Nectar_fs_writeFile,
  appendFile : __Nectar_fs_appendFile,
  unlink : __Nectar_fs_unlink,
  rmdir : __Nectar_fs_rmdir,
  remove : __Nectar_fs_remove,
  rename: __Nectar_fs_rename,
  mkdir: __Nectar_fs_mkdir,
  readdir: "TODO",
  
  readFileSync : __Nectar_fs_readFileSync,
  writeFileSync : __Nectar_fs_writeFileSync,
  appendFileSync : __Nectar_fs_appendFileSync,
  unlinkSync : __Nectar_fs_unlinkSync,
  rmdirSync : __Nectar_fs_rmdirSync,
  removeSync : __Nectar_fs_removeSync,
  renameSync: __Nectar_fs_renameSync,
  mkdirSync: __Nectar_fs_mkdirSync,
  readdirSync: "TODO",
};

module.exports = fs;
