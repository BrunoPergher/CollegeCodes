import Pyro4

@Pyro4.expose
class ChatClient(object):
    def __init__(self, server):
        self.server = server

    def send_message(self, message):
        if self.server.post_message(message):
            print("Mensagem enviada com sucesso.")
        else:
            print("Falha ao enviar a mensagem.")

    def fetch_messages(self):
        return self.server.get_messages()

def main():
    uri = input("Digite a URI do servidor de chat (ex: PYRONAME:example.chatserver): ")
    chat_server = Pyro4.Proxy(uri)

    client = ChatClient(chat_server)

    while True:
        msg = input("Escreva uma mensagem (ou 'exit' para sair): ")
        if msg == "exit":
            break
        client.send_message(msg)
        print("Mensagens no chat:")
        for message in client.fetch_messages():
            print(message)

if __name__ == "__main__":
    main()
