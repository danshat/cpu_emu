#include "cpu.h"

CPU::CPU() {
    instructionRegister = 0;
    stackPointer = 0;
    aluOp1Reg = 0;
    aluOp2Reg = 0;
    tick = 0;
}

void CPU::cpuReset() {
    instructionRegister = 0;
    stackPointer = 0;
    aluOp1Reg = 0;
    aluOp2Reg = 0;
    tick = 0;
    emit updateRegisters(this);
}


