import matplotlib.pyplot as plt
import numpy as np

file1=open("output11.txt","r")
lines=file1.readlines()
bursts=[]
TAT=[]
WT=[]
process=[]
count=0
n=int(lines[0])
i=0
for line in lines:
    if(i==n):
        break
    if(count==0 or count==1):
        count+=1
        continue
    arr=line.split(",")
    
    process.append(arr[1])
    bursts.append(float(arr[3]))
    TAT.append(float(arr[7]))
    WT.append(float(arr[8]))
    i=i+1
#tq=lines[n+2]   #for time quantum line
xpoints=np.array(process)
ypoints=np.array(TAT)
fig = plt.figure(figsize = (10, 5))
plt.title("First Come First Serve")
p1=plt.bar(process,TAT,width=0.3)
p2=plt.bar(process,bursts,width=0.3)
plt.xlabel("Process Name")
plt.ylabel("TurnAround Time")
plt.legend((p1[0], p2[0]), ('Waiting Time', 'Burst Time'))
plt.show()
file1.close()