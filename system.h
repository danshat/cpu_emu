#ifndef SYSTEM_H
#define SYSTEM_H

#include "Memory.h"
#include "cpu.h"
#include <QObject>

class System : public QObject
{
    Q_OBJECT
public:
    explicit System(QObject *parent = nullptr);
    Memory *memory;
    CPU *cpu;
public slots:
    void run();
    void loadDefaultProgram();
    void started();
signals:
    void sendUpdateRegisterUI(CPU *cpu);
    void decodeLabel(QString a);
    void halt();
    void updateMemoryUI(Memory *mem);
};

#endif // SYSTEM_H
