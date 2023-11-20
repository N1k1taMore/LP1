#include<bits/stdc++.h>
using namespace std;

class Page{
    public:
    void queue_fun(queue<int>q){
        while(!q.empty()){
            cout<<q.front()<<" ";
            q.pop();
        }
    }

    bool checkhit(queue<int>q,int temp){
        bool t=0;
        while(!q.empty()){
            if(q.front()==temp){
                t=1;
                break;
            }
            else{
                q.pop();
            }
        }
        return t;
    }

    void fifo(){
        int n,frame;
        cout<<"Enter the size of frame :"<<endl;
        cin>>frame;
        cout<<"Enter the size of sequence :"<<endl;
        cin>>n;
        cout<<"Enter the pages in sequence :"<<endl;
        int pagefault=0;
        int hit=0;
        int temp;
        queue<int>q;
        for(int i=0;i<n;i++){
            cin>>temp;

            if(checkhit(q,temp)){
                hit++;
                continue;
            }
            else{
                pagefault++;
                if(q.size()>=frame){
                    q.pop();
                    q.push(temp);
                }
                else{
                    q.push(temp);
                }
                
            }
        }
        cout<<"The page fault in fifo :"<<pagefault<<endl;
        cout<<"The hit count in fifo :"<<hit<<endl;
    }

    bool search(int key,vector<int>&fr){
        for(int i=0;i<fr.size();i++){
            if(fr[i]==key){
                return true;
            }
        }
        return false;
    }

    int predict(int pg[],vector<int>&fr,int pn,int index){
        //pg is the sequence
        //fr is vector to store sequence in frames
        //pn is size of sequence 
        //index is the location+1 of page in pg

        int res=-1;
        int farthest=index;
        for(int i=0;i<fr.size();i++){
            int j;
            for(j=index;j<pn;j++){
                if(fr[i]==pg[j]){
                    if(j>farthest){
                        farthest=j;
                        res=i;
                    }
                    break;
                }
            }
            if(j==pn){
                return i;
            }
        }
        if(res==-1){
            return 0;
        }
        else{
            return res;
        }
    }

    void Optimal(){
        int n,frame;
        cout<<"Enter the size of frame :"<<endl;
        cin>>frame;
        cout<<"Enter the size of sequence :"<<endl;
        cin>>n;
        vector<int>F;
        int hit=0;
        int pagefault=0;
        int page[n];
        cout<<"Enter the pages in sequence :"<<endl;
        for(int i=0;i<n;i++){
            cin>>page[i];
        }
        for(int i=0;i<n;i++){
            if(search(page[i],F)){
                hit++;
            }
            else if(F.size()<frame){
                pagefault++;
                F.push_back(page[i]);
            }
            else{
                pagefault++;
                int j=predict(page,F,n,i+1);
                F[j]=page[i];
            }
            for(int i=0;i<F.size();i++){
                cout<<F[i]<<" ";
            }
            cout<<endl;
        }
        cout << "Page Faults of Optimal is : " << pagefault<< endl;
        cout << "Page Hits of Optimal is : " << hit << endl;

    }

    void Lru(){
        int n,frame;
        cout<<"Enter the size of frame :"<<endl;
        cin>>frame;
        cout<<"Enter the size of sequence :"<<endl;
        cin>>n;
        int hit=0;
        int pagefault=0;
        int page[n];
        cout<<"Enter the pages in sequence :"<<endl;
        for(int i=0;i<n;i++){
            cin>>page[i];
        }
        unordered_set<int>s;
        unordered_map<int,int>indexes;  //store page value index in page in sequence
        for(int i=0;i<n;i++){
            if(s.size()<frame){
                if(s.find(page[i])==s.end()){
                    s.insert(page[i]);
                    pagefault++;
                }
                else{
                    hit++; 
                }
                 indexes[page[i]] = i;

            }
            else{
                if(s.find(page[i])==s.end()){     
                    int lru=INT_MAX,val;  //sequence number
                    for(auto it=s.begin();it!=s.end();it++){
                        if(indexes[*it]<lru){    
                            lru=indexes[*it];
                            val=*it;
                        }
                    }
                    s.erase(val);
                    s.insert(page[i]);
                    pagefault++;
                }
                else{
                    hit++;
                }
                indexes[page[i]]=i;
            }
        }
        cout << "Page Faults of lru is : " << pagefault<< endl;
        cout << "Page Hits of lru is : " << hit << endl;
    }
};
int main(){
    Page p;
   // p.fifo();
    p.Optimal();
}