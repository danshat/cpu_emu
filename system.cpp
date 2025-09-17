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
        qInfo() << "Tick " << cpu->tick << " DECODE";
        break;
    case 2:
        // Execute
        qInfo() << "Tick " << cpu->tick << " EXECUTE";
        break;
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
