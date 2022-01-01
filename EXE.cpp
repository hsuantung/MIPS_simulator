#include <iostream>
#include <string>
using namespace std;

int RegisterMemory[32] = {0};

struct reg_IDEXE{
    string opcode;
    int rs;               // reg的編號
    int rt;               // reg的編號
    int rd;               // 如果是reg，就放reg的編號，否則先填-1
    int address;          // 如果rd = -1，這邊是地址(word)
    int WriteRegNum = 0;  // 寫回去的reg是哪個編號

    char RegDst = '0';
    char ALUSrc = '0';
    char Branch = '0';
    char MemRead = '0';
    char MemWrite = '0';
    char RegWrite = '0';
    char MemToReg = '0';

    int ALUOp = 0;    
} IDEXE;

struct reg_EXEMEM{
    string opcode;        // add, sub, lw, sw, beq
    int ALUResult = 0;    // 下面ALU的計算結果

    char MemRead = '0';   // lw
    char MemWrite = '0';  // sw
    char Branch = '0';    // 我覺得這邊應該要傳下去給MEM才可以有output?
    char MemToReg = '0';  // lw
    char RegWrite = '0';  // R-format, lw
    int WriteRegNum = 0;  // 寫回的reg編號(RegWrite == 1)
} EXEMEM;

class EXE{
public:
    EXE(){
        pass_Signal();
    }

    void start(){
        btm_ALU();
        make_Output();
    }

    string currentInstr(){
        return EXEMEM.opcode;
    }

private:
    void pass_Signal(){
        // 將ID的signal存下來
        EXEMEM.opcode = IDEXE.opcode;
        EXEMEM.MemRead = IDEXE.MemRead;
        EXEMEM.MemWrite = IDEXE.MemWrite;
        EXEMEM.MemToReg = IDEXE.MemToReg;
        EXEMEM.RegWrite = IDEXE.RegWrite;
        EXEMEM.WriteRegNum = IDEXE.WriteRegNum;
    }

    void btm_ALU(){
        // 下面ALU的運算
        if(IDEXE.opcode == "add"){
            // rs + rt
            EXEMEM.ALUResult = RegisterMemory[IDEXE.rs] + RegisterMemory[IDEXE.rt];
        }
        else if(IDEXE.opcode == "sub"){
            // rs-rt
            EXEMEM.ALUResult = RegisterMemory[IDEXE.rs] - RegisterMemory[IDEXE.rt];
        }
        else if(IDEXE.opcode == "lw" || IDEXE.opcode == "sw"){
            // rs + offset
            EXEMEM.ALUResult = RegisterMemory[IDEXE.rs] + IDEXE.address;
        }
    }

    void make_Output(){
        EXEMEM.opcode = IDEXE.opcode + ": EXE " + IDEXE.RegDst + IDEXE.ALUSrc + 
                        " " + IDEXE.Branch + IDEXE.MemRead + IDEXE.MemWrite + 
                        " " + IDEXE.RegWrite + IDEXE.MemToReg;
    }
};