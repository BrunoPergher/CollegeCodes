import Pyro4

@Pyro4.expose
class ChatServer(object):
    def __init__(self):
        self.chats = []

    def post_message(self, message):
        print(f"Nova mensagem: {message}")
        self.chats.append(message)
        return True

    def get_messages(self):
        return self.chats

def main():
    Pyro4.Daemon.serveSimple(
            {
                ChatServer: "example.chatserver"
            },
            ns=True)

if __name__ == "__main__":
    main()
