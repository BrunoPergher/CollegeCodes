import socket
import json

# Dados dos usuários e questões
usuarios = {"12345": "senha123", "67890": "abcde"}
questoes = [
    {"pergunta": "Qual a capital da França?", "opcoes": ["A) Paris", "B) Londres", "C) Berlim", "D) Madrid"], "correta": "A"},
    {"pergunta": "2 + 2?", "opcoes": ["A) 3", "B) 4", "C) 5", "D) 6"], "correta": "B"}
]

# Configuração inicial do socket
host = '127.0.0.1'
porta = 65432
servidor = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
servidor.bind((host, porta))
servidor.listen()

print(f"Servidor rodando em {host}:{porta}")

while True:
    conexao, endereco = servidor.accept()
    print(f"Conectado por {endereco}")

    try:
        # Autenticação do aluno
        dados_autenticacao = conexao.recv(1024).decode()
        matricula, senha = dados_autenticacao.split(';')
        if matricula in usuarios and usuarios[matricula] == senha:
            conexao.sendall("AUTENTICADO".encode())
        else:
            conexao.sendall("ERRO_AUTENTICACAO".encode())
            conexao.close()
            continue
        
        # Enviando questões
        respostas_corretas = 0
        for questao in questoes:
            msg = json.dumps(questao)
            conexao.sendall(msg.encode())
            resposta = conexao.recv(1024).decode()
            if resposta.upper() == questao["correta"]:
                respostas_corretas += 1

        # Enviando resultado
        resultado = f"Total de questões: {len(questoes)}, Acertos: {respostas_corretas}"
        conexao.sendall(resultado.encode())

    finally:
        conexao.close()
