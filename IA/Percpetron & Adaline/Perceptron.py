import numpy as np
import matplotlib.pyplot as plt

# Função de ativação (step function)
def step_function(x):
    return 1 if x >= 0 else 0

# Função do Perceptron
def perceptron_train(inputs, labels, eta=0.1, epochs=10):
    weights = np.zeros(inputs.shape[1])
    bias = 0
    errors = []

    # Treinamento por número de épocas
    for epoch in range(epochs):
        total_error = 0
        for x, label in zip(inputs, labels):
            # Previsão
            linear_output = np.dot(x, weights) + bias
            y_pred = step_function(linear_output)

            # Atualização dos pesos e do bias
            error = label - y_pred
            weights += eta * error * x
            bias += eta * error

            # Soma do erro absoluto para esta época
            total_error += abs(error)

        errors.append(total_error)

    return weights, bias, errors

# Tabelas Verdade para AND, OR e XOR
inputs = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
labels_and = np.array([0, 0, 0, 1])  # AND
labels_or = np.array([0, 1, 1, 1])   # OR
labels_xor = np.array([0, 1, 1, 0])  # XOR

# Treinamento do Perceptron para cada tabela
weights_and, bias_and, errors_and = perceptron_train(inputs, labels_and)
weights_or, bias_or, errors_or = perceptron_train(inputs, labels_or)
weights_xor, bias_xor, errors_xor = perceptron_train(inputs, labels_xor)

# Gráficos de evolução do erro
plt.figure(figsize=(12, 4))
plt.subplot(1, 3, 1)
plt.plot(errors_and, marker='o', label='AND')
plt.title('Evolução do Erro - AND')
plt.xlabel('Iterações')
plt.ylabel('Erro')
plt.grid(True)

plt.subplot(1, 3, 2)
plt.plot(errors_or, marker='o', label='OR', color='green')
plt.title('Evolução do Erro - OR')
plt.xlabel('Iterações')
plt.ylabel('Erro')
plt.grid(True)

plt.subplot(1, 3, 3)
plt.plot(errors_xor, marker='o', label='XOR', color='red')
plt.title('Evolução do Erro - XOR')
plt.xlabel('Iterações')
plt.ylabel('Erro')
plt.grid(True)

plt.tight_layout()
plt.show()
