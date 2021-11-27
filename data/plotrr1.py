import matplotlib.pyplot as plt
import matplotlib
import numpy as np

file1=open("rr.txt","r")
lines=file1.readlines()
TAT=[]
WT=[]
RT=[]
tq=[]
count=0
#n=int(lines[0])
i=0
for line in lines:
    arr=line.split(",")
    print(arr)
    tq.append(int(arr[0]))
    TAT.append(float(arr[3]))
    WT.append(float(arr[4]))
    RT.append(float(arr[1]))


#tq=lines[n+2]   #for time quantum line
xpoints=np.array(tq)
ypoints=np.array(TAT)
fig = plt.figure(figsize = (10, 5))
plt.title("Round Robin") #for time quantum line
p1=plt.scatter(tq,TAT,label="TAT")
p2=plt.scatter(tq,WT)
p3=plt.scatter  (tq,RT)
#p2=plt.bar(tq,bursts,width=0.3)
plt.xlabel("Time Quantum")
plt.ylabel("Average Time")
plt.xticks([i for i in range(tq[0],tq[-1],1)])
plt.legend(['AVG TurnAround Time','AVG Waiting Time', 'AVG Response Time'])
plt.show()
file1.close()