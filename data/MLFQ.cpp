#include<bits/stdc++.h>
#include <fstream>
using namespace std;

struct process
{
	int pid;
	int at;
	int bt;
	int type;
};

struct cmp {
	bool operator()(process const& p1, process const& p2)
	{
		if(p1.at > p2.at) return true;
		else if(p1.at == p2.at && p1.bt>p2.bt) return true;
		else return false;
	}
};
 
int main()
{

	cout<<"..\n";
	ifstream file("input8.txt");
	string data="";
	cout<<"..\n";
	ofstream outlogs("MLFQLogs.txt", ios::trunc);

	vector<string> inputstrings;
	while(getline(file,data,'\n')){
		cout<<data<<"\n";
		// stringstream ss(data);
		int count=0;
        inputstrings.push_back(data);
	}
	cout<<"..\n";

	
	int nop=stoi(inputstrings[0]);
	int nol=stoi(inputstrings[1]);

	// cin>>nop>>nol;


	vector<int> PID(nop), AT(nop), BT(nop), TYPE(nop), CT(nop), TAT(nop), WT(nop), RT(nop), TQ(nol);
	vector<string> PNAME(nop),BOUND(nop);
	vector<priority_queue<process, vector<process>, cmp>> mlq(nol);

	stringstream ss(inputstrings[2]);
	int i1=0;
	while(ss.good())
	{
		string subs;
		getline(ss,subs,',');
		TQ[i1]=stoi(subs);
		i1++;
	}


	
	for(int i=0;i<nop;i++)
	{
		// int pidv,ATv, BTv, PTyv;
		// PID,PNAME,AT,BT,BOUND,PTY
		int count=0;
		stringstream ss(inputstrings[i+5]);
		while(ss.good()){
			string subs;
			getline(ss,subs,',');
			if(count==0) PID[i]=stoi(subs);
			else if(count==1) PNAME[i]=subs;
			else if(count==2)AT[i]=stoi(subs);
			else if(count==3) BT[i]=stoi(subs);
			else if(count==4) BOUND[i]=subs;
			else if(count==5) TYPE[i] = stoi(subs);
		count++;
		}
		// cin>>PID[i]>>AT[i]>>BT[i]>>PTY[i];
	}

	for(int i=0;i<nop;i++)
	{
		// cin>>PID[i]>>AT[i]>>BT[i]>>TYPE[i];
		if(BOUND[i]=="IO") continue;
		mlq[TYPE[i]].push({PID[i],AT[i],BT[i],TYPE[i]});
	} 

	vector<int> get1st(nop,0);

int nopr=nop;
	int agtime;
	 agtime=stoi(inputstrings[3]);

	for(int i=0;i<nop;i++)
	{
		if(BOUND[i]=="IO")
		{
			CT[i] = AT[i]+BT[i];
			RT[i] = 0;
			get1st[i]=1;
			nopr--;
			cout<<"************************";
		}
	}
	int prremain=nopr;
	int time=0;
	while(prremain)
	{
		int fg=0;
		for(int i=0;i<nol;i++)
		{
			if(!mlq[i].empty() && i != nol-1 &&  mlq[i].top().at<=time)
			{
				process curp = mlq[i].top();
				mlq[i].pop();
				if(curp.bt < TQ[curp.type])
				{
					
					if(get1st[curp.pid]==0)
					{
						get1st[curp.pid]=1;
						RT[curp.pid] = time - AT[curp.pid];
					}
					outlogs<<"\n"<<PNAME[curp.pid]<<" into running State";
					time += curp.bt;
					CT[curp.pid]=time;
					outlogs<<"\n"<<PNAME[curp.pid]<<" has completed its Execution Phase";
					prremain--;

				}
				else
				{
					if(get1st[curp.pid]==0)
					{
						get1st[curp.pid]=1;
						RT[curp.pid] = time - AT[curp.pid];
					}
					outlogs<<"\n"<<PNAME[curp.pid]<<" into running State";
					time += TQ[curp.type];
					curp.bt -= TQ[curp.type];
					curp.type += 1;
					outlogs<<"\n"<<PNAME[curp.pid]<<" Moved to Ready State";
					mlq[i+1].push(curp);
				}
				fg=1;
				break;
			}
			else if(!mlq[i].empty() && i == nol-1 && mlq[i].top().at<=time)
			{
				process curp = mlq[i].top();
				if(get1st[curp.pid]==0)
				{
					get1st[curp.pid]=1;
					RT[curp.pid] = time - AT[curp.pid];
				}
				mlq[i].pop();
				outlogs<<"\n"<<PNAME[curp.pid]<<" into running State";
				time += curp.bt;
				CT[curp.pid]=time;
				prremain--;
				outlogs<<"\n"<<PNAME[curp.pid]<<" has completed its Execution Phase";


				fg=1;
				break;
			}
			
		}

 		for(int i=1;i<nol;i++)
 		{
 			while(!mlq[i].empty() && (time - mlq[i].top().at) >= agtime )
			{
				process curp = mlq[i].top();
				curp.type = 0;
				mlq[0].push(curp);
				mlq[i].pop();
				outlogs<<"\n"<<PNAME[curp.pid]<<" has moved to level 1";

			}
 		}
		

		if(!fg) time++;
	}

	cout<<"\n\n\nTAT : ";
	float AvgRT,AvgCT,AvgTAT,AvgWT;
	int calrt = 0,calct = 0,caltat = 0,calwt = 0;
	for(int i=0;i<nop;i++)
	{
		TAT[i] = CT[i] - AT[i];
		cout<<TAT[i]<<" ";
		caltat += TAT[i];
		calrt += RT[i];
		calct += CT[i];

	}

	cout<<"\nWT : ";
	for(int i=0;i<nop;i++)
	{
		WT[i] = TAT[i]-BT[i];
		cout<<WT[i]<<" ";
		calwt += WT[i];

	}
	AvgRT = (float)calrt/nop;
	AvgCT = (float)calct/nop;
	AvgTAT = (float)caltat/nop;
	AvgWT = (float)calwt/nop; 
	cout<<"\n\n";
	

	ofstream out("output81.txt", ios::trunc);
	string header=to_string(nop)+"\nPID,PNAME,AT,BT,BOUND,PTY,RT,CT,TAT,WT\n";
	out<<header;	
	// PID,PNAME,AT,BT,BOUND,PTY,RT,CT,TAT,WT
	if(out.is_open())
    {
        string str;
        for(int i=0;i<nop;i++)
        {
        	str = to_string(PID[i])+","+ (PNAME[i])+","+to_string(AT[i]) + ","+to_string(BT[i])+","+ (BOUND[i])+","+to_string(TYPE[i])+","+ to_string(RT[i])+","+to_string(CT[i])+","+to_string(TAT[i])+","+to_string(WT[i])+"\n";
        	out<<str;
        }
		
        out.close();
    }
    else cerr<<"Unable to open file";

	ofstream out2("output82.txt", ios::trunc);
	string header2=to_string(AvgRT)+"\n"+to_string(AvgCT)+"\n"+to_string(AvgTAT)+"\n"+to_string(AvgWT);
	out2<<header2;	
	// PID,PNAME,AT,BT,BOUND,PTY,RT,CT,TAT,WT
	out2.close();


	ofstream out3("output83.txt", ios::trunc);
	// string header=to_string(nop)+"\nRT,TAT,WT\n";
	// out3<<header;	
	// PID,PNAME,AT,BT,BOUND,PTY,RT,CT,TAT,WT
	if(out3.is_open())
    {
        string str;
        for(int i=0;i<nop;i++)
        {
        	str = (PNAME[i])+","+ to_string(RT[i])+","+to_string(TAT[i])+","+to_string(WT[i])+"\n";
        	out3<<str;
        }
		
        out3.close();
    }
    else cerr<<"Unable to open file";

    outlogs.close();
}