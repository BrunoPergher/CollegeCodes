import Pyro4

@Pyro4.expose
class ChatServer(object):
    def __init__(self):
        self.chats = []
        self.users = {}
        self.max_users = 2

    def register_user(self, nickname):
        if len(self.users) >= self.max_users:
            return False, "Chat já está cheio."
        if nickname in self.users:
            return False, "Este apelido já está em uso."
        self.users[nickname] = []
        return True, f"{nickname} entrou no chat."

    def post_message(self, nickname, message):
        if nickname in self.users:
            full_message = f"{nickname}: {message}"
            print(f"Nova mensagem: {full_message}")
            self.chats.append(full_message)
            return True, "Mensagem enviada."
        return False, "Usuário não autenticado."

    def get_messages(self, nickname):
        if nickname not in self.users:
            return False, "Usuário não autenticado."
        return True, self.chats

def main():
    Pyro4.Daemon.serveSimple(
            {
                ChatServer: "example.chatserver"
            },
            ns=True)

if __name__ == "__main__":
    main()
