import Pyro4

@Pyro4.expose
class ChatServer(object):
    def __init__(self):
        self.chats = []
        self.users = {}
        self.client_callbacks = {}
        self.max_users = 2

    def register_user(self, nickname, client_callback):
        if len(self.users) >= self.max_users:
            return False, "Chat já está cheio."
        if nickname in self.users:
            return False, "Este apelido já está em uso."
        self.users[nickname] = []
        self.client_callbacks[nickname] = client_callback
        self.update_clients(f"{nickname} entrou no chat.")
        return True, f"Bem-vindo ao chat, {nickname}."

    def post_message(self, nickname, message):
        if nickname in self.users:
            full_message = f"{nickname}: {message}"
            self.chats.append(full_message)
            self.update_clients(full_message)
            return True, "Mensagem enviada."
        return False, "Usuário não autenticado."

    def update_clients(self, message):
        for callback in self.client_callbacks.values():
            callback(message)  # Enviar atualizações para todos os clientes registrados

def main():
    Pyro4.Daemon.serveSimple(
            {
                ChatServer: "example.chatserver"
            },
            ns=True)

if __name__ == "__main__":
    main()
