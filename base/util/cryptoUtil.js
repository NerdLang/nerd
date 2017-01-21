var crypto = require('crypto');
var Crypto =
{
    encrypt: function(text, password)
    {
      if(password == undefined) password = wf.CONF['AES_KEY'];
      var algorithm = 'aes-256-ctr';
      var cipher = crypto.createCipher(algorithm, password)
      var crypted = cipher.update(text, 'utf8', 'hex')
      crypted += cipher.final('hex');
      return crypted;
    },

    decrypt: function(text, password)
    {
  		try
  		{
              if(password == undefined) password = wf.CONF['AES_KEY'];
              var algorithm = 'aes-256-ctr';
              var decipher = crypto.createDecipher(algorithm, password)
              var dec = decipher.update(text, 'hex', 'utf8')
              dec += decipher.final('utf8');
              return dec;
  		}
  		catch(e)
  		{
  			return "";
  		};
    },

    returnHash: function(name, str)
    {
      switch (name)
      {
        case "MD5":
          return createMD5(str);
          break;

        case "SHA256":
          return createSHA256(str);
          break;

        case "SHA512":
          return createSHA512(str);
          break;

        default:
          return null;
          break;
      }
    },

    createMD5: function(str)
	  {
		    var shasum = crypto.createHash('MD5');
		    return shasum.update(str).digest('hex');
	  },

    createSHA256: function(str)
	  {
		    var shasum = crypto.createHash('sha256');
		    return shasum.update(str).digest('hex');
	  },

    createSHA512: function(str)
	  {
		    var shasum = crypto.createHash('sha512');
		    return shasum.update(str).digest('hex');
	  },
}
module.exports = Crypto;
