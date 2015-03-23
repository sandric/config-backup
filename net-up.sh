#!/bin/bash

echo "here comes the polly!"
echo "$1"
echo "${address}"
echo "${netmask}"
echo "${broadcast}"
echo "${gateway}"
echo "wut?"
echo "$1"

ip link set dev  "$1" down
ip addr del ${address}/${netmask} broadcast ${broadcast} dev "$1"

ip link set dev "$1" up
ip addr add ${address}/${netmask} broadcast ${broadcast} dev "$1"

[[ -z ${gateway} ]] || { 
  ip route add default via ${gateway}
}
