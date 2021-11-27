import matplotlib.pyplot as plt
import numpy as np

file1=open("output81.txt","r")
lines=file1.readlines()
bursts=[]
TAT=[]
WT=[]
process=[]
count=0
n=int(lines[0])
i=0
for line in lines:
    if(i==n+2):
        break
    if(i==0 or i==1):
        i=i+1
        continue
    line = line.split("\n")[0]
    arr=line.split(",")
    print(arr)
    process.append(arr[1])
    bursts.append(float(arr[3]))
    TAT.append(float(arr[8]))
    WT.append(float(arr[9]))
    i=i+1
# tq=lines[n+2]   #for time quantum line
xpoints=np.array(process)
ypoints=np.array(TAT)
fig = plt.figure(figsize = (10, 5))
plt.title("Multilevel Feedback Queue Scheduling") #for time quantum line
p1=plt.bar(process,TAT,width=0.3)
p2=plt.bar(process,bursts,width=0.3)
plt.xlabel("Process Name")
plt.ylabel("TurnAround Time")
plt.legend((p1[0], p2[0]), ('Waiting Time', 'Burst Time'))
plt.show()
file1.close()