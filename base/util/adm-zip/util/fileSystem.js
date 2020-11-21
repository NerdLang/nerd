exports.require = function() {
  var fs = require("fs");
  if (process.versions['electron']) {
	  try {
		  fs = require("original-fs")
	  } catch (e) {}
  }
  return fs
};
