#!/bin/bash

echo 1 > /proc/sys/net/ipv4/ip_forward

# Ativa o encaminhamento de pacotes IPv4, essencial para funcionar como roteador
echo 1 > /proc/sys/net/ipv4/ip_forward

# Remove a rota padrão atual e configura uma nova rota padrão através de 192.0.2.2
ip route del default
ip route add default via 192.0.2.2

# Configura o NAT para mascarar IPs de saída usando a interface eth0
iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE

# Permite tráfego TCP para a internet para HTTP e HTTPS
iptables -A FORWARD -p tcp -s 192.0.3.0/24 -m multiport --dports 80,443 -j ACCEPT

# Permite tráfego de saída para serviços de e-mail
iptables -A FORWARD -p tcp -s 192.0.3.0/24 -m multiport --dports 465,587,995,143,993 -j ACCEPT

# Bloqueia todo o acesso à máquina na rede com IP 192.0.2.9
iptables -A FORWARD -d 192.0.2.9 -j DROP

# Bloqueia tráfego para a subrede local nas portas HTTP e HTTPS
iptables -A FORWARD -p tcp -d 192.0.3.0/24 -m multiport --dports 80,443 -j DROP
iptables -A FORWARD -p udp -d 192.0.3.0/24 -m multiport --dports 80,443 -j DROP

# Permite todo o tráfego da subrede local para o servidor de aplicação em 192.0.2.10
iptables -A FORWARD -s 192.0.3.0/24 -d 192.0.2.10 -j ACCEPT 
iptables -A FORWARD -d 192.0.2.10 -j DROP 

# Permite todo o tráfego entre a rede local e a DMZ
iptables -A FORWARD -s 192.0.3.0/24 -d 192.0.2.0/24 -j ACCEPT
iptables -A FORWARD -s 192.0.2.0/24 -d 192.0.3.0/24 -j ACCEPT

# Bloqueia todo o tráfego destinado à subrede local
iptables -A FORWARD -d 192.0.3.0/24 -j DROP

# Política padrão para encaminhamento é ACEITAR
iptables -P FORWARD ACCEPT

# Log de pacotes que serão bloqueados com prefixo "DROP"
iptables -A FORWARD -j LOG --log-prefix "DROP: " --log-level 4

# dmesg ou estão disponíveis no arquivo de log do sistema, como /var/log/syslog ou /var/log/messages