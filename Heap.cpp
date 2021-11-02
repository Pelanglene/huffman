//
// Created by ulad on 02.10.2021.
//

#include "headers/Heap.h"
#include "iostream"

void Heap::ShiftUp(size_t pos) {
    while (pos) {
        if (data[pos / 2] > data[pos]) {
            std::swap(data[pos / 2], data[pos]);
            pos /= 2;
        } else {
            break;
        }
    }
}

void Heap::ShiftDown(size_t pos) {
    while (pos * 2 + 1 < data.size()) {
        size_t left = pos * 2 + 1;
        size_t right = pos * 2 + 2;

        int nxt = left;

        if (right < data.size() && data[right] < data[left]) {
            nxt = right;
        }

        if (data[pos] <= data[nxt]) {
            break;
        }

        std::swap(data[pos], data[nxt]);
        pos = nxt;
    }
}

void Heap::AddElement(const std::pair<int, HuffmanTree*> x) {
    size_t pos = data.size();
    data.push_back(x);
    ShiftUp(pos);
}

std::pair<int, HuffmanTree*> Heap::TopElement() {
    return data[0];
}

void Heap::DelElement() {
    data[0] = data.back();
    data.pop_back();
    ShiftDown(0);
}

void Heap::PrintHeap() {
    std::cout << this->TopElement() << ": ";
    for (auto u : data) {
        std::cout << u.first << " ";
    }
    std::cout << "\n";
}

std::ostream& operator<<(std::ostream& out, std::pair<int, HuffmanTree*> gg) {
    out << "{" << gg.first << "}";
    return out;
}

size_t Heap::Size() {
    return this->data.size();
}