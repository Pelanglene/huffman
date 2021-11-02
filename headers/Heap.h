//
// Created by ulad on 02.10.2021.
//

#ifndef HSE_VLAD_ANOKHOV_ANOKHOV04_HEAP_H
#define HSE_VLAD_ANOKHOV_ANOKHOV04_HEAP_H

#include <utility>
#include "HuffmanTree.h"
#include <ostream>
#include <vector>

class Heap {
public:
    void AddElement(std::pair<int, HuffmanTree*> x);

    std::pair<int, HuffmanTree*> TopElement();

    void DelElement();

    size_t Size();

    void PrintHeap();

private:
    std::vector <std::pair<int, HuffmanTree*>> data;

    void ShiftUp(size_t pos);

    void ShiftDown(size_t pos);
};

std::ostream& operator<<(std::ostream&, std::pair<int, HuffmanTree*>);

#endif //HSE_VLAD_ANOKHOV_ANOKHOV04_HEAP_H
