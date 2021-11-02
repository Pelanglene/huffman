//
// Created by ulad on 06.10.2021.
//

#include <iostream>
#include "headers/CoderTester.h"

void CoderTester::DecodeFile(Getter &reader, Putter &writer) {
    this->SymbolsCount = reader.Get(9);
    //std::cout << "INFO: SymbolsCount: " << this->SymbolsCount << "\n";

    std::vector <int16_t> symbols;
    for (size_t i = 0; i < SymbolsCount; ++i) {
        symbols.push_back(reader.Get(9));
        //std::cout << "INFO: new symbol: " << symbols.back() << "\n";
    }
    //std::cout << "-----------\n";
    int64_t was = 0;
    while (was != SymbolsCount) {
        this->counts.push_back(reader.Get(9));
        was += this->counts.back();
    }

    //std::cout << "INFO: counts:\n";
    //for (auto u : this->counts) {
    //    std::cout << u << " ";
    //}
    //std::cout << "\n";

}