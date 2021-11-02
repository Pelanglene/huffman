//
// Created by ulad on 05.10.2021.
//

#include "headers/Putter.h"
#include "headers/config.h"


Putter::Putter(std::ostream &_out) : to(_out) {
    this->buff = 0;
    this->ws = 0;
}

void Putter::Close() {
    if (this->ws != 0) {
        this->to.put(this->buff);
    }
}

void Putter::Put(int16_t c, uint16_t bits) {
    int16_t to_write = 0;
    for (size_t i = 0; i < bits; ++i) {
        to_write |= ((c >> i) & 1) << (bits - i - 1);
    }
    while (bits > 0) {
        size_t write_bits = std::min(static_cast<uint16_t> (BYTE_SIZE - this->ws), bits);
        this->buff |= ((to_write & ((1 << write_bits) - 1)) << this->ws);
        this->ws += write_bits;
        if (this->ws == 8) {
            this->to.put(this->buff);
            this->ws = 0;
            this->buff = 0;
        }
        bits -= write_bits;
        to_write >>= write_bits;
    }
}