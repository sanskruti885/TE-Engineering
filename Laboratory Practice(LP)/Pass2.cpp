#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream>
#include<unordered_map>
#include<sstream>
using namespace std;

unordered_map<string,int> readSymbol(const string &filename){
    unordered_map<string,int> symTable;
    ifstream file(filename);
    string line,symbol;
    int address;
    while(getline(file,line)){
        istringstream iss(line);
         if (!(iss >> symbol >> address)) {
            cerr << "Invalid symbol table line: " << line << '\n';
            continue;
        }
        symTable[symbol] = address;
        cout<<symbol<<" "<<address;
    }
    return symTable;
}
unordered_map<string,int> readLiteral(const string &filename){
    unordered_map<string,int> litTable;
    ifstream file(filename);
    string line,literal;
    int address;
    while(getline(file,line)){
        istringstream iss(line);
         if (!(iss >> literal >> address)) {
            cerr << "Invalid symbol table line: " << line << '\n';
            continue;
        }
        litTable[literal] = address;
    }
}

pair<string,string> parseToken(const string &token){
    if(token.empty()) return {"",""};
    // check start and end (IS,01)
    if(token.front() == '(' && token.back() == ')'){
        string inner  = token.substr(1,token.size()-2); // (IS,01) then size=2, 1 index skip ( token.size()-2 means 7-2=5 total 5 char from index 1
        size_t commaPos = inner.find(',')
    }
}
int main(){
    
}
