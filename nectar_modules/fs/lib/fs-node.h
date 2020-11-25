//void callback(uv_fs_t* req);
//fprintf(stderr, "error opening file: %s\n", uv_strerror((int)req->result));


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


function maybeCallback(cb) 
{
  if (cb.type == NectarCore::Enum::Type::Function)
    return cb;

  throw NectarCore::VAR("Invalid Callback");
}

long GetFileSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

long FdGetFileSize(int fd)
{
    struct stat stat_buf;
    int rc = fstat(fd, &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}


/*** Sync ***/
function __Nectar_fs_readFileSync(_name, _options, _cb)
{ 
	uv_fs_t openReq;
	uv_fs_open(__Nectar_UV_DEFAULT_LOOP, &openReq, ((std::string)_name).c_str(), O_RDONLY, 0, NULL);
	if (openReq.result < 0) 
	{
		fprintf(stderr, "error: %s\n", uv_strerror(openReq.result));
    } 
	else 
	{
		uv_fs_t readReq;
		uv_buf_t uvBuf;
		long _fsize = GetFileSize(((std::string)_name));
		char strBuf[_fsize];
		char dataBuf[_fsize];
		uvBuf = uv_buf_init(dataBuf, sizeof(dataBuf));
		
		uv_fs_read(__Nectar_UV_DEFAULT_LOOP, &readReq, openReq.result, &uvBuf, 1, -1, NULL);
		
		if (readReq.result < 0)
		{
			fprintf(stderr, "error: %s\n", uv_strerror(readReq.result));
		}
		else if (readReq.result == 0)
		{
			uv_fs_t closeReq;
			uv_fs_close(__Nectar_UV_DEFAULT_LOOP, &closeReq, openReq.result, NULL);
		}
		else
		{
			memset(strBuf, 0, sizeof(strBuf));
			memcpy(strBuf, dataBuf, sizeof(dataBuf));
			return strBuf;
		}
    }
};

function __Nectar_fs_writeFileSync(_name, _content)
{

};

function __Nectar_fs_appendFileSync(_name, _content)
{

};

function __Nectar_fs_unlinkSync(_name)
{

};

function __Nectar_fs_rmdirSync(_name)
{

};

function __Nectar_fs_removeSync(_name)
{

};

function __Nectar_fs_renameSync(_old, _new)
{

};

function __Nectar_fs_mkdirSync(_path)
{

}
/* END SYNC */

/*** Async ***/
/*
void onReadFile(uv_fs_t* readReq)
{
	if (readReq->result < 0)
	{
		fprintf(stderr, "error: %s\n", uv_strerror(readReq->result));
	}
	else if (readReq->result == 0)
	{
		//uv_fs_t closeReq;
		//uv_fs_close(__Nectar_UV_DEFAULT_LOOP, &closeReq, openReq.result, NULL);
	}
	else
	{
		memset(strBuf, 0, sizeof(strBuf));
		memcpy(strBuf, dataBuf, sizeof(dataBuf));
		//return strBuf;
	}
}

void onOpenFile(uv_fs_t* openReq)
{
	if (openReq->result < 0) 
	{
		fprintf(stderr, "error: %s\n", uv_strerror(openReq->result));
    } 
	else 
	{
		uv_fs_t readReq;
		uv_buf_t uvBuf;
		long _fsize = GetFileSize(((std::string)_name));
		char strBuf[_fsize];
		char dataBuf[_fsize];
		uvBuf = uv_buf_init(dataBuf, sizeof(dataBuf));
		
		uv_fs_read(__Nectar_UV_DEFAULT_LOOP, &readReq, openReq->result, &uvBuf, 1, -1, onReadFile);
		
		
    }
}
*/

struct __Nectar_UV_FS_DATA
{
	std::string filename;
	NectarCore::Class::Function* fn;
	char* charbuf;
	int size;
	uv_buf_t buffer;
};

function __Nectar_fs_readFile(_name, _cb)
{ 
	uv_fs_t* _openReq = new uv_fs_t();
	__Nectar_UV_FS_DATA* _data = new __Nectar_UV_FS_DATA{.filename = (std::string)_name, .fn = (NectarCore::Class::Function*)_cb.data.ptr};
	
	_openReq->data = _data;
	
	uv_fs_open(__Nectar_UV_DEFAULT_LOOP, _openReq, _data->filename.c_str(), O_RDONLY, 0,
	[](uv_fs_t* openReq)
	{
		if (openReq->result < 0)
		{
			NectarCore::Class::Function* fn = ((__Nectar_UV_FS_DATA*)openReq->data)->fn;
			std::string result = uv_strerror(openReq->result);
			
			free(((__Nectar_UV_FS_DATA*)openReq->data)->charbuf);
			free((__Nectar_UV_FS_DATA*)openReq->data);
			free(openReq);
			
			(*fn)(result);
		} 
		else 
		{
			uv_fs_t* _readReq = new uv_fs_t();;
			_readReq->data = openReq->data;

			long _fsize = GetFileSize(((__Nectar_UV_FS_DATA*)_readReq->data)->filename);
			((__Nectar_UV_FS_DATA*)_readReq->data)->size = _fsize;
			
			char* dataBuf = (char*)malloc(_fsize);
			((__Nectar_UV_FS_DATA*)_readReq->data)->charbuf = dataBuf;
			((__Nectar_UV_FS_DATA*)_readReq->data)->buffer = uv_buf_init(dataBuf, _fsize);
			
			free(openReq);
			
			uv_fs_read(__Nectar_UV_DEFAULT_LOOP, _readReq, openReq->result, &((__Nectar_UV_FS_DATA*)_readReq->data)->buffer, 1, -1,
			[](uv_fs_t* readReq)
			{
				if (readReq->result < 0)
				{
					NectarCore::Class::Function* fn = ((__Nectar_UV_FS_DATA*)readReq->data)->fn;
					std::string result = uv_strerror(readReq->result);
					
					free(((__Nectar_UV_FS_DATA*)readReq->data)->charbuf);
					free((__Nectar_UV_FS_DATA*)readReq->data);
					free(readReq);
					
					(*fn)(result);
				}
				else if (readReq->result == 0)
				{
					uv_fs_close(__Nectar_UV_DEFAULT_LOOP, readReq, readReq->result,
					[](uv_fs_t* closeReq)
					{
						NectarCore::Class::Function* fn = ((__Nectar_UV_FS_DATA*)closeReq->data)->fn;
						free(((__Nectar_UV_FS_DATA*)closeReq->data)->charbuf);
						free((__Nectar_UV_FS_DATA*)closeReq->data);
						free(closeReq);
						
						(*fn)();
					});
				}
				else
				{
					char* strBuf = (char*)malloc(((__Nectar_UV_FS_DATA*)readReq->data)->size);
					memset(strBuf, 0, ((__Nectar_UV_FS_DATA*)readReq->data)->size);
					memcpy(strBuf, ((__Nectar_UV_FS_DATA*)readReq->data)->charbuf, ((__Nectar_UV_FS_DATA*)readReq->data)->size);
					
					NectarCore::Class::Function* fn = ((__Nectar_UV_FS_DATA*)readReq->data)->fn;
					NectarCore::VAR _res = strBuf;
					
					free(((__Nectar_UV_FS_DATA*)readReq->data)->charbuf);
					free((__Nectar_UV_FS_DATA*)readReq->data);
					free(readReq);
					
					(*fn)(null, _res);
				}
			});
		}
	});
};


function __Nectar_fs_writeFile(_name, _content, _cb)
{

};

function __Nectar_fs_appendFile(_name, _content, _cb)
{

};

function __Nectar_fs_unlink(_name, _cb)
{

};

function __Nectar_fs_rmdir(_name, _cb)
{

};

function __Nectar_fs_remove(_name, _cb)
{

};

function __Nectar_fs_rename(_old, _new, _cb)
{

};

function __Nectar_fs_mkdir(_path, _cb)
{

}
/* END ASYNC */
