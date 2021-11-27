import matplotlib.pyplot as plt
import numpy as np


RT=[]
TAT=[]
WT=[]
PName=""
Algolist=["FCFS","RR","SJF","SRTF","Priority","P Priority","MLQ","MLFQ"]

nop = int(input("Enter number of Process : "))

for i in range(nop):

    for j in range(8):

        file = open("output"+str(j+1)+"3.txt", "r")
        lines = file.readlines()[i].split(",")
        #print(lines)
        PName = lines[0]
        RT.append(float(lines[1]))
        TAT.append(float(lines[2]))
        WT.append(float(lines[3]))
        file.close()

    plt.title(PName)
    plt.xlabel("Process Scheduling Algorithms")
    plt.ylabel("Time")
    pltrt = plt.plot(Algolist,RT)
    plttat = plt.plot(Algolist,TAT)
    pltwt = plt.plot(Algolist,WT)

    plt.legend((pltrt[0], plttat[0],pltwt[0]), ('RT', 'TAT', 'WT'))

    plt.grid()

    
    RT.clear()
    WT.clear()
    TAT.clear()
    plt.show()






