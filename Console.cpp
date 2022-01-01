#include<iostream>
#include"IF.cpp"
#include"ID.cpp"
using namespace std;

int main(){
        /*
    Test
    add $1, $2, $3
    sub $4, $5, $6
    lw $7, 12($8)
    sw $9, 24(&10)
    beq $11, $12, 5
    */

    // 之後改讀檔
    string instruction;
    getline(cin,instruction);

    IF IFF(instruction); // 指定切割->放進IFID
    ID idd(IFID.opcode,IFID.rs,IFID.rt,IFID.rd,IFID.addr);
    

    return 0;
}
/*
ID test
    cout<< idd.ret()<<endl;
    cout<<idd.RegDst<<endl;
    cout<<idd.RegWrite<<endl;
    cout<<idd.ALUSrc<<endl;
    cout<<idd.MemRead<<endl;
    cout<<idd.MemWrite<<endl;
    cout<<idd.MemToReg<<endl;
    cout<<idd.Branch<<endl;
    cout<<idd.ALUOp<<endl;
*/