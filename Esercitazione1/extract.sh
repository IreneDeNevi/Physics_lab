#!/bin/bash
echo " " > fileInput
for pl in  $@
do
    grep "/\*$pl" effemeridi.h | awk '{print $1}'>>fileInput
    grep -A6 "// $pl" effemeridi.h | grep -v "// $pl" >> fileInput
    echo " " >> fileInput
done

'''
-v fa da filtro: eleimina la stringa con il nome del pianeta
@ prende tutti i parametri pianeta che passo  sul terminale
'''
