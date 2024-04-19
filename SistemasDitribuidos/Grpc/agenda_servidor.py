import logging
import sys
from concurrent import futures
import grpc
import agenda_pb2
import agenda_pb2_grpc

class Agenda(agenda_pb2_grpc.AgendaServicer):
    def __init__(self) -> None:
    # banco de dados será uma lista em memória
        self.database = []
        
    def duplicado(self,id) -> agenda_pb2.Pessoa:
        for pessoa in self.database:
            if pessoa.id == id:
                return pessoa
        return agenda_pb2.Pessoa(id=-1)
    
    # método que poderá ser invocado pelo cliente
    def adicionar(self, request, context):
    # Verificando se id já está no banco
        pessoa = self.duplicado(request.id)
        if pessoa.id == -1:
            self.database.append(request)
            mensagem = f'contato ({request.id}, {request.nome}) adicionado com sucesso'
            return agenda_pb2.Resposta(resultado=mensagem)
        else:
            mensagem = 'id já existe no banco de dados'
            logging.debug(mensagem)
            return agenda_pb2.Resposta(resultado=mensagem)


# método que poderá ser invocado pelo cliente
    def buscar(self, request, context):
        pessoa = self.duplicado(request.id)
        if pessoa.id == -1:
            return agenda_pb2.Pessoa(encontrado=False)  # Pessoa não encontrada
        pessoa.encontrado = True
        return pessoa

    
if __name__ == "__main__":
    logging.basicConfig(format='%(asctime)s -> %(message)s',stream=sys.stdout, level=logging.DEBUG)
    
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    
    agenda_pb2_grpc.add_AgendaServicer_to_server(Agenda(), server)
    
    server.add_insecure_port('[::]:50051')
    server.start()
    server.wait_for_termination()
