var mysql = require("mysql");

var _db = mysql.connect("test:password@localhost");

_db.add('{"language":"JS","compiler":"NectarJS"}');

var _data = _db.find('compiler = "NectarJS"');
console.log(_data);

_db.remove("true");

_db.close();