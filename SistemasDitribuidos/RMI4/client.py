import Pyro4
import threading

@Pyro4.expose
class ChatClient(object):
    def __init__(self, server):
        self.server = server

    def register(self, nickname):
        daemon = Pyro4.Daemon()  # Inicia um Daemon para este cliente
        callback_uri = daemon.register(self)  # Registra este cliente como um objeto Pyro
        threading.Thread(target=daemon.requestLoop).start()  # Inicia o loop de request em uma thread separada
        success, response = self.server.register_user(nickname, callback_uri)  # Passa a URI do callback para o servidor
        return success, response

    def send_message(self, nickname, message):
        success, response = self.server.post_message(nickname, message)
        return success, response

    def handle_message(self, message):
        print(f"\nNova mensagem: {message}")

def main():
    uri = input("Digite a URI do servidor de chat (ex: PYRONAME:example.chatserver): ")
    chat_server = Pyro4.Proxy(uri)
    client = ChatClient(chat_server)

    nickname = input("Digite seu apelido para o chat: ")
    success, response = client.register(nickname)
    print(response)
    if not success:
        return

    while True:
        msg = input("Escreva uma mensagem (ou 'exit' para sair): ")
        if msg == "exit":
            break
        success, response = client.send_message(nickname, msg)
        if not success:
            print(response)

if __name__ == "__main__":
    main()
