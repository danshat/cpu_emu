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
signals:
    void sendUpdateRegisterUI(CPU *cpu);
    void decodeLabel(QString a);
};

#endif // SYSTEM_H
