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
      "SCOPED_FUNCTION";                                                                                                    
      try
      {                                                                                                                       
        coll.add(__NJS_Get_String(_json)).execute();
        var _result = __NJS_Create_Boolean(1);
        return _result;
      }
      catch(const std::exception& e)
      {
        return __NJS_Create_Boolean(0);
      }
    };
    
   function _mysql_modify(_obj)
   {
     "SCOPED_FUNCTION";
     var _search = __NJS_Object_Get("search",_obj);
     if(_search.type != __NJS_STRING) return __NJS_Create_Boolean(0);

        auto _cm = coll.modify(__NJS_Get_String(_search));

        var _set = __NJS_Object_Get("set", _obj);
        if(_set && _set.type == __NJS_ARRAY)
        {
          var _left = __NJS_Object_Get(0, _set);
          var _right = __NJS_Object_Get(1, _set);
          if(_left.type == __NJS_STRING && _right.type == __NJS_STRING)
          _cm.set(__NJS_Get_String(_left), __NJS_Get_String(_right));
        }
        _cm.execute();

        var _result = __NJS_Create_Boolean(1);
        return _result;
   }

    function _mysql_find(_request)
    {
      "SCOPED_FUNCTION";
      var _result = __NJS_Create_Array();
      std::list<DbDoc> dbList;
      if(_request) dbList = coll.find(__NJS_Get_String(_request)).execute().fetchAll();
      else dbList = coll.find().execute().fetchAll();
      
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
      s << "], \"code\":0, \"length\":" << dbList.size() << "}";
      std::string _str = std::string(s.str());
      var _data = _str.c_str();
      return _data;
    }
    
    function _mysql_remove(_request)
    {
      "SCOPED_FUNCTION";
      coll.remove(__NJS_Get_String(_request)).execute();
    }

    __NJS_Object_Set("version", "8", _mysqlObject);
    __NJS_Object_Set("add", _mysql_add, _mysqlObject);
    __NJS_Object_Set("modify", _mysql_modify, _mysqlObject);
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
