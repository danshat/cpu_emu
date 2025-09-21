#ifndef UNTITLED_MEMORY_H
#define UNTITLED_MEMORY_H
#include "qobject.h"
#include <bitset>


class Memory : public QObject {
    Q_OBJECT
public:
    std::bitset<4224> ramStorage; // 33 bits * 128 units
    void set_cell(int cellNumber, std::bitset<33> value);
    std::bitset<33> get_cell(int cellNumber);
    Memory();
    void reset();
signals:
    void updateMemoryUI(Memory *mem);
public slots:
    void init_default_program();
    void memReset();

};


#endif //UNTITLED_MEMORY_H
