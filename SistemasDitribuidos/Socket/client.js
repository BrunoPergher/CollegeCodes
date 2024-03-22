const net = require('net');

const client = new net.Socket();
const port = 8088;
const host = '127.0.0.1';

client.connect(port, host, function() {
    console.log('Conectado ao servidor');

    client.write('Get /teste.html');
});

client.on('data', function(data) {
    console.log('Dados recebidos do servidor: ' + data);

    client.destroy();
});

client.on('close', function() {
    console.log('Conexão encerrada');
});
