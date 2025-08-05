#include<iostream>
#include<cstring>
#include<vector>
using namespace std;

int exor(char a, char b){
    char bit = (a==b)?'0':'1';
    return bit;
}

string crc(char data[], char divisor[]){
    // add zeroes at end of data, no. zero = divisor-1
    char original[50];
    strcpy(original,data) ;//inorder to append 
    int datalen = strlen(data);
    int divlen = strlen(divisor);

    // length of data is 5 =0-4 no. zero 5-1 =4
    for(int i=0;i<divlen-1;i++){
        data[datalen+i] = '0'; //data[5+0] since index 5 has no data 
    }

    data[datalen+divlen-1] = '\0'; // end of data;

    int codelen = datalen+divlen - 1; // actual length after adding 0's

    char temp[50],rem[50];

    for(int i=0;i<divlen;i++){  // initially store the first divisor length digit of data in remainder
        rem[i] = data[i];       // ex: data = 1001, divisor = 101, after zero = 100100 rem[0]=1,rem[1]=0,rem[2]=0 divlen=3
    }

    for(int j=divlen;j<=codelen;j++){ // check from divlen index liken 0-2 is rem check from 3
        for(int i=0;i<divlen;i++){  // store remainder in 
            temp[i] = rem[i];
        }

        if(rem[0] == '0'){ //xor with 0's and skip leftmost bit
            for(int i=0;i<divlen-1;i++){
                rem[i] = temp[i+1];   // store all same digit in rem[1],rem[2]
            } 
        }else{
            for(int i=0;i<divlen-1;i++){ // ignore rem[0] and in rem[0] store then exor 
                rem[i] = exor(temp[i+1],divisor[i+1]); //ignore first element
            }
        }

        if(j!=codelen)
            rem[divlen-1] = data[j];
        else
            rem[divlen-1] = '\0'; 
    }

     for(int i=0;i<divlen-1;i++)
        data[datalen+i]=rem[i];

    data[codelen]='\0';
    cout<<"CRC="<<rem<<"\nDataword="<<data;
    return string(data);
}
bool checkCRC(char data[], char divisor[]) {
    int datalen = strlen(data);
    int divlen = strlen(divisor);

    char temp[100], rem[100];

    // Copy the first 'divlen' bits to rem
    for (int i = 0; i < divlen; i++) {
        rem[i] = data[i];
    }

    for (int j = divlen; j <= datalen; j++) {
        for (int i = 0; i < divlen; i++) {
            temp[i] = rem[i];
        }

        if (rem[0] == '0') {
            for (int i = 0; i < divlen - 1; i++) {
                rem[i] = temp[i + 1];
            }
        } else {
            for (int i = 0; i < divlen - 1; i++) {
                rem[i] = exor(temp[i + 1], divisor[i + 1]);
            }
        }

        if (j != datalen)
            rem[divlen - 1] = data[j];
    }

    // Check if remainder is all 0s
    for (int i = 0; i < divlen - 1; i++) {
        if (rem[i] != '0')
            return false; // Error detected
    }

    return true; // No error
}


int main(){
    char data[100],divisor[100];

    cout<<"\nEnter data: ";
    cin>>data;
    cout<<"\nEnter key: ";
    cin>>divisor;
    string dataword = crc(data,divisor);
    
    char received[100];
    dataword ="100101";
    strcpy(received,dataword.c_str());
    // received = "100101";
    if(checkCRC(received,divisor)){
        cout<<"\nNo Error: Dataword is uncorrupted.\n";
    }else{
        cout<<"\nError: Dotaword is corrupted";
    }

    return 0;
}