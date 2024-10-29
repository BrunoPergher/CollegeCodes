import heapq
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
            'H': ['G', 'I', 'K', 'L'],
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

        # Coordenadas para cada sala (x, y)
        self.coordinates = {
            'A': (0, 0.5),
            'B': (1.5, 0),
            'C': (1.5, 1),
            'D': (3, 0.5),
            'E': (4.5, 0.5),
            'F': (6, 0.5),
            'G': (0.5, 2),
            'H': (2, 2.5),
            'I': (3.5, 2),
            'J': (5.5, 2),
            'K': (0.5, 3),
            'L': (3.5, 3.5),
            'M': (5.5, 3.5),
            'N': (0.5, 4.5),
            'O': (2, 4.5),
            'P': (4.5, 5),
            'Q': (0.5, 6.5),
            'R': (2, 6.5),
            'S': (3, 6.5),
            'T': (4.5, 6.5),
            'U': (6, 6.5)
        }

    def heuristic(self, node, goal):
        """
        Calcula a heurística de Distância de Manhattan entre o nó atual e o nó objetivo.
        """
        x1, y1 = self.coordinates[node]
        x2, y2 = self.coordinates[goal]
        return abs(x1 - x2) + abs(y1 - y2)

    def a_estrela_busca(self, start, goal):
        """
        Realiza a Busca A* do nó inicial ao nó objetivo.
        """
        # Inicializa a fila de prioridade com o nó inicial
        frontier = []
        # (custo estimado total, custo até agora, caminho)
        heapq.heappush(frontier, (self.heuristic(start, goal), 0, [start]))
        visited = set()
        nodes_expanded = 0

        while frontier:
            # Retira o caminho com o menor custo estimado total
            estimated_total_cost, cost_so_far, path = heapq.heappop(frontier)
            node = path[-1]

            if node == goal:
                # Objetivo encontrado; retorna o caminho e o número de nós expandidos
                return path, nodes_expanded

            if node not in visited:
                # Marca o nó como visitado
                visited.add(node)
                nodes_expanded += 1

                # Expande para os nós adjacentes
                for adjacent in self.graph.get(node, []):
                    # Assume que cada movimento tem custo 1
                    new_cost = cost_so_far + 1
                    # Custo estimado total = custo até agora + heurística
                    estimated_cost = new_cost + self.heuristic(adjacent, goal)
                    new_path = list(path)
                    new_path.append(adjacent)
                    # Adiciona o novo caminho à fronteira com seu custo estimado total
                    heapq.heappush(frontier, (estimated_cost, new_cost, new_path))

        # Se o objetivo não for alcançável
        return None, nodes_expanded

# Uso de exemplo
if __name__ == "__main__":
    labyrinth = Labyrinth()

    start_room = 'A'
    goal_room = 'U'

    # Registra o tempo de início
    start_time = time.time()

    # Realiza a Busca A*
    path, nodes_expanded = labyrinth.a_estrela_busca(start_room, goal_room)

    # Registra o tempo de término
    end_time = time.time()
    execution_time = end_time - start_time

    if path:
        print("Caminho encontrado pela Busca A*:")
        print(" -> ".join(path))
        print(f"Total de passos: {len(path) - 1}")
        print(f"Nós expandidos: {nodes_expanded}")
        print(f"Tempo de execução: {execution_time:.6f} segundos")
    else:
        print(f"Nenhum caminho encontrado de {start_room} para {goal_room}")
