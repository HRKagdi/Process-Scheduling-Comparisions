#!/bin/bash

echo "#################################################"
echo "##############Running Project ############"
echo "#################################################"


cd "data"
fcfs="fcfs.cpp"
rr="rr.cpp"
sjf="SJF.cpp"
srtf="SRTF.cpp"
mlfq="MLFQ.cpp"
mlq="MLQ.cpp"
npp="NPP.cpp"
pp="PP.cpp"

g++ $fcfs -o fcfs
g++ $rr -o rr
g++ $srtf -o srtf
g++ $sjf -o sjf
g++ $mlq -o mlq
g++ $mlfq -o mlfq
g++ $npp -o npp
g++ $pp -o pp

chmod +x ./fcfs
chmod +x ./rr
chmod +x ./sjf
chmod +x ./srtf
chmod +x ./mlq
chmod +x ./mlfq
chmod +x ./npp
chmod +x ./pp

./fcfs
rm ./rr.txt
./rr
./sjf
./srtf
./mlq
./mlfq
./pp
./npp

python3 plotfcfs.py & python3 plotrr.py & python3 plotrr1.py & python3 AvgRTGraphAllSchAlgo.py & python3 AvgTATGraphAllSchAlgo.py & python3 AvgWTGraphAllSchAlgo.py & python3 graphSJF.py & python3 graphSRTF.py & python3 graphMLFQ.py & python3 graphMLQ.py & python3 GenerateGraphs.py

echo "#################################################"
echo "##############Done Project ############"
echo "#################################################"
