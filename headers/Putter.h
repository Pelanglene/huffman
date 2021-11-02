//
// Created by ulad on 05.10.2021.
//

#ifndef ARCHIEVER_PUTTER_H
#define ARCHIEVER_PUTTER_H

#include <cstddef>
#include <ostream>
#include <type_traits>
#include "config.h"

class Putter {
public:
    explicit Putter(std::ostream& to);
    void Put(int16_t c, uint16_t bits);
    void Close();

private:
    std::ostream& to;
    uint16_t buff, ws;
};


#endif //ARCHIEVER_PUTTER_H
