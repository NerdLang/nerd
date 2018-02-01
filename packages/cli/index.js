#!/usr/bin/env node
/* eslint-disable spaced-comment, strict, global-require */

'use strict'

if (process.env.NODE_ENV === 'production') {
  module.exports = require('./dist/index.production.js')
} else {
  module.exports = require('./dist/index.development.js')
}
