#include <bits/stdc++.h>
using namespace std;

class ID
{
    struct IFID
    {
        string op;
        int rs;
        int rt;
        int rd;
        int addr;
    };

public:
    // class var
    IFID instruction;
    int registerTable[32] = {0};
    // control unit
    bool RegDst = 0;
    bool ALUSrc = 0;
    bool MemToReg = 0;
    bool RegWrite = 0;
    bool MemRead = 0;
    bool MemWrite = 0;
    bool Branch = 0;
    int ALUOp = 0;

    // constructor
    ID(string op, int rs, int rt, int rd, int addr)
    {
        // var init
        instruction.op = op;
        instruction.rs = rs;
        instruction.rt = rt;
        instruction.rd = rd;
        instruction.addr = addr;

        // init
        for (int i = 1; i < 32; i++)
        {
            registerTable[i] = 1;
        }

        // func call
        ControlUnit();
    }

    // control unit
    void ControlUnit()
    {
        if (instruction.op == "add" || instruction.op == "sub")
        {
            RegDst = 1;
            ALUOp = 2;
            ALUSrc = 0;
            Branch = 0;
            MemRead = 0;
            MemWrite = 0;
            RegWrite = 1;
            MemToReg = 0;
        }
        else if (instruction.op == "lw")
        {
            RegDst = 0;
            ALUOp = 0;
            ALUSrc = 1;
            Branch = 0;
            MemRead = 1;
            MemWrite = 0;
            RegWrite = 1;
            MemToReg = 1;
        }
        else if (instruction.op == "sw")
        {
            RegDst = 1; // X
            ALUOp = 0;
            ALUSrc = 1;
            Branch = 0;
            MemRead = 0;
            MemWrite = 1;
            RegWrite = 0;
            MemToReg = 0; // X
        }
        else if (instruction.op == "beq")
        {
            RegDst = 1; // X
            ALUOp = 1;
            ALUSrc = 0;
            Branch = 1;
            MemRead = 0;
            MemWrite = 0;
            RegWrite = 0;
            MemToReg = 0; // X
        }
    }

    // write data
    void WriteData(int data)
    {
        if (instruction.rd == -1)
        {
            instruction.rt = data;
        }
        else
        {
            instruction.rd = data;
        }
    }

    // clock pulse
    string ret()
    {
        return instruction.op;
    }
};

// int main()
// {
//     ID id("add", 1, 2, 3, 0);
//     cout << id.instruction.op << endl;
//     cout << id.instruction.rs << endl;
//     cout << id.instruction.rt << endl;
//     cout << id.instruction.rd << endl;
//     cout << id.instruction.addr << endl;
//     cout << id.RegDst << endl;
//     cout << id.ALUOp << endl;
//     cout << id.ALUSrc << endl;
//     cout << id.Branch << endl;
//     cout << id.MemRead << endl;
//     cout << id.MemWrite << endl;
//     cout << id.RegWrite << endl;
//     cout << id.MemToReg << endl;

//     return 0;
// }