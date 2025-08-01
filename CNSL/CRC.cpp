#include<iostream>
#include<cstring>
using namespace std;

int exor(char a, char b){
    char bit = (a==b)?0:1;
}

void crc(char data[], char divisor[]){
    // add zeroes at end of data, no. zero = divisor-1
    char original[50];
    strcpy(original,data) ;//inorder to append 
    int datalen = strlen(data);
    int divlen = strlen(divisor);

    // length of data is 5 =0-4 
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

        }

    }
}

int main(){
    char data[100],divisor[100];

    cout<<"\nEnter data: ";
    cin>>data;
    cout<<"\nEnter key: ";
    cin>>divisor;
    crc(data,divisor);
    return 0;
}