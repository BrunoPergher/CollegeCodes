import random
import numpy as np

# Definição das constantes do problema
COMPARTIMENTOS = {
    'D': {'volume': 6800, 'peso': 10},  # Compartimento Dianteiro
    'C': {'volume': 8700, 'peso': 16},  # Compartimento Central
    'T': {'volume': 5300, 'peso': 8}    # Compartimento Traseiro
}

CARGAS = {
    'C1': {'volume': 480, 'peso': 18, 'lucro': 310},  # Carga 1
    'C2': {'volume': 650, 'peso': 15, 'lucro': 380},  # Carga 2
    'C3': {'volume': 580, 'peso': 23, 'lucro': 350},  # Carga 3
    'C4': {'volume': 390, 'peso': 12, 'lucro': 285}   # Carga 4
}

compartimentos = list(COMPARTIMENTOS.keys())

# Parâmetros do algoritmo genético
TAMANHO_POPULACAO = 600
GERACOES = 2500
TAXA_MUTACAO = 0.2
TAXA_CROSSOVER = 0.8

def criar_individuo():
    """Cria um indivíduo viável respeitando todas as restrições."""
    individuo = np.zeros((4, 3), dtype=float)
    
    # Disponibilidade das cargas
    peso_disponivel_cargas = {i: CARGAS[f'C{i+1}']['peso'] for i in range(4)}
    
    # Capacidade dos compartimentos
    capacidade_peso_compartimentos = [COMPARTIMENTOS[comp]['peso'] for comp in compartimentos]
    capacidade_volume_compartimentos = [COMPARTIMENTOS[comp]['volume'] for comp in compartimentos]
    
    # Proporção de peso em cada compartimento (baseado na proporção de volumes)
    proporcao_volumes = np.array(capacidade_volume_compartimentos, dtype=float)
    proporcao_volumes /= proporcao_volumes.sum()
    capacidade_peso_total = sum(capacidade_peso_compartimentos)
    peso_compartimentos = proporcao_volumes * capacidade_peso_total
    
    # Distribuir as cargas nos compartimentos
    for i in range(4):
        carga = CARGAS[f'C{i+1}']
        peso_restante_carga = carga['peso']
        for j in range(3):
            # Determinar o peso máximo que pode ser alocado
            peso_maximo_carga = min(peso_restante_carga, peso_compartimentos[j])
            peso_maximo_compartimento = COMPARTIMENTOS[compartimentos[j]]['peso'] - np.sum(individuo[:, j])
            volume_maximo_compartimento = COMPARTIMENTOS[compartimentos[j]]['volume'] - np.sum(individuo[:, j] * [CARGAS[f'C{k+1}']['volume'] for k in range(4)])
            volume_carga = carga['volume']
            peso_maximo_volume = volume_maximo_compartimento / volume_carga if volume_carga > 0 else 0
            peso_maximo = min(peso_maximo_carga, peso_maximo_compartimento, peso_maximo_volume)
            if peso_maximo <= 0:
                continue
            # Gerar um peso aleatório entre 0 e peso máximo
            peso_alocado = np.random.uniform(0, peso_maximo)
            individuo[i][j] += peso_alocado
            peso_restante_carga -= peso_alocado
            peso_compartimentos[j] -= peso_alocado
            if peso_restante_carga <= 0:
                break
    # Ajustar para manter o equilíbrio do avião
    individuo = ajustar_individuo(individuo)
    
    return individuo

def ajustar_equilibrio(individuo):
    """Ajusta o indivíduo para manter o equilíbrio do avião, respeitando as capacidades."""
    peso_compartimentos = np.sum(individuo, axis=0)
    peso_total = np.sum(peso_compartimentos)
    proporcao_volumes = np.array([comp['volume'] for comp in COMPARTIMENTOS.values()], dtype=float)
    proporcao_volumes /= proporcao_volumes.sum()
    peso_desejado = proporcao_volumes * peso_total

    # Ajustar pesos nos compartimentos
    for j in range(3):
        diferenca = peso_desejado[j] - peso_compartimentos[j]
        if diferenca > 0:
            # Aumentar peso no compartimento
            capacidade_peso_restante = COMPARTIMENTOS[compartimentos[j]]['peso'] - peso_compartimentos[j]
            diferenca = min(diferenca, capacidade_peso_restante)
            if diferenca <= 0:
                continue
            for i in range(4):
                carga = CARGAS[f'C{i+1}']
                peso_disponivel_carga = carga['peso'] - np.sum(individuo[i])
                capacidade_volume_restante = COMPARTIMENTOS[compartimentos[j]]['volume'] - np.sum(individuo[:, j] * [CARGAS[f'C{k+1}']['volume'] for k in range(4)])
                volume_carga = carga['volume']
                peso_maximo_volume = capacidade_volume_restante / volume_carga if volume_carga > 0 else 0
                aumento_max = min(diferenca, peso_disponivel_carga, capacidade_peso_restante, peso_maximo_volume)
                if aumento_max <= 0:
                    continue
                individuo[i][j] += aumento_max
                diferenca -= aumento_max
                peso_compartimentos[j] += aumento_max
                if diferenca <= 0:
                    break
        elif diferenca < 0:
            # Reduzir peso no compartimento
            diferenca = -diferenca
            for i in range(4):
                reducao_max = min(individuo[i][j], diferenca)
                individuo[i][j] -= reducao_max
                diferenca -= reducao_max
                peso_compartimentos[j] -= reducao_max
                if diferenca <= 0:
                    break
    return individuo

