import socket

# Configuração do servidor a ser conectado
host = '127.0.0.1'  # Endereço do servidor
porta = 65432       # Porta do servidor

# Criando o socket TCP/IP
cliente = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Conectando ao servidor
cliente.connect((host, porta))

# Autenticação do usuário
matricula = input("Digite sua matrícula: ")
senha = input("Digite sua senha: ")
cliente.sendall(f"{matricula};{senha}".encode())

# Verificação da resposta do servidor sobre a autenticação
resposta_servidor = cliente.recv(1024).decode()
if resposta_servidor == "ERRO_AUTENTICACAO":
    print("Erro de autenticação. Verifique sua matrícula e senha.")
    cliente.close()
else:
    print("Autenticado com sucesso. Iniciando o quiz.")

    # Recebendo e respondendo questões
    while True:
        dados = cliente.recv(1024).decode()
        if dados.startswith("Total de questões"):
            print(dados)  # Mostra o resultado final
            break
        else:
            questao = eval(dados)
            print(questao["pergunta"])
            for opcao in questao["opcoes"]:
                print(opcao)
            resposta = input("Escolha sua resposta (A, B, C ou D): ")
            cliente.sendall(resposta.encode())

    # Finalizando a conexão
    cliente.close()
