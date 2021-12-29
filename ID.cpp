#include <bits/stdc++.h>
using namespace std;

// return struct type
struct reg_IDEXE
{
    string op;
    int rs;
    int rt;
    int rd;
    int addr;
    bool RegDst = 0;
    bool ALUSrc = 0;
    bool MemToReg = 0;
    bool RegWrite = 0;
    bool MemRead = 0;
    bool MemWrite = 0;
    bool Branch = 0;
    int ALUOp = 0;
};

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

private:
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

    // control unit
    void ControlUnit()
    {
        if (instruction.op == "add" || instruction.op == "sub")
        {
            this->RegDst = 1;
            this->ALUOp = 2;
            this->ALUSrc = 0;
            this->Branch = 0;
            this->MemRead = 0;
            this->MemWrite = 0;
            this->RegWrite = 1;
            this->MemToReg = 0;
        }
        else if (instruction.op == "lw")
        {
            this->RegDst = 0;
            this->ALUOp = 0;
            this->ALUSrc = 1;
            this->Branch = 0;
            this->MemRead = 1;
            this->MemWrite = 0;
            this->RegWrite = 1;
            this->MemToReg = 1;
        }
        else if (instruction.op == "sw")
        {
            this->RegDst = 1; // X
            this->ALUOp = 0;
            this->ALUSrc = 1;
            this->Branch = 0;
            this->MemRead = 0;
            this->MemWrite = 1;
            this->RegWrite = 0;
            this->MemToReg = 0; // X
        }
        else if (instruction.op == "beq")
        {
            this->RegDst = 1; // X
            this->ALUOp = 1;
            this->ALUSrc = 0;
            this->Branch = 1;
            this->MemRead = 0;
            this->MemWrite = 0;
            this->RegWrite = 0;
            this->MemToReg = 0; // X
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

public:
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

    // data to next stage
    reg_IDEXE ret()
    {
        reg_IDEXE idexe;

        idexe.op = instruction.op;
        idexe.rs = instruction.rs;
        idexe.rt = instruction.rt;
        idexe.rd = instruction.rd;
        idexe.addr = instruction.addr;
        idexe.RegDst = this->RegDst;
        idexe.ALUSrc = this->ALUSrc;
        idexe.MemToReg = this->MemToReg;
        idexe.RegWrite = this->RegWrite;
        idexe.MemRead = this->MemRead;
        idexe.MemWrite = this->MemWrite;
        idexe.Branch = this->Branch;
        idexe.ALUOp = this->ALUOp;

        return idexe;
    }
};

int main()
{
    ID id("add", 1, 2, 3, 0);
    reg_IDEXE test;
    test = id.ret();
    // cout << id.instruction.op << endl;
    // cout << id.instruction.rs << endl;
    // cout << id.instruction.rt << endl;
    // cout << id.instruction.rd << endl;
    // cout << id.instruction.addr << endl;
    // cout << id.RegDst << endl;
    // cout << id.ALUOp << endl;
    // cout << id.ALUSrc << endl;
    // cout << id.Branch << endl;
    // cout << id.MemRead << endl;
    // cout << id.MemWrite << endl;
    // cout << id.RegWrite << endl;
    // cout << id.MemToReg << endl;

    return 0;
}