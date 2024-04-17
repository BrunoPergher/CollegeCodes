from subprocess import call

# Especifica o endereço IP para o servidor de nomes
call('python -m Pyro4.naming --host 192.168.0.211', shell=True)
