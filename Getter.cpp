//
// Created by ulad on 05.10.2021.
//

#include "headers/Getter.h"
#include "headers/config.h"
#include <iostream>

Getter::Getter(std::istream &source) : from(source) {
    this->buff = 0;
    this->was = BYTE_SIZE;
}

int16_t Getter::Get(uint16_t count) {
    int16_t ans = 0, read = 0;
    while (count > 0) {
        if (this->was == BYTE_SIZE) {
            this->buff = this->from.get();
            this->was = 0;
            if (this->from.eof()) {
                throw EOF_ERROR;
            }
        }

        uint16_t need_now = std::min(count, static_cast<uint16_t>(BYTE_SIZE - this->was));
        auto rem = static_cast<uint16_t>(this->buff >> this->was);
        rem &= (1 << need_now) - 1;
        ans |= rem << read;

        count -= need_now;
        this->was += need_now;
        read += need_now;
    }

    int16_t res = 0;
    for (size_t i = 0; i < read; ++i) {
        res |= ((ans >> i) & 1) << (read - i - 1);
    }
    return res;
}
