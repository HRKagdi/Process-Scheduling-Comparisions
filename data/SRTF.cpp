#include<bits/stdc++.h>
using namespace std;
class PCB{
	public:
	
	string PName;
	string PState;
	long long int PID;
	long long int PCounter;
	vector<long long int> registers;
	pair<long long int,long long int> memLimits;
	vector<string> files;
	string PType;
	int priority;
	float arrivalTime;
	float startTime;
	float BurstTime;
	float waitTime;
	float turnAround;
	float completionTime;
	float temp;
	float responseTime;
	PCB(string PName, string PState,long long int PID,long long int PCounter,
	    vector<long long int> registers,pair<long long int,long long int>memLimits,
	    vector<string> files,string PType,int priority, float startTime,float BurstTime){
	    
	    this->PName=PName;
	    this->PState=PState;
	    this->PID=PID;
	    this->PCounter=PCounter;
	    this->registers=registers;
	    this->memLimits=memLimits;
	    this->files=files;
	    this->PType=PType;
	    this->priority=priority;
		this->arrivalTime=startTime;
	    this->startTime=0;
	    this->BurstTime=BurstTime;
		this->temp=BurstTime;
	    this->waitTime=0;
	    this->turnAround=0;
	    this->completionTime=0;
		this->responseTime=0;
	}
	
	void PrintPCB(){
		cout<<"PCB of Process "<<PID<<" is"<<endl;
		cout<<"----------------------------------------"<<endl;
		cout<<"Process ID: "<<PID<<endl;
		cout<<"Process Name: "<<PName<<endl;
		cout<<"Process State: "<<PState<<endl;
		cout<<"Program Counter: "<<PCounter<<endl;
		cout<<"PType: "<<PType<<endl;
		cout<<"Priority: "<<priority<<endl;
		cout<<"StartTime: "<<startTime<<endl;
		cout<<"BurstTime: "<<BurstTime<<endl;
		cout<<"----------------------------------------"<<endl;
	}
};

