#!/bin/bash

#$ -cwd
#$ -j y
#$ -S /bin/bash
/home/chris/usr/STMAC/veins_stableTMAC/run -u Cmdenv -f ./veins_STMAC_EDCA.ini -r 0 -c VehN_50