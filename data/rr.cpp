#include <bits/stdc++.h>
using namespace std;
int tq;

class PCB
{
public:
    int pid;
    string pname;
    string bound;
    int at;
    int bt;
    int remaining_bt;
    int tat;
    int wt;
    int ct;
    int rt;
    string state;
    bool in_memory;
    PCB()
    {
        remaining_bt = 0;
        tat = 0;
        ct = 0;
        rt = 0;
    }
    PCB(int id, string name, string b, int a, int bu)
    {
        pid = id;
        pname = name;
        bound = b;
        at = a;
        bt = bu;
        remaining_bt = bu;
        tat = 0;
        ct = 0;
        rt = 0;
        in_memory = 0;
    }
    void PrintPCB()
    {
        cout << "PCB of Process " << pid << " is" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Process ID: " << pid << endl;
        cout << "Process Name: " << pname << endl;
        cout << "PType: " << bound << endl;

        cout << "StartTime: " << at << endl;
        cout << "BurstTime: " << bt << endl;
        cout << "----------------------------------------" << endl;
    }
};
struct Compare
{
    bool operator()(const PCB *lx, const PCB *rx) const
    {
        if (lx->at < rx->at)
        {
            return true;
        }
        else if (lx->at == rx->at)
        {
            if (lx->pid < rx->pid)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};
int main(int argv, char *argc[])
{
    ifstream inp("input2.txt");
    int end = 0;
    string readed_data;
    getline(inp, readed_data);
    int n, i;
    //cout<<readed_data;
    n = stoi(readed_data);
    getline(inp, readed_data);
    tq = stoi(readed_data);

    vector<string> arguments;
    string temp;
    getline(inp, temp);
    for (int l = 0; l < n; l++)
    {
        getline(inp, readed_data);

        string temp = "";
        for (int h = 0; h < readed_data.length(); h++)
        {
            if (readed_data[h] == ',')
            {

                arguments.push_back(temp);
                temp = "";
            }
            else
            {
                temp = temp + readed_data[h];
            }
        }
        arguments.push_back(temp);
    }

    vector<PCB *> table;

    deque<PCB *> waiting;
    float avg_tat = 0, avg_wt = 0, avg_rt = 0, avg_ct = 0;

    for (int l = 0; l < arguments.size();)
    {
        int a = stoi(arguments[l + 0]);
        string name = arguments[l + 1];
        int b, c;
        b = stoi(arguments[l + 2]);
        c = stoi(arguments[l + 3]);
        end = max(end, c);
        string bound = arguments[l + 4];
        PCB *process = new PCB(a, name, bound, b, c);
        table.push_back(process);
        //table[a] = process;
        l = l + 5;
    }
    vector<PCB *> input_table(table);
    sort(table.begin(), table.end(), Compare());
    i = -1;
    PCB *r = nullptr;
    for (auto t : table)
    {
        if (t->bound == "CPU")
        {
            r = t;
            break;
        }
    }

    int cur_time;
    if (r != nullptr)
    {
        waiting.push_back(r);
        r->in_memory = true;
        cur_time = r->at;
    }

    while (!waiting.empty())
    {
        PCB *cur = waiting.front();

        waiting.pop_front();
        if (cur->bound == "IO")
        {
            continue;
        }
        cout << "-------------------------" << endl;
        cout << "Process ID " << cur->pid << " is running" << endl;

        if (cur->remaining_bt == cur->bt)
        {
            cur->rt = cur_time - cur->at;
            avg_rt += cur->rt;
        }

        if (cur->remaining_bt == tq)
        {
            cur_time += tq;
            cur->ct = cur_time;
            cur->tat = cur_time - cur->at;
            cur->wt = cur->tat - cur->bt;
            avg_tat += cur->tat;
            avg_wt += cur->wt;
            avg_ct += cur->ct;
            cur->remaining_bt = 0;

            cout << "Process ID " << cur->pid << " Completed" << endl;
        }
        else if (cur->remaining_bt < tq)
        {
            cur_time += cur->remaining_bt;
            cur->ct = cur_time;
            cur->tat = cur_time - cur->at;
            cur->wt = cur->tat - cur->bt;
            avg_tat += cur->tat;
            avg_wt += cur->wt;
            avg_ct += cur->ct;
            cur->remaining_bt = 0;
        }
        else
        {
            cur_time += tq;
            cur->remaining_bt -= tq;
        }
        for (auto s : table)
        {
            if (s->in_memory == false && s->bound == "CPU" && s->at <= cur_time)
            {
                waiting.push_back(s);
                s->in_memory = true;
            }
        }
        if (cur->remaining_bt > 0)
        {
            waiting.push_back(cur);
        }

        cout << "Waiting queue(process IDs)status" << endl;

        for (int y = 0; y < waiting.size(); y++)
        {
            cout << waiting[y]->pid << " ";
        }
        cout << endl;
    }
    for (i = 0; i < input_table.size(); i++)
    {
        if (input_table[i]->bound == "IO")
        {
            input_table[i]->tat = input_table[i]->bt;
            input_table[i]->wt = 0;
            input_table[i]->rt = 0;
            input_table[i]->ct = input_table[i]->at + input_table[i]->bt;

            avg_tat += input_table[i]->tat;
            continue;
        }
    }
    ofstream out, out4;
    out.open("output21.txt", ios::trunc);
    out4.open("output23.txt", ios::trunc);
    out << n << "\n";
    out << "PID"
        << ","
        << "PNAME"
        << ","
        << "AT"
        << ","
        << "BT"
        << ","
        << "BOUND"
        << ","
        << "RT"
        << ","
        << "CT"
        << ","
        << "TAT"
        << ","
        << "WT"
        << endl;
    i = 0;
    for (auto s : input_table)
    {
        out << s->pid
            << ","
            << s->pname
            << ","
            << s->at
            << ","
            << s->bt
            << ","
            << s->bound
            << ","
            << s->rt
            << ","
            << s->ct
            << ","
            << s->tat
            << ","
            << s->wt
            << endl;
        out4 << s->pname
             << ","
             << s->rt
             << ","
             << s->tat
             << ","
             << s->wt
             << endl;
    }
    out << tq << endl;
    out << avg_rt / n << endl;
    out << avg_ct / n << endl;
    out << avg_tat / n << endl;
    out << avg_wt / n << endl;
    out.close();
    out4.close();
    out.open("output22.txt", ios::trunc);
    out << avg_rt / n << endl;
    out << avg_ct / n << endl;
    out << avg_tat / n << endl;
    out << avg_wt / n << endl;
    inp.close();
    out.close();

    for (int tqu = tq + 1; tqu < end; tqu++)
    {
        vector<PCB *> table;

        deque<PCB *> waiting;
        float avg_tat = 0, avg_wt = 0, avg_rt = 0, avg_ct = 0;

        for (int l = 0; l < arguments.size();)
        {
            int a = stoi(arguments[l + 0]);
            string name = arguments[l + 1];
            int b, c;
            b = stoi(arguments[l + 2]);
            c = stoi(arguments[l + 3]);

            string bound = arguments[l + 4];
            PCB *process = new PCB(a, name, bound, b, c);
            table.push_back(process);
            //table[a] = process;
            l = l + 5;
        }
        vector<PCB *> input_table(table);
        sort(table.begin(), table.end(), Compare());
        i = -1;
        PCB *r = nullptr;
        for (auto t : table)
        {
            if (t->bound == "CPU")
            {
                r = t;
                break;
            }
        }

        int cur_time;
        if (r != nullptr)
        {
            waiting.push_back(r);
            r->in_memory = true;
            cur_time = r->at;
        }

        while (!waiting.empty())
        {
            PCB *cur = waiting.front();

            waiting.pop_front();
            if (cur->bound == "IO")
            {
                continue;
            }
            cout << "-------------------------" << endl;
            cout << "Process ID " << cur->pid << " is running" << endl;

            if (cur->remaining_bt == cur->bt)
            {
                cur->rt = cur_time - cur->at;
                avg_rt += cur->rt;
            }

            if (cur->remaining_bt == tqu)
            {
                cur_time += tqu;
                cur->ct = cur_time;
                cur->tat = cur_time - cur->at;
                cur->wt = cur->tat - cur->bt;
                avg_tat += cur->tat;
                avg_wt += cur->wt;
                avg_ct += cur->ct;
                cur->remaining_bt = 0;

                cout << "Process ID " << cur->pid << " Completed" << endl;
            }
            else if (cur->remaining_bt < tqu)
            {
                cur_time += cur->remaining_bt;
                cur->ct = cur_time;
                cur->tat = cur_time - cur->at;
                cur->wt = cur->tat - cur->bt;
                avg_tat += cur->tat;
                avg_wt += cur->wt;
                avg_ct += cur->ct;
                cur->remaining_bt = 0;
            }
            else
            {
                cur_time += tqu;
                cur->remaining_bt -= tqu;
            }
            for (auto s : table)
            {
                if (s->in_memory == false && s->bound == "CPU" && s->at <= cur_time)
                {
                    waiting.push_back(s);
                    s->in_memory = true;
                }
            }
            if (cur->remaining_bt > 0)
            {
                waiting.push_back(cur);
            }

            cout << "Waiting queue(process IDs)status" << endl;

            for (int y = 0; y < waiting.size(); y++)
            {
                cout << waiting[y]->pid << " ";
            }
            cout << endl;
        }
        for (i = 0; i < input_table.size(); i++)
        {
            if (input_table[i]->bound == "IO")
            {
                input_table[i]->tat = input_table[i]->bt;
                input_table[i]->wt = 0;
                input_table[i]->rt = 0;
                input_table[i]->ct = input_table[i]->at + input_table[i]->bt;

                avg_tat += input_table[i]->tat;
                continue;
            }
        }
        out.open("rr.txt", ios::app);
        out << tqu << ",";
        out << avg_rt / n << ",";
        out << avg_ct / n << ",";
        out << avg_tat / n << ",";
        out << avg_wt / n << ",";
        out << endl;
        out.close();
    }
    /*for(auto a:table)
    {
        a.second->PrintPCB();
    }*/

    return 0;
}