#include<bits/stdc++.h>

using namespace std;



bool flag;

class pcb{

    public:
    string process_name;
    int pid;
    int waiting_time;
    int burst_time;
    int arrival_time;
    int turnaround_time;
    int completion_time;
    int priority;
    string state;
    int start_time;
    int response_time;
    string type_of_process;
};

bool comp(pcb* a, pcb* b)
{
    if(a->arrival_time > b->arrival_time)
    {
        return false;
    }
    else if(a->arrival_time==b->arrival_time)
    {
        if(flag)
        return (a->priority < b->priority);  // Smallest number first
        else
            return (a->priority > b->priority);
    }
    else{
        return true;
    }
}

auto Comparator = [](const std::tuple<int,int>& left, const std::tuple<int,int>& right)
        {
            return std::get<1>(left) > std::get<1>(right);
        };


bool comp1(pcb* a, pcb* b)
{
    return a->pid < b->pid;
}


int main()
{


        int counter=0;
        for(int i=0;i<2;i++)
        {        map<int,pcb*> mpp;
                vector<pcb*> process_queue;  



                ifstream file("input5.txt");
                string line;
                int n;
                bool flag1=false;
                while(getline(file,line))
                {
                    stringstream linestream(line);
                    string value;
                    while(getline(linestream,value,','))
                    {
                        n=stoi(value.c_str());
                        //cout<<n<<endl;
                        flag1=true;
                        break;
                    }
                    if(flag1)
                        break;
                }
                flag1=false;
                int priority_mode=0;
                line="";
                while(getline(file,line))
                {

                
                    stringstream linestream(line);
                    string value;
                    while(getline(linestream,value,','))
                    {
                        //cout<<"Inside";
                        priority_mode=stoi(value.c_str());
                        if(counter==1)
                        {
                            priority_mode=1-priority_mode;
                        }
                    // cout<<priority_mode<<endl;
                    // cout<<'k';
                        if(priority_mode==1)
                        {
                            flag=false;
                            flag1=true;
                            //cout<<"b2";
                            break;
                            //cout<<"broken";
                        }
                        else{
                            flag=true;
                            flag1=true;
                            //cout<<"b1";
                            break;
                            //cout<<"broken";
                        }
                        
                        break;
                        //cout<<"broken";
                    }
                    //cout<<'b';
                    if(flag1)
                    break;

                    
                }

                
                
                
                while(getline(file,line))
                {
                    stringstream linestream(line);
                    string value;

                    pcb *new_pcb= new pcb;
                    int cnt=1;
                    while(getline(linestream,value,','))
                    {   

                        switch(cnt)
                        {
                            case 1: new_pcb->pid=stoi(value.c_str());
                                    mpp[new_pcb->pid]=new_pcb;
                                    break;
                            case 2: new_pcb->process_name=value;
                                    break;
                            case 3: new_pcb->arrival_time=stoi(value.c_str());
                                    break;
                            case 4: new_pcb->burst_time=stoi(value.c_str());
                                    
                                    break;
                            case 5: new_pcb->type_of_process=value;
                                    break;
                            // case 6: new_pcb->priority=stoi(value.c_str());
                            //          break;

                        }


                        new_pcb->priority=rand()%(n+1);
                        cnt++;
                        
                    }
                    new_pcb->start_time=-1;
                    process_queue.push_back(new_pcb);
                }

                file.close();
                
                vector<pcb*>completed_processes;
                double avg_waiting_time=0;
                double avg_response_time=0;
                double avg_turnaround_time=0; 
                double avg_completion_time=0;

                
                for(int i=0;i<process_queue.size();i++)
                {
                    if(process_queue[i]->type_of_process=="IO")
                    {
                        process_queue[i]->start_time=process_queue[i]->arrival_time;
                        process_queue[i]->response_time=0;
                        process_queue[i]->completion_time=process_queue[i]->arrival_time+process_queue[i]->burst_time;
                        process_queue[i]->turnaround_time=process_queue[i]->completion_time-process_queue[i]->arrival_time;
                        process_queue[i]->waiting_time=0;


                        avg_waiting_time+=process_queue[i]->waiting_time;
                        avg_response_time+=process_queue[i]->response_time;
                        avg_turnaround_time+=process_queue[i]->turnaround_time;
                        avg_completion_time+=process_queue[i]->completion_time;

                        completed_processes.push_back(process_queue[i]);
                        process_queue.erase(process_queue.begin()+i);
                
                        
                    }
                }

                sort(process_queue.begin(),process_queue.end(),comp);
                
                int k=0;
                while(process_queue.size()!=0)
                {

                    priority_queue<tuple<int,int>,vector<tuple<int,int>>,decltype(Comparator)>pq(Comparator);

                    for(int i=0;i<process_queue.size();i++)
                    {
                        if(process_queue[i]->arrival_time<=k && process_queue[i]->type_of_process!="IO")
                        {
                            pq.push(make_pair(process_queue[i]->pid,process_queue[i]->priority));
                        }
                        else{
                            break;
                        }
                    }
                    if(pq.size()==0)
                    {
                        k++;
                        continue;
                    }
                    int indx=get<0>(pq.top());                   
                

                    pcb * current_process=mpp[indx];
                    if(current_process->arrival_time<=k)
                    {
                        int temp;
                        current_process->start_time=k;
                        current_process->response_time=k-current_process->arrival_time;
                        current_process->completion_time= k+current_process->burst_time;
                        k+=current_process->burst_time;
                        current_process->turnaround_time=current_process->completion_time-current_process->arrival_time;
                        current_process->waiting_time=current_process->turnaround_time-current_process->burst_time;
                        completed_processes.push_back(current_process);
                        for(int i=0;i<process_queue.size();i++)
                        {
                            if(process_queue[i]->pid==indx)
                            {
                                temp=i;
                                break;
                            }
                        }


                        avg_completion_time+=current_process->completion_time;
                        avg_waiting_time+=current_process->waiting_time;
                        avg_response_time+=current_process->response_time;
                        avg_turnaround_time+=current_process->turnaround_time;
                        process_queue.erase(process_queue.begin()+temp);

                    }
                    else{
                        k++;
                    }

                    
                    
                }
                //cout<<"okay";
                sort(completed_processes.begin(),completed_processes.end(),comp1);  


                ofstream myfile;
                if(counter==1)
                {
                    myfile.open("output511.txt");
                }
                else
                {
                    myfile.open("output51.txt");
                }
                for(int i=0;i<completed_processes.size();i++)
                {

                    string line;
                    pcb * cur = completed_processes[i];

                    line+=to_string(cur->pid)+","+cur->process_name+","+to_string(cur->arrival_time);
                    line+=","+to_string(cur->burst_time)+","+cur->type_of_process+",";
                    line+=to_string(cur->priority)+","+to_string(cur->response_time)+","+to_string(cur->completion_time)+","+to_string(cur->turnaround_time)+","+to_string(cur->waiting_time);
                    line+="\n";
                    myfile<<line;
                }

                avg_waiting_time=avg_waiting_time/n;
                avg_response_time=avg_response_time/n;
                avg_turnaround_time=avg_turnaround_time/n;
                avg_completion_time=avg_completion_time/n;

                line+=to_string(avg_response_time)+"\n"+to_string(avg_completion_time)+"\n"+to_string(avg_turnaround_time)+"\n"+to_string(avg_waiting_time);
                myfile<<line;
                myfile.close();




                ofstream file1;
                if(counter==1)
                {
                    file1.open("output521.txt");
                }
                else{
                    file1.open("output52.txt");
                }
                line="";

                line+=to_string(avg_response_time)+"\n"+to_string(avg_completion_time)+"\n"+to_string(avg_turnaround_time)+"\n"+to_string(avg_waiting_time);
                file1<<line;
                file1.close();


                ofstream file2;
                if(counter==1){
                    file2.open("output532.txt");
                }
                else
                {
                    file2.open("output53.txt");
                }
                line="";
                string str="";
                for(int i=0;i<completed_processes.size();i++)
                {
                    
                    pcb * cur = completed_processes[i];
                    str+=cur->process_name+","+to_string(cur->response_time)+","+to_string(cur->turnaround_time)+","+to_string(cur->waiting_time)+"\n";


                }

                file2<<str;
                file2.close();
                counter++;
                //cout<<"Okaty";
        }
    return 0;

}