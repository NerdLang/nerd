/*
 * This file is part of NectarJS
 * Copyright (c) 2017 Adrien THIERRY
 * http://nectarjs.com - http://seraum.com
 *
 * sources : https://github.com/seraum/nectarjs
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */
var crypto = require('crypto');
var Crypto =
{
  encrypt: function(text, password)
  {
    var iv = crypto.randomBytes(32).toString('hex').slice(0, 16);
    if(password == undefined) password = wf.CONF['AES_KEY'];
    var algorithm = 'aes-256-ctr';
    var cipher = crypto.createCipheriv(algorithm, Crypto.createSHA256(password).slice(0, 32), iv)
    var crypted = cipher.update(text, 'utf8', 'hex')
    crypted += cipher.final('hex');
    return iv + ":" + crypted;
  },

  decrypt: function(text, password)
  {
    try
    {
            var encryptedArray = text.split(':');
            var iv = encryptedArray[0];
            var encrypted = Buffer.from(encryptedArray[1], 'hex');
            if(password == undefined) password = wf.CONF['AES_KEY'];
            var algorithm = 'aes-256-ctr';
            var decipher = crypto.createDecipheriv(algorithm, Crypto.createSHA256(password).slice(0, 32), iv)
            var dec = decipher.update(encrypted, 'hex', 'utf8')
            dec += decipher.final('utf8');
            return dec;
    }
    catch(e)
    {
      console.dir(e);
      return "";
    };
  },

    returnHash: function(name, str)
    {
      switch (name)
      {
        case "MD5":
          return Crypto.createMD5(str);
          break;

        case "SHA256":
          return Crypto.createSHA256(str);
          break;

        case "SHA512":
          return Crypto.createSHA512(str);
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
