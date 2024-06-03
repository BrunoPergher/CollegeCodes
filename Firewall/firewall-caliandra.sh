#!/bin/bash

echo 1 > /proc/sys/net/ipv4/ip_forward

# Configuração das rotas de rede
ip route del default
ip route add default via 192.0.1.1
ip route add 192.0.3.0/24 via 192.0.2.3

# Configura NAT para a interface eth0 para permitir tráfego de saída para a Internet
iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE

# Permite conexões HTTP e HTTPS de entrada da RedePan para a Internet (portas 80 e 443)
iptables -A FORWARD -p tcp -d 192.0.2.6 -m multiport --dports 80,443 -j ACCEPT

# Permite conexões DNS de entrada e saída (porta 53)
iptables -A FORWARD -p udp -d 192.0.2.7 --dport 53 -j ACCEPT

# Permite tráfego SMTP e IMAP de entrada para e-mail (portas 465, 587, 995, 143, 993)
iptables -A FORWARD -p tcp -d 192.0.2.0/24 -m multiport --dports 465,587,995,143,993 -j ACCEPT

# Restringe o acesso ao banco de dados, somente o servidor de Aplicações pode acessar (porta 5432)
iptables -A FORWARD -p tcp -s 192.0.2.10 -d 192.0.2.9 --dport 5432 -j ACCEPT 
iptables -A FORWARD -d 192.0.2.9 -j DROP 

# Restringe o acesso ao Servidor de Aplicações à SubredeLocal
iptables -A FORWARD -s 192.0.3.0/24 -d 192.0.2.10 -j ACCEPT 
iptables -A FORWARD -d 192.0.2.10 -j DROP 

# Permite todo o tráfego entre a rede local
iptables -A FORWARD -s 192.0.2.0/24 -d 192.0.2.0/24 -j ACCEPT
iptables -A FORWARD -d 192.0.2.0/24 -j DROP

# Política padrão para encaminhamento é ACEITAR
iptables -P FORWARD ACCEPT

# Log de pacotes que serão bloqueados com prefixo "DROP" e nível de log 4 (WARNING)
iptables -A FORWARD -j LOG --log-prefix "DROP: " --log-level 4
