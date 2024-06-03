#!/bin/sh

# Verificar se a porta e o protocolo foram fornecidos
if [ -z "$1" ] || [ -z "$2" ]; then
  echo "Use: $0 <porta> <protocolo>"
  echo "Protocolo: tcp ou udp"
  exit 1
fi

PORT=$1
PROTOCOLO=$2

# Verificar se o protocolo é tcp ou udp
if [ "$PROTOCOLO" != "tcp" ] && [ "$PROTOCOLO" != "udp" ]; then
  echo "Protocolo inválido. Use tcp ou udp."
  exit 1
fi

# Abrir um socket na porta especificada com o protocolo especificado
echo "Abrindo socket na porta $PORT usando protocolo $PROTOCOLO"
if [ "$PROTOCOLO" = "tcp" ]; then
  nc -l -p $PORT
else
  nc -u -l -p $PORT
fi
