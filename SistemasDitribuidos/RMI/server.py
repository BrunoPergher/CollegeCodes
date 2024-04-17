import Pyro4

@Pyro4.expose
class ChatServer(object):
    def __init__(self):
        self.users = []
        self.nicknames = []
        self.count = 0

    def join(self, nickname, callback):
        self.valid_nickname(nickname)
        self.users.append((nickname, callback))
        self.nicknames.append(nickname)
        callback._pyroOneway.add('jobdone')
        print('{} Entrou'.format(nickname))
        self.publish('SERVER', '** {} Entrou **'.format(nickname))
        return [n for (n, c) in self.users]

    def valid_nickname(self, nickname):
        if not nickname: raise ValueError('Escolha um apelido')
        if nickname in self.nicknames: raise ValueError('Apelido está em uso')

    def exit(self, nickname):
        for(nick, callback) in self.users:
            if nick == nickname:
                self.users.remove((nick, callback))
                break
        self.publish('SERVER', '** {} saiu **'.format(nickname))
        self.nicknames.remove(nickname)
        print('{} Saiu'.format(nickname))

    def publish(self, nickname, msg):
        self.count += 1
        for(nick, callback) in self.users[:]:
            try:
                callback.message(self.count, nickname, msg)
            except Pyro4.errors.ConnectionClosedError:
                if(nick, callback) in self.users:
                    self.users.remove((nick, callback))
                    print('Removido por erro %s %s' % (nick, callback))

def main():
    # Configurando para aceitar conexões na rede
    daemon = Pyro4.Daemon(host="192.168.0.211")
    ns = Pyro4.locateNS(host="192.168.0.211")
    uri = daemon.register(ChatServer)
    ns.register("server", uri)
    print("Ready. Object uri =", uri)
    print('Chat server começou')
    daemon.requestLoop()

if __name__ == '__main__':
    main()
