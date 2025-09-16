#ifndef UNTITLED_CPU_H
#define UNTITLED_CPU_H
#include "qobject.h"
#include <bitset>


class CPU : public QObject {
    Q_OBJECT
public:
    std::bitset<32> stackPointer; // ESP
    std::bitset<32> instructionRegister; // IR
    std::bitset<32> aluOp1Reg;
    std::bitset<32> aluOp2Reg;

    CPU();

    unsigned int tick;

};


#endif //UNTITLED_CPU_H
