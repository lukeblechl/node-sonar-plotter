var ws = require('ws')
exports.connect = function (server) {
  var wss = new ws.Server({server: server})
  
  wss.on('connection', function connection(ws) {
    ws.on('message', function incoming(message) {
      console.log(message);
      ws.send(message);
    });
  });
}
