import Pyro4

@Pyro4.expose
class ChatClient(object):
    def __init__(self, server):
        self.server = server

    def register(self, nickname):
        success, response = self.server.register_user(nickname)
        return success, response

    def send_message(self, nickname, message):
        success, response = self.server.post_message(nickname, message)
        return success, response

    def fetch_messages(self, nickname):
        success, messages = self.server.get_messages(nickname)
        return success, messages

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
        print(response)
        if success:
            print("Mensagens no chat:")
            success, messages = client.fetch_messages(nickname)
            for message in messages:
                print(message)

if __name__ == "__main__":
    main()
