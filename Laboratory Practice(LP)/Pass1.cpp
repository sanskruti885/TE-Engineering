#include<iostream>
#include<iomanip>
#include<string>
#include<map>
#include<fstream>
#include<sstream>
using namespace std;

// hold line ex MOV R1,5 here MOV->Label, R1->opcode, 5->Operand
struct Line{
    string label,opcode,operand;
    int address;
};

// table storing symbol,address
map<string,int> symbol_table;

// convert hexadecimal to integer A=10
int hextostr(const string &hextstr){
    int x;
    stringstream ss;
    ss<<hex<<hextstr; // convert hex to integer
    ss>>x;
    return x;
}

// remove spaces
Line parse_line(string &l){
    Line parsed;
    string temp = l;
    parsed.label="";
    parsed.opcode="";
    parsed.operand="";

    string first,second,third;
    istringstream iss(temp);
    iss>>first;

    if(first.empty() || first[0] == '.'){
        parsed.opcode = ""; //is empty then opcode is also blank
        return parsed;
    }

    if (first == "START" || first == "END" || first == "WORD" || first == "RESW" || first == "RESB" || first == "BYTE"
        || first == "ADD" || first == "SUB" || first == "MUL" || first == "DIV" || first == "JMP" || first == "COMP"){
            
        }

}
