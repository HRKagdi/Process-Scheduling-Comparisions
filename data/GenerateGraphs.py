import matplotlib.pyplot as plt
import numpy as np


def function(name,k):

    file1 = open(name+".txt", "r")
    file2 = open(name+"1.txt", "r")
    lines2=file2.readlines()
    lines = file1.readlines()
    bursts = []
    TAT = []
    WT = []
    WT1 = []
    process = []
    bursts1 = []
    TAT1 = []
    WT1 = []
    process1 = []
    count = 0
    num_lines = sum(1 for line in open(name+".txt"))
    line_count = 0
    for line in lines:
        line_count += 1
    print(line_count)
    file1.close()
    file1 = open(name+".txt", "r")
    lines1 = file1.readlines()
    arr = []
    cnt=0
    line_cntr = 0
    for line in lines:
        if(line_cntr == line_count-4):
            break
        line_cntr += 1
        

        arr = line.split(",")
        print(arr)
        # print(arr)
        process.append(arr[0])
        bursts.append(float(int(arr[3])))
        TAT.append(float(int(arr[7])))
        WT.append(float(arr[8]))

    line_cntr = 0
    arr = []
    for line in lines2:
        if(line_cntr == line_count-4):
            break
        line_cntr += 1
        arr = line.split(",")
        process1.append(arr[0])
        bursts1.append(float(int(arr[3])))
        TAT1.append(float(int(arr[7])))
        WT1.append(float(arr[8]))

    xpoints = np.array(process)
    ypoints = np.array(TAT)
    fig = plt.figure(figsize=(10, 5))
    plt.bar(process, TAT, width=0.3,label="Waiting Time")
    plt.bar(process, bursts, width=0.3, label=" Burst Time")
    plt.xlabel("Process Number")
    plt.ylabel("TurnAround Time")
    str=""
    if(name=="output51"):
        str="Non Preemptive"
    else:
        str="Preemptive"
    plt.title("Comparison of TAT and BT with Original Priority "+str)
    plt.legend()

    plot1=plt.figure(k)
    #plt.show()
    k+=1
    xpoints = np.array(process1)
    ypoints = np.array(TAT)
    fig = plt.figure(figsize=(10, 5))
    plt.bar(process1, TAT1, width=0.3, label="Waiting Time Reversed Priority")
    plt.bar(process1, bursts1, width=0.3,label="Burst Time Reversed Priority")
    plt.xlabel("Process Number")
    plt.ylabel("TurnAround Time")
    #plt.legend()
    plot2=plt.figure(k)
    plt.title("Comparison of TAT and BT with Reversed Priorities "+str )
    #plt.show()


    xpoints = np.array(process1)
    ypoints = np.array(TAT)
    fig = plt.figure(figsize=(10, 5))
    TAT_F = list(map(lambda x,y: x+y,TAT1,TAT))
    plt.bar(process1, TAT_F, width=0.3,label="Reversed Priority")
    plt.bar(process1, TAT, width=0.3,label="Original Priority")
    plt.xlabel("Process Numbers")
    plt.ylabel("Turn Around Time")
    #plt.legend()
    
    plt.title("Comparison of TATs <Reversed Priority/ Original Priority > "+str)
    #plt.show()
    k+=1
    plot3=plt.figure(k)
    WT_F = list(map(lambda x,y : x+y,WT1,WT))
    xpoints = np.array(process1)
    ypoints = np.array(TAT)
    fig = plt.figure(figsize=(10, 5))
    plt.bar(process1, WT_F, width=0.3,label="Reversed Priority")
    plt.bar(process1, WT, width=0.3,label="Original Priority")
    plt.xlabel("Process Number")
    plt.ylabel("Waiting Times")
    plt.legend()
    plt.title("Comparison of Wts of <Reversed/Original> Priorities " +str)
    k+=1
    plot4 = plt.figure(k)
  
    if(name=="output61"):
        plt.show()
    file1.close()
    return k

k=1
k=function("output51",k)
function("output61",k)
