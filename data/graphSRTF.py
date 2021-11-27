import matplotlib.pyplot as plt
import numpy as np
from matplotlib.patches import Rectangle
file1=open("output41.txt","r")
lines=file1.readlines()
bursts=[]
TAT=[]
WT=[]
process=[]
count=0
for line in lines:
    if(count==0):
        count+=1
        continue
    arr=line.split(",")
    #print(arr)
    process.append(arr[1])
    bursts.append(float(arr[3]))
    TAT.append(float(arr[7]))
    WT.append(float(arr[8]))

xpoints=np.array(process)
ypoints=np.array(TAT)
fig = plt.figure(figsize = (10, 5))
plt.bar(process,TAT,width=0.3)
plt.bar(process,bursts,width=0.3)
plt.xlabel("Process Number")
plt.ylabel("TurnAround Time")
colors = {'Wait Time':'blue', 'Burst Time':'orange'}         
labels = list(colors.keys())
handles = [plt.Rectangle((0,0),1,1, color=colors[label]) for label in labels]
plt.legend(handles, labels)
plt.title("SRTF Wait Time Burst Time Distribution")
plt.show()
file1.close()
