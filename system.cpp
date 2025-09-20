#include "system.h"
#include "qdebug.h"
#include <QThread>
#include <QTimer>
#include <iostream>

System::System(QObject *parent)
    : QObject{parent}
{
    cpu = new CPU();
    memory = new Memory();
}


void System::run() {
    switch (cpu->tick % 4) {
    case 0:
        // Fetch
    {
        qInfo() << "Tick " << cpu->tick << " FETCH";
        std::bitset<33> cell = memory->get_cell(cpu->stackPointer.to_ulong());
        while (cell[32] == 0) {
            cpu->stackPointer = cpu->stackPointer.to_ulong() + 1;
            cell = memory->get_cell(cpu->stackPointer.to_ulong());
        }
        std::bitset<32> address = 0;
        for (int i = 0; i < 32; i++) {
            address[i] = cell[i];
        }
        cpu->instructionRegister = address;
        break;
    }
    case 1:
        // Decode
    {
        qInfo() << "Tick " << cpu->tick << " DECODE";
        unsigned long command = cpu->instructionRegister.to_ulong();
        switch (command) {
            case 0:
                emit decodeLabel("TOREG1");
                break;
            case 1:
                emit decodeLabel("TOREG2");
                break;

            case 2:
                emit decodeLabel("CMP");
                break;
            case 3:
                emit decodeLabel("REG1TM");
                break;
            case 4:
                emit decodeLabel("HLT");
                break;
        }

        break;
    }
    case 2:
        // Execute
    {
        qInfo() << "Tick " << cpu->tick << " EXECUTE";
        unsigned long command = cpu->instructionRegister.to_ulong();
        switch (command) {
            case 0:
                {
                    qInfo() << "EXECUTE TOREG1";
                    cpu->stackPointer = cpu->stackPointer.to_ulong() + 1;
                    unsigned long esp = cpu->stackPointer.to_ulong();
                    std::bitset<33> data = memory->get_cell(esp);
                    qInfo() << "DATA IN STACK " << data.to_string();
                    std::bitset<32> literal = 0;
                    for (int i = 0; i < 32; i++) {
                        literal[i] = data[i];
                    }
                    cpu->aluOp1Reg = literal;
                    qInfo() << "LOAD TO REG1 " << literal.to_ulong();

                    break;
                }
            case 1:
                {
                    qInfo() << "EXECUTE TOREG2";
                    cpu->stackPointer = cpu->stackPointer.to_ulong() + 1;
                    unsigned long esp = cpu->stackPointer.to_ulong();
                    std::bitset<33> data = memory->get_cell(esp);
                    qInfo() << "DATA IN STACK " << data.to_string();
                    std::bitset<32> literal = 0;
                    for (int i = 0; i < 32; i++) {
                        literal[i] = data[i];
                    }
                    cpu->aluOp2Reg = literal;
                    qInfo() << "LOAD TO REG2 " << literal.to_ulong();
                    break;
                }
                break;
            case 2:
                {
                    qInfo() << "EXECUTE CMP";
                    cpu->aluOp1Reg = std::max(cpu->aluOp1Reg.to_ulong(), cpu->aluOp2Reg.to_ulong());
                }
                break;
            case 3:

                break;
            case 4:

                break;
        }

        break;
    }
    case 3:
        // Increase ESP
        qInfo() << "Tick " << cpu->tick << " INCREASE";
        cpu->stackPointer = cpu->stackPointer.to_ulong() + 1;
        break;
    }
    cpu->tick += 1;
    emit sendUpdateRegisterUI(cpu);

}

void System::loadDefaultProgram() {
    memory->init_default_program();
}
