var express = require('express')
var app = express()

var server = app.listen(3000, function () {
  console.log('Server listening on', 3000)
})
require('./websockets').connect(server)
