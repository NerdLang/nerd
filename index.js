#!/usr/bin/env node
/* eslint-disable spaced-comment, strict, global-require */

'use strict'

if (process.env.NODE_ENV === 'production') {
  module.exports = require('./build/nectarjs.production.js')
} else {
  module.exports = require('./build/nectarjs.development.js')
}
