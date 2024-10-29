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
    # A função retorna a soma das pontuações dos ingredientes escolhidos
    return sum(ingredients[ingredient] for ingredient in salad)

# Busca Aleatória com um limite de 5 ingredientes
def random_search(iterations):
    best_salad = []
    best_value = 0

    for i in range(iterations):
        # Gera uma nova combinação de ingredientes aleatória com no máximo 5 ingredientes
        num_ingredients = random.randint(1, 5)
        candidate_salad = random.sample(ingredients.keys(), num_ingredients)
        candidate_value = objective_function(candidate_salad)

        # Se a nova salada for melhor, atualizamos o melhor valor
        if candidate_value > best_value:
            best_salad = candidate_salad
            best_value = candidate_value

    return best_salad, best_value

# Executar a busca aleatória
result_salad, result_value = random_search(iterations=5)
print(f"Melhor salada encontrada: {result_salad}, Pontuação: {result_value}")
