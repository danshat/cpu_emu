#include "Memory.h"
#include <iostream>

Memory::Memory() {
    ramStorage = 0;
}
void Memory::set_cell(int cellNumber, std::bitset<33> value) {
    int pos = cellNumber * 33;
    for (int i = 0; i < 33; i++) {
        ramStorage[pos + i] = value[i];
    }
    emit updateMemoryUI(this);
}

std::bitset<33> Memory::get_cell(int cellNumber) {
    int pos = cellNumber * 33;
    std::bitset<33> resultCell;
    for (int i = pos; i < pos + 33; i++) {
        resultCell[i-pos] = ramStorage[i];
    }
    return resultCell;
}



void Memory::init_default_program() {
    this->set_cell(0, std::bitset<33>(0x100000000));
    this->set_cell(1, std::bitset<33>(1));
    this->set_cell(2, std::bitset<33>(0x100000001));
    this->set_cell(3, std::bitset<33>(71));
    this->set_cell(4, std::bitset<33>(0x100000002));
    this->set_cell(5, std::bitset<33>(0x100000001));
    this->set_cell(6, std::bitset<33>(5));
    this->set_cell(7, std::bitset<33>(0x100000002));
    this->set_cell(8, std::bitset<33>(0x100000001));
    this->set_cell(9, std::bitset<33>(7));
    this->set_cell(10, std::bitset<33>(0x100000002));
    this->set_cell(11, std::bitset<33>(0x100000001));
    this->set_cell(12, std::bitset<33>(18));
    this->set_cell(13, std::bitset<33>(0x100000002));
    this->set_cell(14, std::bitset<33>(0x100000001));
    this->set_cell(15, std::bitset<33>(22));
    this->set_cell(16, std::bitset<33>(0x100000002));
    this->set_cell(17, std::bitset<33>(0x100000001));
    this->set_cell(18, std::bitset<33>(12));
    this->set_cell(19, std::bitset<33>(0x100000002));
    this->set_cell(20, std::bitset<33>(0x100000001));
    this->set_cell(21, std::bitset<33>(21));
    this->set_cell(22, std::bitset<33>(0x100000002));
    this->set_cell(23, std::bitset<33>(0x100000001));
    this->set_cell(24, std::bitset<33>(34));
    this->set_cell(25, std::bitset<33>(0x100000002));
    this->set_cell(26, std::bitset<33>(0x100000001));
    this->set_cell(27, std::bitset<33>(8));
    this->set_cell(28, std::bitset<33>(0x100000002));
    this->set_cell(29, std::bitset<33>(0x100000003));
    this->set_cell(30, std::bitset<33>(0x100000004));
}

