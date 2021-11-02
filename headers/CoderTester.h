//
// Created by ulad on 06.10.2021.
//

#ifndef ARCHIEVER_CODERTESTER_H
#define ARCHIEVER_CODERTESTER_H


#include <cstdint>
#include <vector>
#include "Getter.h"
#include "Putter.h"

class CoderTester {
public:
    void DecodeFile(Getter &reader, Putter &writer);
private:
    int64_t SymbolsCount;
    std::vector <int64_t> counts;
};


#endif //ARCHIEVER_CODERTESTER_H
