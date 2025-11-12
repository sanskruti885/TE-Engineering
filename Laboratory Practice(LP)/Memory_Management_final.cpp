#include<iostream>
#include<algorithm>
#include<iomanip>
#include<map>
using namespace std;

class Memory{
    int *blocks,*flags,*process;
    int b_size,p_size;
public:
    Memory(){
        b_size=0;
        p_size=0;
    }
    void take_input();
    void display_output(string,map<int,int>);
    void first_fit();
    void best_fit();
    void worst_fit();
    void next_fit();
};

void Memory :: take_input(){
    cout<<"\nEnter block number: ";
    cin>>b_size;
    cout<<"\nENter process number: ";
    cin>>p_size;

    blocks = new int[b_size];
    process = new int[p_size];
    flags = new int[b_size];

    cout<<"\nEnter blocks: ";
    for(int i=0;i<b_size;i++){
        cin>>blocks[i];
    }

    cout<<"\nEnter processes: ";
    for(int i=0;i<p_size;i++){
        cin>>process[i];
    }
}

void Memory :: display_output(string s, map<int,int> mp){
    cout<<"------------"<<s<<"---------------"<<endl;

    cout<<"Block No."<<setw(20)<<"Block size"<<setw(20)<<"Process size"<<setw(20)<<"Wastage"<<endl;
    for(auto it= mp.begin();it!=mp.end();it++){
        cout<<it->first<<setw(20)<<blocks[it->first]<<setw(20)<<it->second<<setw(20)<<blocks[it->first]-it->second<<endl;
    }
}

void Memory :: first_fit(){
    map<int,int> mp;
    int *process_not_alloctated = new int[p_size];

    for(int i=0;i<b_size;i++) flags[i] = 0;
    for(int i=0;i<p_size;i++) process_not_alloctated[i]=0;

    for(int i=0;i<p_size;i++){
        for(int j=0;j<b_size;j++){
            if(process[i]<=blocks[j] && flags[j] == 0){
                mp[j] = process[i];
                flags[j] = 1;
                process_not_alloctated[i]=1;
                break;
            }
        }
    }
    cout<<"\nProcess not allocated\n";
    for(int i=0;i<p_size;i++){
        if(process_not_alloctated[i] == 0){
            cout<<"Process "<<process[i]<<endl;
        }    
    }
    display_output("First Fit",mp);
}

void Memory :: best_fit(){
    map<int,int> mp;
    int *process_not_alloctated = new int[p_size];

    for(int i=0;i<b_size;i++) flags[i] = 0;
    for(int i=0;i<p_size;i++) process_not_alloctated[i]=0;
    
    int wastage[b_size];

    for(int i=0;i<p_size;i++){
        for(int j=0;j<b_size;j++) wastage[j] = 9999;
        for(int k=0;k<b_size;k++){
            if(process[i]<=blocks[k] && flags[k] == 0){
                wastage[k] = blocks[k] - process[i];
            }
        }

        int min_val = *min_element(wastage,wastage+b_size);
        
        if(min_val == 9999){
            process_not_alloctated[i] = 0;
            continue;
        }

        int pos = find(wastage,wastage+b_size,min_val)-wastage;
        mp[pos] = process[i];
        flags[pos] = 1;
        process_not_alloctated[i] = 1;
    }
    cout<<"\nProcess not allocated\n";
    for(int i=0;i<p_size;i++){
        if(process_not_alloctated[i] == 0){
            cout<<"Process "<<process[i]<<endl;
        }    
    }
    display_output("Best Fit",mp);
}
void Memory :: worst_fit(){
    map<int,int> mp;
    int *process_not_alloctated = new int[p_size];

    for(int i=0;i<b_size;i++) flags[i] = 0;
    for(int i=0;i<p_size;i++) process_not_alloctated[i]=0;
    
    int wastage[b_size];

    for(int i=0;i<p_size;i++){
        for(int j=0;j<b_size;j++) wastage[j] = -1;
        for(int k=0;k<b_size;k++){
            if(process[i]<=blocks[k] && flags[k] == 0){
                wastage[k] = blocks[k] - process[i];
            }
        }

        int max_val = *max_element(wastage,wastage+b_size);
        
        if(max_val == -1){
            process_not_alloctated[i] = 0;
            continue;
        }

        int pos = find(wastage,wastage+b_size,max_val)-wastage;
        mp[pos] = process[i];
        flags[pos] = 1;
        process_not_alloctated[i] = 1;
    }
    cout<<"\nProcess not allocated\n";
    for(int i=0;i<p_size;i++){
        if(process_not_alloctated[i] == 0){
            cout<<"Process "<<process[i]<<endl;
        }    
    }
    display_output("Worst Fit",mp);
}
void Memory :: next_fit(){
    map<int,int> mp;
    int *process_not_alloctated = new int[p_size];

    for(int i=0;i<b_size;i++) flags[i] = 0;
    for(int i=0;i<p_size;i++) process_not_alloctated[i]=0;

    int last_allocated = 0;
    int j = 0,checked_block = 0;
    bool allocated;

    for(int i=0;i<b_size;i++){
        last_allocated = j;
        allocated = false;
        checked_block=0; 
        while(checked_block<b_size){
            if(process[i]<=blocks[j] && flags[j] == 0){
                mp[j] = process[i];
                flags[j] = 1;
                allocated = true;

            }
            j = (j+1) % b_size;
            checked_block ++;
        }
        if(!allocated){
            process_not_alloctated[i] = 0;
        }
    }
    cout<<"\nProcess not allocated\n";
    for(int i=0;i<p_size;i++){
        if(process_not_alloctated[i] == 0){
            cout<<"Process "<<process[i]<<endl;
        }    
    }
    display_output("Worst Fit",mp);
}
int main(){
    Memory m;

    m.take_input();
    m.first_fit();
    m.best_fit();
    m.worst_fit();
    m.next_fit();
    return 0; 
}
