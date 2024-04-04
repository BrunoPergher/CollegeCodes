from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
import os

# Gerar uma chave aleatória de 256 bits e um nonce de 128 bits
key = os.urandom(32)  # Gera uma chave aleatória de 32 bytes (256 bits)
nonce = os.urandom(16)  # Gera um nonce aleatório de 16 bytes (128 bits)

# Mensagem de exemplo a ser cifrada, codificada como bytes
plaintext = b"Exemplo de mensagem secreta!"

# Cria uma instância do ChaCha20 com a chave e o nonce gerados
algorithm = algorithms.ChaCha20(key, nonce)
cipher = Cipher(algorithm, mode=None, backend=default_backend())

# Cria um objeto encryptor e cifra a mensagem
encryptor = cipher.encryptor()
ciphertext = encryptor.update(plaintext) + encryptor.finalize()

# Cria um objeto decryptor e decifra a mensagem
decryptor = cipher.decryptor()
decrypted_message = decryptor.update(ciphertext) + decryptor.finalize()

print(f"Mensagem original: {plaintext}")
print(f"Mensagem cifrada: {ciphertext}")
print(f"Mensagem decifrada: {decrypted_message}")
