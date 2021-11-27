#include <bits/stdc++.h>
using namespace std;

int main(int argv, char *argc[])
{
    /*Read From File*/
    /*
    4
    1,darshan,11,2.0,IO
    2,chomr,1,3.5,CPU
    3,ipad,8,4,IO
    4,mouse,13,5,IO*/
    ifstream inp("input1.txt");
    
    string readed_data;
    getline(inp, readed_data);
    int n, i;
    //cout<<readed_data;
    n = stoi(readed_data);

    map<int, pair<float, float>> stat;                 //<id,<tat,wt>>
    map<int, pair<float, float>> stat1;                //<id,<ct,rt>>
    vector<pair<float, pair<int, float>>> input_table; //<at,<id,bt>>
    vector<string> pname, arguments, bound;
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
    for (int l = 0; l < arguments.size();)
    {
        pname.push_back(arguments[l + 1]);

        float b, c;
        int a = stoi(arguments[l + 0]);
        b = stof(arguments[l + 2]);
        c = stof(arguments[l + 3]);
        bound.push_back(arguments[l + 4]);
        input_table.push_back({b, {a, c}});
        l = l + 5;
    }

    vector<pair<float, pair<int, float>>> process(input_table);
    sort(process.begin(), process.end());

    float cur_time = process[0].first;
    float avg_tat = 0, avg_wt = 0, avg_ct = 0,avg_rt=0;
    for (int i = 0; i < n; i++)
    {
        if (bound[i] == "IO")
        {
            cout << "-------------------------" << endl;
            cout << "Process ID " << input_table[i].second.first << " is running" << endl;
            stat[input_table[i].second.first] = {input_table[i].second.second, 0};
            stat1[input_table[i].second.first] = {input_table[i].first + input_table[i].second.second, 0};
            avg_ct += input_table[i].first + input_table[i].second.second;
            avg_tat += input_table[i].second.second;
            cout << "Process ID " << input_table[i].second.first << " is Completed" << endl;
            continue;
        }
        if (cur_time >= process[i].first)
        {
            cout << "-------------------------" << endl;
            cout << "Process ID " << process[i].second.first << " is running" << endl;
            stat1[process[i].second.first] = {cur_time + process[i].second.second, cur_time - process[i].first};
            avg_rt+=cur_time-process[i].first;
            cur_time = cur_time + process[i].second.second;
            float t = cur_time - process[i].first;
            float g = t - process[i].second.second;
            stat[process[i].second.first] = {t, g};
            
            avg_tat += t;
            avg_wt += g;
            
            cout << "Process ID " << process[i].second.first << " is Completed" << endl;
        }
        else
        {
            cout << "-------------------------" << endl;
            cout << "Process ID " << process[i].second.first << " is running" << endl;
            stat1[process[i].second.first] = {cur_time + process[i].second.second, cur_time - process[i].first};
            avg_rt+=cur_time-process[i].first;
            cur_time = process[i].first;
            cur_time = cur_time + process[i].second.second;
            float t = cur_time - process[i].first;
            float g = t - process[i].second.second;
            stat[process[i].second.first] = {t, g};
            avg_tat += t;
            avg_wt += g;
            cout << "Process ID " << process[i].second.first << " is Completed" << endl;
        }
        avg_ct += cur_time;
    }
    ofstream out,out4;
    out.open("output11.txt", ios::trunc);
    out4.open("output13.txt", ios::trunc);
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
    auto it = stat1.begin();

    for (auto s : stat)
    {
        out << s.first
            << ","
            << pname[i]
            << ","
            << input_table[i].first
            << ","
            << input_table[i].second.second
            << ","
            << bound[i]
            << ","
            << it->second.second
            << ","
            << it->second.first
            << ","
            << s.second.first
            << ","
            << s.second.second
            << endl;
            out4  << pname[i]
             << ","
             << it->second.second
             << ","
             << s.second.first
             << ","
             << s.second.second
             << endl;
        i++;
        it++;
    }
    out<<avg_rt/n<<endl;
    out << avg_ct / n << endl;
    out << avg_tat / n << endl;
    out << avg_wt / n << endl;
    out.close();
    
    out.open("output12.txt", ios::trunc);
    out<<avg_rt/n<<endl;
    out << avg_ct / n << endl;
    out << avg_tat / n << endl;
    out << avg_wt / n << endl;
    out.close();
    inp.close();
    return 0;
}
