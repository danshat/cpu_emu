#include "system.h"
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
    std::cout << "Tick " << cpu->tick << "\n";
    switch (cpu->tick % 4) {
    case 0:
        // Fetch
        break;
    case 1:
        // Decode
        break;
    case 2:
        // Execute
        break;
    case 3:
        // Increase ESP
        cpu->stackPointer = cpu->stackPointer.to_ulong() + 1;

        break;
    }
    emit sendUpdateRegisterUI(cpu);
    cpu->tick += 1;
}

void System::loadDefaultProgram() {
    memory->init_default_program();
}
