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

    def dfs(self, start, goal):
        # Inicializa a pilha com o nó inicial e o conjunto de visitados
        stack = [[start]]
        visited = set()
        nodes_expanded = 0

        while stack:
            # Retira o próximo caminho da pilha (último inserido)
            path = stack.pop()
            node = path[-1]

            if node == goal:
                # Objetivo encontrado; retorna o caminho e o número de nós expandidos
                return path, nodes_expanded

            if node not in visited:
                # Marca o nó como visitado
                visited.add(node)
                nodes_expanded += 1

                # Empilha caminhos para todos os nós adjacentes não visitados
                # Usamos reversed para manter a ordem de inserção consistente
                for adjacent in reversed(self.graph.get(node, [])):
                    if adjacent not in visited:
                        new_path = list(path)
                        new_path.append(adjacent)
                        stack.append(new_path)

        # Se o objetivo não for alcançável
        return None, nodes_expanded

# Uso de exemplo
if __name__ == "__main__":
    labyrinth = Labyrinth()

    start_room = 'A'
    goal_room = 'U'

    # Registra o tempo de início
    start_time = time.time()

    # Executa a busca em profundidade
    path, nodes_expanded = labyrinth.dfs(start_room, goal_room)

    # Registra o tempo de término
    end_time = time.time()
    execution_time = end_time - start_time

    if path:
        print("Caminho encontrado pela Busca em Profundidade:")
        print(" -> ".join(path))
        print(f"Total de passos: {len(path) - 1}")
        print(f"Nós expandidos: {nodes_expanded}")
        print(f"Tempo de execução: {execution_time:.6f} segundos")
    else:
        print(f"Nenhum caminho encontrado de {start_room} para {goal_room}")
