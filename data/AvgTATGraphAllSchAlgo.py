import matplotlib.pyplot as plt
import numpy as np


# algono=1
algono=1
AvgTAT=[] 
Algolist=["FCFS","RR","SJF","SRTF","Priority","P Priority","MLQ","MLFQ"]
# Algolist=["FCFS","RR","SJF","SRTF","MLQ","MLFQ"]
for i in range(8):
	
	
    filename = "output"+str(algono)+"2.txt"
    file1=open(filename,"r")
    
    data=file1.readlines()[2].split("\n")[0]
    print(data)
    AvgTAT.append(float(data))
    file1.close()
    algono=algono+1
    
        
    

# tq=lines[n+2]   #for time quantum line
xpoints=np.array(Algolist)
ypoints=np.array(AvgTAT)
# fig = plt.figure(figsize = (10, 5))
plt.title("Average Turn Around Time") #for time quantum line
p1=plt.bar(Algolist,AvgTAT,width=0.3, color="green")
plt.xlabel("Scheduling Algorithms")
plt.ylabel("Average TAT Time")
plt.show()
