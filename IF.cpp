#include<iostream>
#include<vector>
#include<cstring>
#include<sstream>
using namespace std;

struct reg_IFID {
    string opcode;
    int rs;   // 站存器的編號
    int rt;   // 同上
    int rd;   // 如果是站存器，就放暫存器的編號，否則先填-1
    int addr; // 如果rd是-1，這裡要填地址(word)
}IFID;

class IF {
public: 
    IF(string instr) {
        set(instr);
    }
private:
    vector<string> data;
    string instruction;
    void set(string instr){
        instruction = instr;
        spilt();
    }
    void spilt(){
        // 切割字串
        char instruct[30];
        strcpy(instruct,instruction.c_str());
        char *p = strtok(instruct," ");  
        while(p){
            data.push_back(p);
            p = strtok(NULL," ,$()");
        }
        judge();
    }
    void judge(){
        // 判斷opcode->完成封包
        IFID.opcode = data[0];
        
        if(data[0] == "lw" || data[0] == "sw"){
            IFID.rs = stoi(data[3]);
            IFID.rt = stoi(data[1]);
            IFID.rd = -1;
            IFID.addr = stoi(data[2]);
        }
        else if(data[0] == "beq"){
            IFID.rs = stoi(data[1]);
            IFID.rt = stoi(data[2]);
            IFID.rd = -1;
            IFID.addr = stoi(data[3]);
        }
        else{ // R-format
            IFID.rs = stoi(data[2]);
            IFID.rt = stoi(data[3]);
            IFID.rd = stoi(data[1]);
        }
    }       
};