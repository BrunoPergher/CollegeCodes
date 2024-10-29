import random

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

# Hill Climbing com reinicialização aleatória
def hill_climbing_with_restart(iterations, restart_threshold):
    best_salad = []
    best_value = 0

    current_salad = random.sample(ingredients.keys(), random.randint(1, 5))
    current_value = objective_function(current_salad)

    for i in range(iterations):
        # Fazemos uma pequena mudança na salada (adicionar ou remover um ingrediente)
        new_salad = current_salad.copy()

        if len(new_salad) < 5 and random.random() > 0.5:
            new_ingredient = random.choice(list(set(ingredients.keys()) - set(new_salad)))
            new_salad.append(new_ingredient)
        else:
            if new_salad:
                new_salad.remove(random.choice(new_salad))

        new_value = objective_function(new_salad)

        # Se a nova salada for melhor, atualizamos
        if new_value > current_value:
            current_salad = new_salad
            current_value = new_value

        # Se encontramos uma salada melhor que todas até agora, atualizamos o melhor resultado
        if current_value > best_value:
            best_salad = current_salad
            best_value = current_value

        # Reiniciar a busca se não houver melhorias significativas por várias iterações
        if i % restart_threshold == 0:
            current_salad = random.sample(ingredients.keys(), random.randint(1, 5))
            current_value = objective_function(current_salad)

    return best_salad, best_value

# Executar o Hill Climbing com reinicialização aleatória
result_salad, result_value = hill_climbing_with_restart(iterations=100, restart_threshold=100)
print(f"Melhor salada encontrada: {result_salad}, Pontuação: {result_value}")
