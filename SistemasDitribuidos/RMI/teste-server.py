import Pyro4

@Pyro4.expose
class TestServer(object):
    def say_hello(self):
        return "Hello!"

def main():
    daemon = Pyro4.Daemon(host="192.168.0.211")  # Endereço IP do servidor
    uri = daemon.register(TestServer)
    print("Ready. Object uri =", uri)
    daemon.requestLoop()

if __name__ == "__main__":
    main()
