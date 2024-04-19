import logging
import sys
import grpc
import agenda_pb2
import agenda_pb2_grpc

if __name__ == "__main__":
    logging.basicConfig(format='%(asctime)s -> %(message)s',stream=sys.stdout, level=logging.DEBUG)
    joao = agenda_pb2.Pessoa() # criando uma pessoa
    joao.id = 1
    joao.nome = 'Joao'
    joao.email = 'joaoo@email.com'
    telefone = joao.telefones.add()
    telefone.numero = '(48) 3381-23800'
    telefone.tipo = 2
    
    # conectando na porta 50051 da máquina que tem o nome 'servidor'
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = agenda_pb2_grpc.AgendaStub(channel)
    # adicionando um contato
        resposta = stub.adicionar(joao)
        logging.debug(f'Resposta: {resposta.resultado}')
        # buscando pelo ID de um contato
        resposta = stub.buscar(agenda_pb2.Pessoa(id=1))
        if resposta.id != -1:
            logging.debug(f'id: {resposta.id}, nome: {resposta.nome}, telefones: {resposta.telefones}')
        else:
            logging.debug(f'contato não encontrado')
