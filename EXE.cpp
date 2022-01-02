#include <iostream>
#include <string>
using namespace std;

int RegisterMemory[32] = {0};

struct reg_IDEXE{
    string opcode;
    int rs;               // reg的編號
    int rt;               // reg的編號
    int rd;               // 如果是reg，就放reg的編號，否則先填-1
    int num_rs;           // rs暫存器的編號(for forwarding unit)
    int num_rt;           // rt暫存器的編號(for forwarding unit)
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
    int ALUResult = 0;    // ALU的計算結果

    char MemRead = '0';   // lw
    char MemWrite = '0';  // sw
    char Branch = '0';    // 我覺得這邊應該要傳下去給MEM才可以有output?
    char MemToReg = '0';  // lw
    char RegWrite = '0';  // R-format, lw
    int WriteRegNum = 0;  // 寫回的reg編號(RegWrite == 1)
} EXEMEM;

//MEMWB struct是for forwarding unit，我先寫我需要的東西，名字可以再改
struct reg_MEMWB{
    int ALUResult = 0;    
    char RegWrite = '0';  // R-format, lw
    int WriteRegNum = 0;  // MEM/WB.RegisterRd
} MEMWB;

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
        int forwardingA = 0;  // rs / 先假設沒有hazard
        int forwardingB = 0;  // rt / 先假設沒有hazard

        if(EXEMEM.RegWrite == '1' && EXEMEM.WriteRegNum != 0 && EXEMEM.WriteRegNum == IDEXE.num_rs){
            //EXE hazard / rs
            forwardingA = 2;
        }
        if(EXEMEM.RegWrite == '1' && EXEMEM.WriteRegNum != 0 && EXEMEM.WriteRegNum == IDEXE.num_rt){
            //EXE hazard / rt
            forwardingB = 2;
        }
        if(!(EXEMEM.RegWrite == '1' && EXEMEM.WriteRegNum != 0 && (EXEMEM.WriteRegNum == IDEXE.num_rs || EXEMEM.WriteRegNum == IDEXE.num_rt))){
            //no EXE hazard
            if(MEMWB.RegWrite == '1' && MEMWB.WriteRegNum != 0 && MEMWB.WriteRegNum == IDEXE.num_rs){
                // unrevised MEM Hazard / rs
                forwardingA = 1;
            }
            if(MEMWB.RegWrite == '1' && MEMWB.WriteRegNum != 0 && MEMWB.WriteRegNum == IDEXE.num_rt){
                // unrevised MEM Hazard / rt
                forwardingB = 1;
            }
        }

        int MUX1 = 0;  // 上面那個multiplexer選擇出來的值
        int MUX2 = 0;  // 下面那個multiplexer選擇出來的值
        //source: 00->ID/EXE
        //        01->MEM/WB
        //        10->EX/MEM

        switch(forwardingA){
            case 0:
                MUX1 = RegisterMemory[IDEXE.num_rs];
                break;
            case 1:
                MUX1 = EXEMEM.ALUResult;
                break;
            case 2:
                MUX1 = MEMWB.ALUResult;
                break;
        }

        switch(forwardingB){
            case 0:
                MUX2 = RegisterMemory[IDEXE.num_rt];
                break;
            case 1:
                MUX2 = EXEMEM.ALUResult;
                break;
            case 2:
                MUX2 = MEMWB.ALUResult;
                break;
        }

        // ALU的運算
        if(IDEXE.opcode == "add"){
            // rs + rt
            EXEMEM.ALUResult = MUX1 + MUX2;
        }
        else if(IDEXE.opcode == "sub"){
            // rs-rt
            EXEMEM.ALUResult = MUX1 - MUX2;
        }
        else if(IDEXE.opcode == "lw" || IDEXE.opcode == "sw"){
            // rs + offset
            EXEMEM.ALUResult = MUX1 + IDEXE.address;
        }
    }

    void make_Output(){
        EXEMEM.opcode = IDEXE.opcode + ": EXE " + IDEXE.RegDst + IDEXE.ALUSrc + 
                        " " + IDEXE.Branch + IDEXE.MemRead + IDEXE.MemWrite + 
                        " " + IDEXE.RegWrite + IDEXE.MemToReg;
    }
};