var mysqlx = require("mysqlx");

var _db = mysqlx.connect("test:password@localhost");

_db.add('{"language":"JS","compiler":"NectarJS"}');

var _data = _db.find('compiler = "NectarJS"');

console.log(JSON.parse(_data).data[0]);

_db.remove("true");

_db.close();
