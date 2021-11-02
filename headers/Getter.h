//
// Created by ulad on 05.10.2021.
//

#ifndef ARCHIEVER_GETTER_H
#define ARCHIEVER_GETTER_H

#include <cstddef>
#include <istream>
#include <type_traits>

class Getter {
public:
    explicit Getter(std::istream &source);
    int16_t Get(uint16_t n);

private:
    std::istream &from;
    int16_t was, buff;
};


#endif //ARCHIEVER_GETTER_H
