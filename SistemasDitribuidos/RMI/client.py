import Pyro4
import threading

class ChatClient(object):
    def __init__(self):
        # Conectar ao servidor usando o nome registrado
        self.chat_server = Pyro4.core.Proxy('PYRONAME:server')
        self.abort = 0

    @Pyro4.expose
    @Pyro4.oneway
    def message(self, number_msg, nickname, msg):
        if nickname != self.nickname:
            print('Mensagem {}-[{}] {}'.format(number_msg, nickname, msg))

    def start(self):
        self.nickname = input('Escolha um apelido: ').strip()
        people = self.chat_server.join(self.nickname, self)
        print('Entrou no chat como {}'.format(self.nickname))
        print('Pessoas online: {}'.format(', '.join(people)))
        print('Escreva /sair para sair da conversa.')
        try:
            self.send_action()
        finally:
            self.exit()

    def send_action(self):
        while not self.abort:
            line = input('> ').strip()
            if line == '/sair':
                break
            if line:
                self.chat_server.publish(self.nickname, line)

    def exit(self):
        self.chat_server.exit(self.nickname)
        self.abort = 1
        self._pyroDaemon.shutdown()

class DaemonThread(threading.Thread):
    def __init__(self, chat_client):
        threading.Thread.__init__(self)
        self.chat_client = chat_client
        self.daemon = True

    def run(self):
        with Pyro4.core.Daemon() as daemon:
            daemon.register(self.chat_client)
            daemon.requestLoop(lambda: not self.chat_client.abort)

def main():
    chat_client = ChatClient()
    dt = DaemonThread(chat_client)
    dt.start()
    chat_client.start()
    print('Saiu.')

if __name__ == '__main__':
    main()
