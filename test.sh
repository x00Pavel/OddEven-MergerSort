#!/bin/bash

PREFIX=""

#preklad cpp zdrojaku
if [[ $(hostname) == *"merlin"* ]]
then
    PREFIX="--prefix /usr/local/share/OpenMPI"
fi

mpic++ ${PREFIX} -o oems oems.cpp


#vyrobeni souboru s random cisly
dd if=/dev/random bs=1 count=8 of=numbers

#spusteni
PREFIX="${PREFIX} --oversubscribe"
mpirun ${PREFIX} -np 20 oems

#uklid
rm -f oems numbers