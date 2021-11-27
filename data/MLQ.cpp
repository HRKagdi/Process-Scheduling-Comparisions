#include<bits/stdc++.h>
#include<fstream>
using namespace std;


struct process
{
	int pid;
	int at;
	int bt;
	int pty;
};

 
struct cmp {
	bool operator()(process const& p1, process const& p2)
	{
		if(p1.pty > p2.pty) return true;
		else if(p1.pty == p2.pty && p1.bt > p2.bt) return true;
		else if(p1.pty == p2.pty && p1.bt == p2.bt && p1.at>p1.at) return true;
		else if(p1.pty == p2.pty && p1.bt == p2.bt && p1.at==p1.at && p1.pid>p2.pid) return true;
		else return false;
	}
};

int main()
{
	cout<<"..\n";
	ifstream file("input7.txt");
	string data="";
	cout<<"..\n";
	ofstream outlogs("MLQLogs.txt", ios::trunc);

	vector<string> inputstrings;
	while(getline(file,data,'\n')){
		cout<<data<<"\n";
		// stringstream ss(data);
		int count=0;
        inputstrings.push_back(data);
	}
	cout<<"..\n";

	int nop=stoi(inputstrings[0]);
	
	vector<string> PNAME(nop),BOUND(nop);
	
	
	vector<int> flag(nop,0);
	vector<int> get1st(nop,0);
	int time=0;
    
	vector<int> PID(nop), AT(nop), BT(nop), PTY(nop), CT(nop), TAT(nop), WT(nop), RT(nop);
	
	for(int i=0;i<nop;i++)
	{
		// int pidv,ATv, BTv, PTyv;
		// PID,PNAME,AT,BT,BOUND,PTY
		int count=0;
		stringstream ss(inputstrings[i+2]);
		while(ss.good()){
			string subs;
			getline(ss,subs,',');
			if(count==0) PID[i]=stoi(subs);
			else if(count==1) PNAME[i]=subs;
			else if(count==2)AT[i]=stoi(subs);
			else if(count==3) BT[i]=stoi(subs);
			else if(count==4) BOUND[i]=subs;
			else if(count==5) PTY[i] = stoi(subs);
		count++;
		}
		// cin>>PID[i]>>AT[i]>>BT[i]>>PTY[i];
	}


	
	int nopr=nop;

	for(int i=0;i<nop;i++)
	{
		if(BOUND[i]=="IO")
		{
			CT[i] = AT[i]+BT[i];
			RT[i] = 0;
			get1st[i]=1;
			nopr--;
		}
	}

	cout<<"done1";

	
	// cout<<"  "<<nopr-2;
	while(nopr>0)
	{
		priority_queue<process, vector<process>, cmp> PQ;
		for(int i=0;i<nop;i++)
		{
			if(BOUND[i]=="IO") continue;
			if(AT[i]<=time && flag[PID[i]]==0) PQ.push({PID[i],AT[i],BT[i],PTY[i]});
		}
		if(PQ.empty())
		{
			time++;
			continue;
		}
		process curp = PQ.top();
		PQ.pop();
		flag[curp.pid]=1;
		RT[curp.pid] = time - curp.at;

		nopr--;
		time += curp.bt;
		outlogs<<"\n"<<PNAME[curp.pid]<<" into running State and completed its execution at "<<time;
		CT[curp.pid] = time;

	}
	cout<<"\nTAT : ";
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
	ofstream out("output71.txt", ios::trunc);
	string header=to_string(nop)+"\nPID,PNAME,AT,BT,BOUND,PTY,RT,CT,TAT,WT\n";
	out<<header;	
	// PID,PNAME,AT,BT,BOUND,PTY,RT,CT,TAT,WT
	if(out.is_open())
    {
        string str;
        for(int i=0;i<nop;i++)
        {
        	str = to_string(PID[i])+","+ (PNAME[i])+","+to_string(AT[i]) + ","+to_string(BT[i])+","+ (BOUND[i])+","+to_string(PTY[i])+","+ to_string(RT[i])+","+to_string(CT[i])+","+to_string(TAT[i])+","+to_string(WT[i])+"\n";
        	out<<str;
        }
		
        out.close();
    }
    else cerr<<"Unable to open file";



	ofstream out2("output72.txt", ios::trunc);
	string header2=to_string(AvgRT)+"\n"+to_string(AvgCT)+"\n"+to_string(AvgTAT)+"\n"+to_string(AvgWT);
	out2<<header2;	
	// PID,PNAME,AT,BT,BOUND,PTY,RT,CT,TAT,WT
	out2.close();
	
	ofstream out3("output73.txt", ios::trunc);
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