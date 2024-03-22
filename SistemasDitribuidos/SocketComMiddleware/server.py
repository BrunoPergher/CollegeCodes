import zmq
import json

context = zmq.Context()
socket = context.socket(zmq.REP)  # REP (Reply) socket
socket.bind("tcp://*:5555")

print("Servidor iniciado. Aguardando conexões...")

usuarios = {"12345": "senha123", "67890": "abcde"}
questoes = [
    {"pergunta": "Qual a capital da França?", "opcoes": ["A) Paris", "B) Londres", "C) Berlim", "D) Madrid"], "correta": "A"},
    {"pergunta": "2 + 2?", "opcoes": ["A) 3", "B) 4", "C) 5", "D) 6"], "correta": "B"}
]

while True:
    mensagem = socket.recv_json()
    print(f"Mensagem recebida: {mensagem}")

    if mensagem['tipo'] == 'autenticacao':
        matricula = mensagem['matricula']
        senha = mensagem['senha']
        
        if matricula in usuarios and usuarios[matricula] == senha:
            print(f"Usuário {matricula} autenticado com sucesso.")
            socket.send_json({"status": "AUTENTICADO"})
        else:
            print(f"Erro de autenticação para o usuário {matricula}.")
            socket.send_json({"status": "ERRO_AUTENTICACAO"})
            continue
    elif mensagem['tipo'] == 'resposta':
        respostas_corretas = 0
        for questao in questoes:
            socket.send_json({"questao": questao})
            print(f"Enviada questão: {questao['pergunta']}")
            resposta = socket.recv_json()
            if resposta['resposta'].upper() == questao["correta"]:
                respostas_corretas += 1
        
        # Envia o resultado final
        resultado = f"Total de questões: {len(questoes)}, Acertos: {respostas_corretas}"
        print(f"Resultado final enviado para o usuário {matricula}: {resultado}")
        socket.send_json({"resultado": resultado})
