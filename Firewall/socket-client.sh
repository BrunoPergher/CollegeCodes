#!/bin/sh

# Verificar se o IP, a porta e o protocolo foram fornecidos
if [ -z "$1" ] || [ -z "$2" ] || [ -z "$3" ]; then
  echo "Uso: $0 <ip> <porta> <protocolo>"
  echo "Protocolo: tcp ou udp"
  exit 1
fi

IP=$1
PORT=$2
PROTOCOLO=$3

# Verificar se o protocolo é tcp ou udp
if [ "$PROTOCOLO" != "tcp" ] && [ "$PROTOCOLO" != "udp" ]; then
  echo "Protocolo inválido. Use tcp ou udp."
  exit 1
fi

# Conectar ao servidor remoto usando netcat
if [ "$PROTOCOLO" = "tcp" ]; then
  nc $IP $PORT
else
  nc -u $IP $PORT
fi
