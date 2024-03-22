import zmq

context = zmq.Context()
socket = context.socket(zmq.REQ)  # REQ (Request) socket
socket.connect("tcp://localhost:5555")

print("Cliente conectado ao servidor.")

# Autenticação do usuário
matricula = input("Digite sua matrícula: ")
senha = input("Digite sua senha: ")
socket.send_json({"tipo": "autenticacao", "matricula": matricula, "senha": senha})

print("Enviando dados de autenticação...")

resposta_servidor = socket.recv_json()
print(f"Resposta do servidor: {resposta_servidor}")

if resposta_servidor["status"] == "ERRO_AUTENTICACAO":
    print("Erro de autenticação. Verifique sua matrícula e senha.")
else:
    print("Autenticado com sucesso. Iniciando o quiz.")
    socket.send_json({"tipo": "resposta"})
    
    while True:
        questao = socket.recv_json()
        if "resultado" in questao:
            print(questao["resultado"])
            break
        else:
            print(questao["questao"]["pergunta"])
            for opcao in questao["questao"]["opcoes"]:
                print(opcao)
            resposta = input("Escolha sua resposta (A, B, C ou D): ")
            print(f"Resposta enviada: {resposta}")
            socket.send_json({"resposta": resposta})
