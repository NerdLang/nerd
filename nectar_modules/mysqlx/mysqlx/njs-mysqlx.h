#include <mysqlx/xdevapi.h>

using namespace ::mysqlx;

function __NJS_NATIVE_CONNECT_MYSQL(_auth, _schema, _coll)
{
  try 
  {
    if(!_auth) _auth = "mysqlx://root@localhost";
    else
    {
      if(_auth.type == __NJS_STRING) _auth = "mysqlx://" + _auth;
      else if(_auth.type == __NJS_OBJECT)
      {
        var _strauth = "mysqlx://";

        var _user = __NJS_Object_Get("user", _auth);
        if(_user.type == __NJS_STRING) _strauth += _user;
        else _strauth += "root";

        var _pass = __NJS_Object_Get("pass", _auth);
        if(_pass.type == __NJS_STRING) _strauth += ":" + _pass;

        var _host = __NJS_Object_Get("host", _auth);
        if(_host.type == __NJS_STRING) _strauth += "@" + _host;
        else _strauth += "localhost";

        _auth = _strauth;  
      }
    }

    if(!_schema) _schema = "nectarSchema";
    if(!_coll) _coll = "nectar";

    Session* sess = new Session(__NJS_Get_String(_auth));
    Schema sch= sess->getSchema(__NJS_Get_String(_schema));
    Collection coll= sch.createCollection(__NJS_Get_String(_coll), true);

    var _mysqlObject = __NJS_Create_Object();

    function _mysql_close()
    {
      delete sess;
    };

    function _mysql_add(_json)
    {
      coll.add(__NJS_Get_String(_json)).execute();
      var _result = __NJS_Create_Boolean(1);
      return _result;
    };

    function _mysql_find(_request)
    {
      var _result = __NJS_Create_Array();
      std::list<DbDoc> dbList = coll.find(__NJS_Get_String(_request)).execute().fetchAll();

      int i = 0;
      std::list<DbDoc>::iterator it;
      stringstream s;
      s << "{\"data\":[";
      for (it = dbList.begin(); it != dbList.end(); it++)
      {
        if(i) s << ",";
        it->print(s);
        i++;
      }
      s << "], \"code\":0}";
      std::string _str = std::string(s.str());
      var _data = _str.c_str();
      return _data;
    }
    
    function _mysql_remove(_request)
    {
      coll.remove(__NJS_Get_String(_request)).execute();
    }

    __NJS_Object_Set("version", "8", _mysqlObject);
    __NJS_Object_Set("add", _mysql_add, _mysqlObject);
    __NJS_Object_Set("find", _mysql_find, _mysqlObject);
    __NJS_Object_Set("remove", _mysql_remove, _mysqlObject);
    __NJS_Object_Set("close", _mysql_close, _mysqlObject);

    return _mysqlObject;

  }
  catch (const mysqlx::Error &err)
  {
    cout <<"ERROR: " <<err <<endl;
    return var();
  }
  catch (std::exception &ex)
  {
    cout <<"STD EXCEPTION: " <<ex.what() <<endl;
    return var();
  }
  catch (const char *ex)
  {
    cout <<"EXCEPTION: " <<ex <<endl;
    return var();
  }
};
