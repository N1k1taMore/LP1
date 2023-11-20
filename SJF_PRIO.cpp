#include<bits/stdc++.h>
using namespace std;
class process{
    int id,at,bt,ct,tat,wt,rt;
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
    void getProcess(){
        cout<<"enter number of processes: ";
        cin>>n;
        process m;
        for(int i=0;i<n;i++){
            cout<<"process id:: "<<(i+1)<<endl;
            m.id=(i+1);
            cout<<"\t\tArrival time:: ";
            cin>>m.at;           
            cout<<"\t\tburst time:: ";
            cin>>m.bt;            
            m.rt=m.bt;         
            p.push_back(m);
        }
    }
    void printtable(){
        int n=p.size();
        cout<<"Process\tAT\tBT\tCT\tTAT\tWT\n";
        for(int i=0;i<n;i++){
            cout<<p[i].id<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"<<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<endl;
        }
    }
    void sort_process_by_at(){
        int n = p.size();
        process temp;
        for(int i=0;i<n;i++){
            for(int j=0;j<n-i-1;j++){
                if(p[j].at>p[j+1].at){
                    temp=p[j];
                    p[j]=p[j+1];
                    p[j+1]=temp;
                }
            }
        }
    }
    void sjf_preemptive(){
        sort_process_by_at();
        int curr_time = 0;
        int completed = 0;
        vector<int> visited(n, 0);

        while (completed < n) {
            int min_bt = INT_MAX, shortest = -1;
            for (int i = 0; i < n; i++) {
                if (p[i].at <= curr_time && p[i].rt < min_bt && p[i].rt > 0) {
                    min_bt = p[i].rt;
                    shortest = i;
                }
            }

            if (shortest == -1) {
                curr_time++;
                continue;
            }

            p[shortest].rt--;
            curr_time++;

            if (p[shortest].rt == 0) {
                completed++;
                p[shortest].ct = curr_time;
                p[shortest].tat = p[shortest].ct - p[shortest].at;
                p[shortest].wt = p[shortest].tat - p[shortest].bt;
            }
        }

        int totalTat = 0, totalWt = 0;
        float avgTat = 0, avgWt = 0;

        for (int i = 0; i < n; i++) {
            totalTat += p[i].tat;
            totalWt += p[i].wt;
        }

        avgTat = (float)totalTat / n;
        avgWt = (float)totalWt / n;

        printtable();
        cout << endl;

        cout << "Average TAT :: " << avgTat << endl;
        cout << "Average WT :: " << avgWt << endl;
    }

    void priority_non_preemptive(){
        int pa[n];
        cout<<"Enter priorities"<<endl;
        for (int i = 0; i < n; i++) {
            cin>>pa[i];
        }

        int curr_time=0;
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    if (pa[j] > pa[j + 1]) {
                        swap(pa[j], pa[j + 1]);
                        swap(p[j], p[j + 1]);
                    }
                }
            }
        
        while(true){
            int highest_priority_index=-1;
            int highest_priority=INT_MAX;
            bool isCompleted=true;

            for(int i=0;i<n;i++){
                if(p[i].rt>0){
                    isCompleted=false;
                    if(p[i].at <= curr_time){
                        if(pa[i]<highest_priority){
                            highest_priority=pa[i];
                            highest_priority_index=i;
                        }
                    }
                }
            }
            if(isCompleted){
                break;
            }
            curr_time=curr_time+p[highest_priority_index].bt;
            p[highest_priority_index].ct=curr_time;
            p[highest_priority_index].rt=0;

        }
        int totalTat = 0, totalWt = 0;
        float avgTat = 0, avgWt = 0;
        for(int i=0;i<n;i++){
            p[i].tat=p[i].ct-p[i].at;
            p[i].wt=p[i].tat-p[i].bt;
            totalTat+=p[i].tat;
            totalWt+=p[i].wt;
        }
    

        avgTat = (float)totalTat / n;
        avgWt = (float)totalWt / n;
        printtable();
        cout << endl;

        cout << "Average TAT :: " << avgTat << endl;
        cout << "Average WT :: " << avgWt << endl;
    }

};
int main(){
    scheduling s;
    s.getProcess();
    s.sjf_preemptive();
    s.priority_non_preemptive();
}