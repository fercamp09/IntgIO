var express = require('express');
var app = express();
var server = require('http').Server(app);
var io = require('socket.io')(server);

app.use(express.static('public'));
/*
app.get('/index.html', function (req, res) {
   res.sendFile( __dirname + "/" + "index.html" );
})


 app.get('/process_get', function (req, res) /*
{
   // Prepare output in JSON format
   response = {
      first_name:req.query.first_name,
      last_name:req.query.last_name
   };
   console.log(response);
   res.end(JSON.stringify(response));
}) */


io.on('connection', function(socket){
	console.log("El cliente se ha conectado");
});

server.listen(8081, function(){
	console.log("servidor corriendo en 8081");
});
