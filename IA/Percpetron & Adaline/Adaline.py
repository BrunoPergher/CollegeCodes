import numpy as np
import matplotlib.pyplot as plt

# Redefinindo as entradas e tabelas verdade
inputs = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
labels_and = np.array([0, 0, 0, 1])  # AND
labels_or = np.array([0, 1, 1, 1])   # OR
labels_xor = np.array([0, 1, 1, 0])  # XOR

# Função de treinamento do ADALINE
def adaline_train(inputs, labels, eta=0.1, epochs=10):
    weights = np.zeros(inputs.shape[1])
    bias = 0
    mse_errors = []

    # Treinamento por número de épocas
    for epoch in range(epochs):
        total_error = 0
        for x, label in zip(inputs, labels):
            # Previsão
            linear_output = np.dot(x, weights) + bias
            y_pred = linear_output  # ADALINE usa saída linear

            # Calcula o erro
            error = label - y_pred

            # Atualiza pesos e bias
            weights += eta * error * x
            bias += eta * error

            # Soma dos erros quadráticos para esta época
            total_error += error**2

        mse_errors.append(total_error / len(inputs))

    return weights, bias, mse_errors

# Treinamento do ADALINE para cada tabela
weights_and_adaline, bias_and_adaline, mse_errors_and = adaline_train(inputs, labels_and)
weights_or_adaline, bias_or_adaline, mse_errors_or = adaline_train(inputs, labels_or)
weights_xor_adaline, bias_xor_adaline, mse_errors_xor = adaline_train(inputs, labels_xor)

# Gráficos de evolução do erro quadrático médio (MSE)
plt.figure(figsize=(12, 4))
plt.subplot(1, 3, 1)
plt.plot(mse_errors_and, marker='o', label='AND')
plt.title('Evolução do MSE - AND')
plt.xlabel('Iterações')
plt.ylabel('Erro Quadrático Médio')
plt.grid(True)

plt.subplot(1, 3, 2)
plt.plot(mse_errors_or, marker='o', label='OR', color='green')
plt.title('Evolução do MSE - OR')
plt.xlabel('Iterações')
plt.ylabel('Erro Quadrático Médio')
plt.grid(True)

plt.subplot(1, 3, 3)
plt.plot(mse_errors_xor, marker='o', label='XOR', color='red')
plt.title('Evolução do MSE - XOR')
plt.xlabel('Iterações')
plt.ylabel('Erro Quadrático Médio')
plt.grid(True)

plt.tight_layout()
plt.show()
