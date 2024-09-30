import threading
import time
import random

# Número de filósofos e garfos
NUM_FILOSOFOS = 5

# Criar uma lista de garfos (como locks)
garfos = [threading.Lock() for _ in range(NUM_FILOSOFOS)]

# Semáforo para permitir que no máximo NUM_FILOSOFOS - 1 filósofos tentem comer ao mesmo tempo
sem_filosofos = threading.Semaphore(NUM_FILOSOFOS)

# Variáveis para controlar a fila de prioridade
fila_prioridade = []
lock_fila = threading.Lock()

class Filosofo(threading.Thread):
    def __init__(self, indice, garfo_esquerdo, garfo_direito, tempo_maximo_inanicao):
        threading.Thread.__init__(self)
        self.indice = indice  # Índice do filósofo
        self.garfo_esquerdo = garfo_esquerdo  # Garfo à esquerda
        self.garfo_direito = garfo_direito    # Garfo à direita
        self.tempo_maximo_inanicao = tempo_maximo_inanicao  # Tempo máximo sem comer (20 segundos)
        self.ultimo_tempo_comendo = time.time()  # Momento em que o filósofo comeu pela última vez
        self.daemon = True  # Thread daemon será finalizada quando o programa principal terminar
        self.prioritario = False  # Indica se o filósofo está na fila de prioridade

    def pensar(self):
        """Simula o pensamento."""
        tempo_pensando = random.uniform(1, 5)  # Tempo aleatório entre 1 e 5 segundos
        print(f"Filósofo {self.indice} está pensando por {tempo_pensando:.2f} segundos.")
        time.sleep(tempo_pensando)  # Simula o tempo de pensar

    def ficar_com_fome(self):
        """Filósofo fica com fome."""
        print(f"Filósofo {self.indice} está com fome.")

    def comer(self):
        """Simula o ato de comer."""
        tempo_comendo = random.uniform(1, 10)  # Tempo aleatório entre 1 e 5 segundos
        print(f"Filósofo {self.indice} começa a comer por {tempo_comendo:.2f} segundos.")
        time.sleep(tempo_comendo)  # Simula o tempo de comer
        self.ultimo_tempo_comendo = time.time()  # Atualiza o tempo da última refeição
        print(f"Filósofo {self.indice} termina de comer.")

    def verificar_inanicao(self):
        """Verifica se o filósofo está morrendo de fome."""
        tempo_sem_comer = time.time() - self.ultimo_tempo_comendo

        if tempo_sem_comer > 10 and not self.prioritario:
            # Adiciona o filósofo à fila de prioridade
            with lock_fila:
                if self.indice not in fila_prioridade:
                    fila_prioridade.append(self.indice)
                    self.prioritario = True
                    print(f"Filósofo {self.indice} entrou na fila de prioridade.")

        if tempo_sem_comer > self.tempo_maximo_inanicao:
            print(f"Filósofo {self.indice} faleceu por inanição! Não come há {tempo_sem_comer:.2f} segundos.")
            # Reinicia o estado do filósofo
            self.ultimo_tempo_comendo = time.time()
            self.prioritario = False
            with lock_fila:
                if self.indice in fila_prioridade:
                    fila_prioridade.remove(self.indice)
            print(f"Filósofo {self.indice} foi reiniciado após falecer.")

    def run(self):
        """Loop principal da thread do filósofo."""
        while True:
            self.pensar()             # Filósofo está pensando
            self.ficar_com_fome()     # Filósofo fica com fome

            # Adquire o semáforo antes de tentar pegar os garfos
            sem_filosofos.acquire()
            try:
                while True:
                    self.verificar_inanicao()  # Verifica se está morrendo de fome

                    # Tenta pegar os garfos
                    conseguiu_comer = self.tentar_comer()
                    if conseguiu_comer:
                        break  # Sai do loop após comer
                    else:
                        # Aguarda um pouco antes de tentar novamente
                        time.sleep(random.uniform(0.1, 0.5))
            finally:
                # Libera o semáforo após tentar comer
                sem_filosofos.release()

    def tentar_comer(self):
        """Tenta adquirir os garfos e comer."""
        # Ordem padrão dos garfos
        primeiro_garfo = self.garfo_esquerdo
        segundo_garfo = self.garfo_direito

        if self.prioritario:
            # Filósofo prioritário inverte a ordem dos garfos
            primeiro_garfo, segundo_garfo = segundo_garfo, primeiro_garfo

        # Tenta adquirir os garfos
        pegou_primeiro = primeiro_garfo.acquire(timeout=random.uniform(0.1, 0.5))
        if pegou_primeiro:
            try:
                pegou_segundo = segundo_garfo.acquire(timeout=random.uniform(0.1, 0.5))
                if pegou_segundo:
                    try:
                        self.comer()  # Come quando possui os dois garfos
                        # Remove o filósofo da fila de prioridade se necessário
                        if self.prioritario:
                            with lock_fila:
                                if self.indice in fila_prioridade:
                                    fila_prioridade.remove(self.indice)
                            self.prioritario = False
                        return True
                    finally:
                        segundo_garfo.release()
                else:
                    print(f"Filósofo {self.indice} não conseguiu pegar o segundo garfo.")
            finally:
                primeiro_garfo.release()
        else:
            print(f"Filósofo {self.indice} não conseguiu pegar o primeiro garfo.")
        return False

def main():
    """Configura e inicia as threads dos filósofos."""
    tempo_maximo_inanicao = 20  # Tempo máximo aceitável sem comer (20 segundos)
    filosofos = []

    # Cria e inicia as threads dos filósofos
    for i in range(NUM_FILOSOFOS):
        garfo_esquerdo = garfos[i]
        garfo_direito = garfos[(i + 1) % NUM_FILOSOFOS]
        filosofo = Filosofo(i, garfo_esquerdo, garfo_direito, tempo_maximo_inanicao)
        filosofos.append(filosofo)
        filosofo.start()  # Inicia a thread do filósofo

    # Mantém a thread principal viva para permitir que as threads dos filósofos continuem rodando
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("Simulação finalizada.")

if __name__ == "__main__":
    main()
