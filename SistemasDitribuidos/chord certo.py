import hashlib

class ChordNode:
    def __init__(self, identifier):
        self.id = self.hash_function(identifier)
        self.resources = {}
        self.next = None
        self.active = True

    @staticmethod
    def hash_function(key):
        # Função de hash para calcular o hash de uma chave usando SHA-1 e limitando o resultado a 256 bits. errado
        return int(hashlib.sha1(key.encode()).hexdigest(), 16) % 256

    def add_resource(self, key, value):
        self.resources[key] = value

    def remove_resource(self, key):
        return self.resources.pop(key, None)

    def print_details(self):
        if self.active:
            print(f"Active Node ID: {self.id}, Resources: {list(self.resources.keys())}")

class ChordRing:
    def __init__(self):
        self.first_node = None
        self.backup_resources = {}

    def add_node(self, identifier):
        new_node = ChordNode(identifier)
        if not self.first_node:
            self.first_node = new_node
            self.first_node.next = self.first_node
        else:
            current = self.first_node
            prev = None
            while current != self.first_node or prev is None:
                if new_node.id < current.id:
                    break
                prev = current
                current = current.next
            new_node.next = current
            if prev:
                prev.next = new_node
            if new_node.id < self.first_node.id:
                self.first_node = new_node

    def add_resource(self, key, value):
        resource_id = ChordNode.hash_function(key)
        current = self.first_node
        if not current:
            print("No nodes in the Chord ring to add the resource to.")
            return
        
        # Encontrar o nó adequado com base no hash do recurso
        while True:
            if current.id >= resource_id or current.next.id < resource_id or current.next == self.first_node:
                if current.active:
                    current.add_resource(key, value)
                    print(f"Resource '{key}' added to Node ID: {current.id}")
                else:
                    # Se o nó adequado estiver inativo, procurar o próximo nó ativo
                    next_active = current.next
                    while not next_active.active:
                        next_active = next_active.next
                        if next_active == self.first_node:
                            print("No active nodes available to add the resource.")
                            return
                    next_active.add_resource(key, value)
                    print(f"Resource '{key}' added to Node ID: {next_active.id} (active node)")
                break
            current = current.next
            if current == self.first_node:
                # Se o loop completou uma volta completa sem encontrar um nó adequado, significa que não há nós ativos
                print("No active nodes available to add the resource.")
                break

    def disable_node(self, identifier):
        node_id = ChordNode.hash_function(identifier)
        current = self.first_node
        while current:
            if current.id == node_id:
                current.active = False
                # Backup
                for key, value in current.resources.items():
                    self.backup_resources[key] = (value, current)
                # next active node
                next_active = current.next
                while not next_active.active:
                    next_active = next_active.next
                # Transfer resources
                for key, value in current.resources.items():
                    next_active.add_resource(key, value)
                current.resources.clear()
                break
            current = current.next
            if current == self.first_node:
                break

    def enable_node(self, identifier):
        node_id = ChordNode.hash_function(identifier)
        current = self.first_node
        while current:
            if current.id == node_id and not current.active:
                current.active = True
                # Restore resources backup
                for key, (value, original_node) in list(self.backup_resources.items()):
                  if original_node.id == current.id:
                      current.add_resource(key, value)
                      del self.backup_resources[key]
                      # Remove resource to the old node
                      temp_holder = current.next
                      while temp_holder.id != original_node.id:
                          if key in temp_holder.resources:
                              temp_holder.remove_resource(key)
                              break
                          temp_holder = temp_holder.next
                break
            current = current.next
            if current == self.first_node:
                break

    def print_ring(self):
        current = self.first_node
        if current:
            while True:
                if current.active:
                    current.print_details()
                current = current.next
                if current == self.first_node:
                    break

if __name__ == "__main__":
    chord_ring = ChordRing()

    # Adicionando nós ao anel Chord
    chord_ring.add_node("Node1")
    chord_ring.add_node("Node2")
    chord_ring.add_node("Node3")

    print("Estado inicial:")
    chord_ring.print_ring()

    # Adicionando recursos que serão alocados com base em seus hashes
    chord_ring.add_resource("Resource1", "Data for Resource1")
    chord_ring.add_resource("Resource2", "Data for Resource2")
    chord_ring.add_resource("Resource3", "Data for Resource3")
    chord_ring.add_resource("Resource4", "Data for Resource4")
    chord_ring.add_resource("Resource5", "Data for Resource5")
    chord_ring.add_resource("Resource6", "Data for Resource6")
    chord_ring.add_resource("Resource7", "Data for Resource7")
    chord_ring.add_resource("Resource8", "Data for Resource8")
    chord_ring.add_resource("Resource9", "Data for Resource9")
    chord_ring.add_resource("Resource10", "Data for Resource10")
    chord_ring.add_resource("Resource100", "Data for Resource100")
    chord_ring.add_resource("Resource150", "Data for Resource150")
    chord_ring.add_resource("Resource777", "Data for Resource777")


    print("\nApós adicionar recursos:")
    chord_ring.print_ring()

    chord_ring.disable_node("Node3")
    print("\nAfter disabling Node2:")
    chord_ring.print_ring()

    chord_ring.enable_node("Node3")
    print("\nAfter re-enabling Node2:")
    chord_ring.print_ring()

