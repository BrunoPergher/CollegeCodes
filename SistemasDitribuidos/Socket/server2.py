import socket
import os

PORT = 8088
DIRECTORY = "C:/Users/bruno/Documents/GitHub/CollegeCodes/SistemasDitribuidos/Socket"

# Cria um socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('', PORT))
server_socket.listen(5)

print(f'Servidor escutando na porta {PORT}...')

while True:
    # Aceita uma conexão
    client_socket, addr = server_socket.accept()
    print(f'Conexão recebida de {addr}')
    
    # Recebe a mensagem do cliente
    message = client_socket.recv(1024).decode('utf-8')
    print(f'Mensagem recebida: {message}')
    
    # Verifica se a mensagem recebida está no formato esperado
    if message.startswith('GET ') and ' ' in message:
        # Extrai o caminho do arquivo da mensagem
        file_path = message.split(' ')[1]
        full_path = DIRECTORY + file_path
        
        # Verifica se o arquivo existe e envia seu conteúdo ou uma mensagem de erro
        if os.path.exists(full_path):
            with open(full_path, 'rb') as file:
                client_socket.sendall(file.read())
        else:
            client_socket.sendall(b'Erro 404: Arquivo nao encontrado.')
    else:
        client_socket.sendall(b'Erro: Formato de mensagem invalido.')

    # Fecha a conexão com o cliente
    client_socket.close()