int main(){

	cout<<"Welcome to SJF Process Scheduler"<<endl;

	string PName,PType; 
	long long int PID;
	float startTime, BurstTime;
	int priority;
	
	vector<PCB*> readyQ;
	vector<PCB*> blockedQ;
	map<long long int, PCB*> mp;
	map<float,PCB*> arrmaps;
	priority_queue<pair<float,long long int>, vector<pair<float,long long int>>,
			greater<pair<float,long long int>>> pq;

	ifstream file("input3.txt");
	string data="";


	while(getline(file,data,'\n')){
		stringstream ss(data);
		int count=0;
		while(ss.good()){
			string subs;
			getline(ss,subs,',');
			if(count==0) PID=stoi(subs);
			else if(count==1) PName=subs;
			else if(count==2)startTime=stof(subs);
			else if(count==3) BurstTime=stof(subs);
			else if(count==4){
				PType=subs;
				count=0;
			}
			count++;
		}

		
		long long int Pcounter=0;
		vector<long long int> registers;
		pair<long long int,long long int> memLimits;
		vector<string> files;
		string Pstate="New";
		
		PCB* newProcess=new PCB(PName,Pstate,PID,Pcounter,registers,
		memLimits,files,PType,priority,startTime,BurstTime);
		
		if(PType=="C") readyQ.push_back(newProcess);
		else blockedQ.push_back(newProcess);
		
	}
	file.close();
	
	for(int i=0;i<readyQ.size();i++){
		readyQ[i]->PState="Ready";
		mp[readyQ[i]->PID]=readyQ[i];
	}
	for(int i=0;i<blockedQ.size();i++){
		blockedQ[i]->PState="WAITING";
	}
	int temp=0;
	for(int i=0;i<readyQ.size();i++){
		temp+=readyQ[i]->startTime;
		temp+=readyQ[i]->BurstTime;
	}
	vector<pair<float,long long int>> v;
    int smallest; int count=readyQ.size();
    vector<float> tbursts(readyQ.size());
    for(int i=0;i<readyQ.size();i++){
        tbursts[i]=readyQ[i]->BurstTime;
    }
    int currentTime=0;
    while(count>0){
        int maxBT=INT_MAX;
        int index=-1;
        for(int i=0;i<readyQ.size();i++){
            if(readyQ[i]->BurstTime>0 && readyQ[i]->arrivalTime<=currentTime){
                if(readyQ[i]->BurstTime<maxBT){
                    maxBT=readyQ[i]->BurstTime;
                    index=i;
                }
                if(readyQ[i]->BurstTime==maxBT){
                    if(readyQ[i]->arrivalTime<readyQ[index]->arrivalTime){
                        maxBT=readyQ[i]->BurstTime;
                        index=i;
                    }
                }
            }
        }
        if(index>=0 && index<=readyQ.size()){
            if(readyQ[index]->BurstTime==readyQ[index]->temp){
                readyQ[index]->startTime=currentTime;
            }
            readyQ[index]->BurstTime--;
            currentTime++;
            if(readyQ[index]->BurstTime==0){
                readyQ[index]->completionTime=currentTime;
                count--;
            }
        }
        else{
            currentTime++;
        }
    }
	float averageTurnAround=0; float averageWaitTime=0;
	float averageResponseTime=0; float averageCompletionTime=0;
	for(int i=0;i<readyQ.size();i++){
		readyQ[i]->waitTime=readyQ[i]->completionTime-readyQ[i]->arrivalTime-readyQ[i]->temp;
		readyQ[i]->turnAround=readyQ[i]->completionTime-readyQ[i]->arrivalTime;	
		readyQ[i]->responseTime=readyQ[i]->startTime-readyQ[i]->arrivalTime;
		averageTurnAround+=readyQ[i]->turnAround;
		averageWaitTime+=readyQ[i]->waitTime;
		averageResponseTime+=readyQ[i]->responseTime;
		averageCompletionTime+=readyQ[i]->completionTime;
	}
	averageTurnAround/=readyQ.size();
	averageWaitTime/=readyQ.size();
	averageCompletionTime/=readyQ.size();
	averageResponseTime/=readyQ.size();
	cout<<"*************************************************************************************************"<<endl;
	cout<<"PID\t"<<"ArrivalTime\t"<<"BurstTime\t"<<"CompletionTime\t"<<"WaitTime\t"<<"TurnAround"
    <<endl;

	ofstream out("output41.txt");
	ofstream out1("output43.txt");
	ofstream out2("output42.txt");
	string header="PID,PNAME,AT,BT,BOUND,RT,CT,TAT,WT\n";
	out<<header;
	string h1="PID,RT,TAT,WT\n";
	//out1<<h1;
	for(int i=0;i<readyQ.size();i++){
		cout<<readyQ[i]->PID<<"\t\t";
		cout<<readyQ[i]->arrivalTime<<"\t\t";
		cout<<readyQ[i]->temp<<"\t\t";
		cout<<readyQ[i]->completionTime<<"\t\t";
		cout<<readyQ[i]->waitTime<<"\t\t";
        cout<<readyQ[i]->turnAround<<endl;

		string str="";
            str+=to_string(readyQ[i]->PID)+",";
            str+=readyQ[i]->PName+",";
            str+=to_string(readyQ[i]->arrivalTime)+",";
			str+=to_string(readyQ[i]->temp)+",";
			str+=PType+",";
			str+=to_string(readyQ[i]->responseTime)+",";
			str+=to_string(readyQ[i]->completionTime)+",";
			str+=to_string(readyQ[i]->turnAround)+",";
			str+=to_string(readyQ[i]->waitTime)+"\n";
			out<<str;

			string s1="";
			s1+=readyQ[i]->PName+",";
			s1+=to_string(readyQ[i]->responseTime)+",";
			s1+=to_string(readyQ[i]->turnAround)+",";
			s1+=to_string(readyQ[i]->waitTime)+"\n";
			out1<<s1;
	}
	string answer="";
	answer+=to_string(averageResponseTime)+"\n";
	answer+=to_string(averageCompletionTime)+"\n";
	answer+=to_string(averageTurnAround)+"\n";
	answer+=to_string(averageWaitTime)+"\n";
	out2<<answer;
	out.close();
	out1.close();
	out2.close();
	cout<<"Average TurnAroundTime: "<<averageTurnAround<<endl;
	cout<<"Average Waiting Time: "<<averageWaitTime<<endl;
	cout<<"***************************************************************************************************"<<endl;
	return 0;					
}