def ajustar_individuo(individuo):
    """Ajusta o indivíduo para que respeite as restrições."""
    # Garantir que o peso total de cada carga não exceda sua disponibilidade
    for i in range(4):
        peso_total_carga = np.sum(individuo[i])
        carga_max = CARGAS[f'C{i+1}']['peso']
        if peso_total_carga > carga_max:
            # Reduzir proporcionalmente
            fator = carga_max / peso_total_carga
            individuo[i] *= fator

    # Ajustar para manter o equilíbrio do avião, respeitando capacidades
    individuo = ajustar_equilibrio(individuo)

    # Garantir que o peso e volume nos compartimentos não excedam suas capacidades
    for j in range(3):
        peso_total_comp = np.sum(individuo[:, j])
        peso_max = COMPARTIMENTOS[compartimentos[j]]['peso']
        if peso_total_comp > peso_max:
            # Reduzir proporcionalmente
            fator = peso_max / peso_total_comp
            individuo[:, j] *= fator

        # Verificar o volume
        volume_total_comp = 0
        for i in range(4):
            volume_total_comp += individuo[i][j] * CARGAS[f'C{i+1}']['volume']
        volume_max = COMPARTIMENTOS[compartimentos[j]]['volume']
        if volume_total_comp > volume_max:
            # Reduzir proporcionalmente
            fator = volume_max / volume_total_comp
            individuo[:, j] *= fator

    return individuo

def calcular_fitness(individuo):
    """Calcula o lucro total do indivíduo."""
    lucro_total = 0
    peso_cargas = np.sum(individuo, axis=1)
    for i, carga in enumerate(CARGAS.values()):
        lucro_por_tonelada = carga['lucro']
        peso_total_carga = peso_cargas[i]
        lucro_total += lucro_por_tonelada * peso_total_carga
    return lucro_total

def selecionar_pais(populacao, aptidoes):
    """Seleciona dois pais usando seleção por torneio."""
    tamanho_torneio = 5
    pais = []
    for _ in range(2):
        competidores = random.sample(list(zip(populacao, aptidoes)), tamanho_torneio)
        competidores.sort(key=lambda x: x[1], reverse=True)
        pais.append(competidores[0][0])
    return pais[0], pais[1]

def cruzamento(pai1, pai2):
    """Realiza o cruzamento mantendo a viabilidade dos indivíduos."""
    if np.random.rand() < TAXA_CROSSOVER:
        ponto_corte = np.random.randint(1, pai1.size)
        pai1_flat = pai1.flatten()
        pai2_flat = pai2.flatten()

        filho1_flat = np.concatenate([pai1_flat[:ponto_corte], pai2_flat[ponto_corte:]])
        filho2_flat = np.concatenate([pai2_flat[:ponto_corte], pai1_flat[ponto_corte:]])

        filho1 = filho1_flat.reshape(pai1.shape)
        filho2 = filho2_flat.reshape(pai1.shape)

        # Ajustar os filhos para que sejam viáveis
        filho1 = ajustar_individuo(filho1)
        filho2 = ajustar_individuo(filho2)
    else:
        filho1 = pai1.copy()
        filho2 = pai2.copy()

    return filho1, filho2

def mutacao(individuo):
    """Aplica mutação ao indivíduo e ajusta para manter a viabilidade."""
    for i in range(individuo.shape[0]):
        for j in range(individuo.shape[1]):
            if np.random.rand() < TAXA_MUTACAO:
                perturbacao = np.random.uniform(-2, 2)
                individuo[i][j] += perturbacao
                individuo[i][j] = max(individuo[i][j], 0)
    # Ajustar o indivíduo para garantir viabilidade
    individuo = ajustar_individuo(individuo)
    return individuo

def algoritmo_genetico():
    """Executa o algoritmo genético para resolver o problema."""
    populacao = [criar_individuo() for _ in range(TAMANHO_POPULACAO)]
    melhor_aptidao = float('-inf')
    melhor_individuo = None

    for geracao in range(GERACOES):
        aptidoes = [calcular_fitness(ind) for ind in populacao]

        # Atualiza o melhor indivíduo
        aptidao_maxima = max(aptidoes)
        if aptidao_maxima > melhor_aptidao:
            melhor_aptidao = aptidao_maxima
            melhor_individuo = populacao[np.argmax(aptidoes)]

        # Nova população
        nova_populacao = []

        # Elitismo: Mantém os 5% melhores indivíduos
        elite_size = int(0.05 * TAMANHO_POPULACAO)
        populacao_ordenada = [x for _, x in sorted(zip(aptidoes, populacao), key=lambda pair: pair[0], reverse=True)]
        elite = populacao_ordenada[:elite_size]
        nova_populacao.extend(elite)

        while len(nova_populacao) < TAMANHO_POPULACAO:
            pai1, pai2 = selecionar_pais(populacao, aptidoes)
            filho1, filho2 = cruzamento(pai1, pai2)
            filho1 = mutacao(filho1)
            filho2 = mutacao(filho2)
            nova_populacao.extend([filho1, filho2])

        populacao = nova_populacao[:TAMANHO_POPULACAO]

        # Exibir progresso
        if (geracao + 1) % 100 == 0:
            print(f"Geração {geracao + 1}: Melhor Aptidão = {melhor_aptidao:.2f}")

    return melhor_individuo, melhor_aptidao

# Executa o algoritmo genético
melhor_individuo, melhor_aptidao = algoritmo_genetico()

# Exibe os resultados
print("\nMelhor Solução Encontrada:")
print("Aptidão:", melhor_aptidao)

cargas = list(CARGAS.keys())
compartimentos = list(COMPARTIMENTOS.keys())

for i, carga in enumerate(cargas):
    for j, compartimento in enumerate(compartimentos):
        peso = melhor_individuo[i][j]
        if peso > 0:
            print(f"Carga {carga} no Compartimento {compartimento}: {peso:.2f} toneladas")
