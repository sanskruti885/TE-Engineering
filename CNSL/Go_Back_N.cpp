#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

int main(){
    int no_f,N,no_tr=0; //no frame,window size
    srand(time(NULL)); // rand() should produce different sequence, current time is given as seed
    cout<<"Enter number of frames: ";
    cin>>no_f;
    cout<<"\nEnter window size: ";
    cin>>N;

    int i=1;
    while(i<=no_f){ //continue until no all frames tranfer
        
        int ack_got = 0;

        // Send the frame, j<=no_f so that the frame should not go out of the frame size ex:i=5,frame_size=6,window_size=3, then 5+3 = 8>frame_size so out of ArrayBound
        for(int j=i;j<i+N && j<=no_f;j++){ // if i=2 , window size=4 then 2+4=6 j<6 2-5 should be window size 
            cout<<"\nSent Frame: "<<j;
            no_tr++;
        }

        // Receive the frame
        for(int j=i;j<i+N && j<=no_f;j++){
            int flag = rand()%2; //generate 0,1 if 0 then ack received or else not
            if(!flag){ //flag=0
                cout<<"\nAcknowledgment Received"<<j<<endl;
                ack_got++; //slide window since adding this to i later
            }
            else{ //flag = 1
                cout<<"\nFrame "<<j<<" Not Received "<<endl;
                cout<<"\nRetransmitting it";
                break; // ack_got not set so same frame transfered again 
            }
        }
        cout<<endl;
        i+=ack_got; // for retransmit the ack_got not set

    }
    cout<<"\nTotal umber of transmission: "<<no_tr;
    return 0;

}
