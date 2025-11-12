#include<iostream>
using namespace std;

class Mutex_Semaphore{
    int empty,full,signal;
public:
    Mutex_Semaphore(){
        empty = 0;
        full = 0;
        signal = 1;
    }
    void take_buffer_size(){
        cout<<"\nENter buffer size: ";
        cin>>empty;
    }
    void signalE(){
        empty++;
    }
    void waitE(){
        empty--;
    }
    void signalF(){
        full++;
    }
    void waitF(){
        full--;
    }
    void signalS(){
        signal++;
    }
    void waitS(){
        signal--;
    }
    void display(){
        cout<<"Status: "<<signal<<endl<<"Occupied Buffer: "<<full<<endl<<"Empty Buffer: "<<empty;
    }
    void Producer(){
        cout<<"\nIn producer\n";
        if(signal==1 && empty>0){
            waitS();
            waitE();
            signalF();
            display();
            signalS();
            cout<<"\nProduced\n";
        }
        else{
            cout<<"\nCannot produce: Overflow\n";
        }
    }
    void Consumer(){
        cout<<"\nIn Consumer\n";
        if(signal==1 && full>0){
            waitS();
            waitF();
            signalE();
            display();
            signalS();
            cout<<"\nConsumed\n";
        }else{
            cout<<"\nCannot consume:underflow\n";
        }
    }
};
int main(){
    Mutex_Semaphore m;
    int choice=-1;

    m.take_buffer_size();
    while(choice!=4){
        cout<<"\n1.Produce";
        cout<<"\n2.Consume";
        cout<<"\n3.Display";
        cout<<"\n4.Exit";
        cin>>choice;

        switch(choice){
            case 1:
                m.Producer();
                break;
            case 2:
                m.Consumer();
                break;
            case 3:
                m.display();
                break;
            case 4:
                cout<<"\nExiting simulation\n";
                break;
            default:
                cout<<"\nWrong choice\n";
        }
    }
}