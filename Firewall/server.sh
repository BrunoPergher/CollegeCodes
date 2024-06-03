#!/bin/bash

ip route del default
ip route add default via 192.0.2.2
