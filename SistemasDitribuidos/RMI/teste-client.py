import Pyro4

def main():
    uri = input("Enter the URI of the server object: ")
    test_server = Pyro4.Proxy(uri)
    print(test_server.say_hello())

if __name__ == "__main__":
    main()
