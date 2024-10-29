from collections import deque
import time

class Labyrinth:
    def __init__(self):
        # Representação do labirinto como um grafo (lista de adjacência)
        self.graph = {
            'A': ['C'],
            'B': ['C', 'D'],
            'C': ['A', 'B', 'G'],
            'D': ['B', 'E'],
            'E': ['D', 'F'],
            'F': ['E', 'J'],
            'G': ['C', 'H', 'K'],
            'H': ['G', 'K', 'I', 'L'],
            'I': ['H', 'J'],
            'J': ['F', 'I', 'M'],
            'K': ['G', 'H', 'N'],
            'L': ['H', 'M'],
            'M': ['J', 'L', 'P'],
            'N': ['K', 'O', 'Q'],
            'O': ['N', 'P'],
            'P': ['M', 'O', 'T'],
            'Q': ['N', 'R'],
            'R': ['Q', 'S'],
            'S': ['R', 'T'],
            'T': ['P', 'S', 'U'],
            'U': ['T']
        }

    def bfs(self, start, goal):
        # Inicializa a fila com o nó inicial e o conjunto de visitados
        queue = deque([[start]])
        visited = set()
        nodes_expanded = 0

        while queue:
            # Remove o próximo caminho da fila
            path = queue.popleft()
            node = path[-1]

            if node == goal:
                # Objetivo encontrado
                return path, nodes_expanded

            elif node not in visited:
                # Marca o nó como visitado
                visited.add(node)
                nodes_expanded += 1

                # Enfileira caminhos para todos os nós adjacentes não visitados
                for adjacent in self.graph.get(node, []):
                    if adjacent not in visited:
                        new_path = list(path)
                        new_path.append(adjacent)
                        queue.append(new_path)

        # Se o objetivo não for alcançável
        return None, nodes_expanded

# Uso de exemplo
if __name__ == "__main__":
    labyrinth = Labyrinth()

    start_room = 'A'
    goal_room = 'U'

    # Registra o tempo de início
    start_time = time.time()

    # Executa a busca em largura
    path, nodes_expanded = labyrinth.bfs(start_room, goal_room)

    # Registra o tempo de término
    end_time = time.time()
    execution_time = end_time - start_time

    if path:
        print("Caminho encontrado pela Busca em Largura:")
        print(" -> ".join(path))
        print(f"Total de passos: {len(path) - 1}")
        print(f"Nós expandidos: {nodes_expanded}")
        print(f"Tempo de execução: {execution_time:.6f} segundos")
    else:
        print(f"Nenhum caminho encontrado de {start_room} para {goal_room}")
