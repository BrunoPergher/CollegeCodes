import random
import math

# Ingredientes e suas pontuações
ingredients = {
    "Alface": 3,
    "Tomate": 5,
    "Cenoura": 4,
    "Pepino": 2,
    "Abacate": 8,
    "Cebola": 1,
    "Queijo": 7,
    "Frango": 6,
    "Milho": 4,
    "Beterraba": 3,
    "Ovo": 5,
    "Azeitona": 4
}

# Função que avalia a salada
def objective_function(salad):
    return sum(ingredients[ingredient] for ingredient in salad)

# Função que implementa o Simulated Annealing
def simulated_annealing(iterations, initial_temp, cooling_rate):
    # Começamos com uma combinação aleatória de até 5 ingredientes
    current_salad = random.sample(ingredients.keys(), random.randint(1, 5))
    current_value = objective_function(current_salad)

    # Inicializamos a melhor solução como a solução atual
    best_salad = current_salad
    best_value = current_value

    temperature = initial_temp

    for i in range(iterations):
        # Gera uma nova solução (adicionar ou remover um ingrediente aleatoriamente)
        new_salad = current_salad.copy()

        if len(new_salad) < 5 and random.random() > 0.5:
            new_ingredient = random.choice(list(set(ingredients.keys()) - set(new_salad)))
            new_salad.append(new_ingredient)
        else:
            if new_salad:
                new_salad.remove(random.choice(new_salad))

        # Avalia a nova solução
        new_value = objective_function(new_salad)

        # Calcula a mudança de valor
        delta_value = new_value - current_value

        # Se a nova solução for melhor, ou se aceitarmos a pior solução com base na temperatura
        if delta_value > 0 or random.random() < math.exp(delta_value / temperature):
            current_salad = new_salad
            current_value = new_value

        # Atualiza a melhor solução encontrada
        if current_value > best_value:
            best_salad = current_salad
            best_value = current_value

        # Diminui a temperatura
        temperature *= cooling_rate

    return best_salad, best_value

# Executar o Simulated Annealing
result_salad, result_value = simulated_annealing(iterations=100, initial_temp=100, cooling_rate=0.99)
print(f"Melhor salada encontrada: {result_salad}, Pontuação: {result_value}")
