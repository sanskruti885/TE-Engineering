#include<iostream>
#include<map>
#include<iomanip>
#include<algorithm>
using namespace std;
class Memory{
    int *blocks;
    int *process;
    int *flag;
    int  b_size;
    int p_size;

    public:
    Memory(){
        b_size = 0;
        p_size = 0;
    }
    void take_input();
    void first_fit();
    void best_fit();
    void worst_fit();
    void next_fit();
    void give_output(map<int,int>,string);
};

void Memory :: take_input(){
    cout<<"\nEnter number of blocks: ";
    cin>>b_size;
    cout<<"\nEnter the number of process: ";
    cin>>p_size;
    blocks = new int[b_size];
    process = new int[p_size];
    flag = new int[b_size];

    cout<<"\nEnter size of the block: ";
    for(int i=0;i<b_size;i++){
        cin>>blocks[i];
    }

    cout<<"\nEnter the size of process: ";
    for(int i=0;i<p_size;i++){
        cin>>process[i];
    }
}
void Memory :: give_output(map<int,int> mp,string str){
    cout<<"-------------------"<<str<<"------------------------\n";
    cout<<"BLock No"<<setw(20)<<"Size of Block"<<setw(20)<<"Size of Process "<<setw(20)<<"Waste memory"<<endl;
    map<int,int>::iterator it;
    for(it = mp.begin();it!=mp.end();it++){
        cout<<it->first<<setw(20)<<blocks[it->first]<<setw(20)<<it->second<<setw(20)<<blocks[it->first]-it->second<<endl;
        // it->first block no., block[it->first] gives block size
    }
}
void Memory :: first_fit(){
    for(int i=0;i<b_size;i++){
        flag[i] = 0;           // denotes free memory block 
    }

    map<int,int> mp; //block number, size of process in it
    map<int,int> :: iterator it;

    for(int i=0;i<p_size;i++){ // for 1 process need to check whole memory
        for(int j=0;j<b_size;j++){ // full memory traversed
            if(process[i]<=blocks[j] && flag[j]==0){
                mp[j] = process[i]; // allocate to the bloc so mp[j]
                flag[j] = 1;        // occupied block
                break;             // very important as if not given travese again and allocate next memory
            }
        }
    }
    string str= "First Fit Algo";
    give_output(mp,str);
}

void Memory :: best_fit(){
    for(int i=0;i<b_size;i++){
        flag[i]=0; //denotes that memory block is free
    }
    int wastage[b_size];

    map<int,int>mp; //blockno and size allocated process
    

    for(int i = 0; i < p_size; i++){
        for(int k = 0; k < b_size; k++){
            wastage[k] = 9999;  // default to large value
        }
        for(int j = 0; j < b_size; j++){
            if(process[i] <= blocks[j] && flag[j] == 0){
                wastage[j] = blocks[j] - process[i];  // store in array wastage wastage = {100,20,50,80}
            }
        }
        // *min_element(wastage[0],wastage[0]+size of block) * therefore returns the number
        int min = *min_element(wastage, wastage + b_size); // find min element from wastage array
        
        if(min == 9999){
            cout << "Process " << process[i] << " cannot be allocated to any block." << endl;
            continue;  // skip to next process
        }
        // find min = ele within wastage to wastage_b_size 
        // since find returns pointer to element substract wastage gives index of element
        int pos = find(wastage, wastage + b_size, min) - wastage;
        mp[pos] = process[i];
        flag[pos] = 1;
    }
    string str= "Best Fit Algo";
    give_output(mp,str);
}

void Memory::next_fit() {
    for (int i = 0; i < b_size; i++) {
        flag[i] = 0; // all blocks free initially
    }

    map<int, int> mp; // block no and process size allocated
    int start_pos = 0; // keeps track of last allocated block position

    for (int i = 0; i < p_size; i++) {
        int proc_size = process[i];
        bool allocated = false;

        // Search circularly from start_pos to find suitable block
        int count = 0;
        int idx = start_pos;

        while (count < b_size) {
            if (flag[idx] == 0 && blocks[idx] >= proc_size) {
                // Allocate process to this block
                flag[idx] = 1;
                mp[idx] = proc_size;
                allocated = true;
                start_pos = idx; // next search starts from here
                break;
            }
            idx = (idx + 1) % b_size;
            count++;
        }

        if (!allocated) {
            cout << "Process " << proc_size << " cannot be allocated to any block." << endl;
        }
    }

    string str = "Next Fit Algorithm";
    give_output(mp, str);
}

int main(){
    Memory m;
    m.take_input();
    m.first_fit();
    m.best_fit();
    m.worst_fit();
}