#include<bits/stdc++.h>
using namespace std;

class process{
    int id,at,bt,ct,tat,wt,rt;

    //rt is used to save burst time only so that it can be manipulated during roundrobin
    public:
    process(){
        id=0;
        at=0;
        bt=0;
        ct=0;
        tat=0;
        wt=0;
        rt=0;
    }
    friend class scheduling;
};
class scheduling{
    int n;
    vector<process>p;
    public:
    
    void getprocess(){
        cout<<"Enter number of process :: ";
        cin>>n;
        process m;
        for(int i = 0; i < n; i++){   
            cout << "Process ID : "<<(i+1)<<endl;
            m.id = (i+1);
            cout<<"\t\tArrival time :: ";
            cin>>m.at;
            cout<<"\t\tBurst Time :: ";
            cin>>m.bt;
            m.rt = m.bt;
            p.push_back(m);
        }

    }
    void printtable(){
        int n=p.size();
        cout<<"Process\tAT\tBT\tCT\tTAT\tWT\n";
        for(int i=0;i<n;i++){
            cout<<p[i].id<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<"\n";
        }
    }

    void sort_process_by_at(){
        int n = p.size();
        process temp;
        for(int i = 0 ; i < n; i++){
            for(int j = 0; j< n-i-1; j++){
                if (p[j].at > p[j+1].at) {
                    temp = p[j];
                    p[j] = p[j+1];
                    p[j+1] = temp;
                }
            }
        }
    }
    void Fcfs(){
        sort_process_by_at();
        for(int i=0;i<n;i++){
            if(i==0){
                p[i].ct=p[i].bt;
            }
            else{
                p[i].ct=p[i-1].ct+p[i].bt;
            }
        }
        int totalTat = 0, totalWt = 0;
        float avgTat = 0, avgWt = 0;

        for(int i = 0 ; i < n ; i++){
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            totalTat+=p[i].tat;
            totalWt += p[i].wt;
        }

        avgTat = (float)totalTat/n;
        avgWt = (float)totalWt/n;

        printtable();
        cout<<endl;
        
        cout<<"Average TAT :: "<<avgTat<<endl;
        cout<<"Average WT :: "<<avgWt<<endl;
    }
    void roundrobin(){
        int qt;
        cout<<"\nEnter time quantum :: ";
        cin>>qt;
        sort_process_by_at();
        int curr_time = 0;
        queue<int> q;
        vector<int> visited(n,0);

        q.push(0);
        visited[0]=1;

        while(!q.empty()){
            int index = q.front();
            q.pop();
            curr_time+=min(p[index].rt,qt);
            p[index].rt -= min(p[index].rt,qt);

            if(p[index].rt == 0){
                visited[index] = 1;
                p[index].ct = curr_time;
            }

            for(int i = 0; i < n; i++){
                if(visited[i]==0 && p[i].at <= curr_time){
                    q.push(i);
                    visited[i] = 1;
                }
            }

            if(p[index].rt != 0){
                q.push(index);
            }
        }

        int totalTat = 0, totalWt = 0;
        float avgTat = 0, avgWt = 0;

        for(int i = 0 ; i < n ; i++){
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            totalTat+=p[i].tat;
            totalWt += p[i].wt;
        }

        avgTat = (float)totalTat/n;
        avgWt = (float)totalWt/n;

        printtable();
        cout<<endl;
        
        cout<<"Average TAT :: "<<avgTat<<endl;
        cout<<"Average WT :: "<<avgWt<<endl;
    }
};
int main(){

    scheduling s;
    s.getprocess();
    s.Fcfs();
    s.roundrobin();
}



