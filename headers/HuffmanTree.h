//
// Created by ulad on 05.10.2021.
//

#ifndef ARCHIEVER_HUFFMANTREE_H
#define ARCHIEVER_HUFFMANTREE_H


#include <vector>
#include <string>
#include <unordered_map>
#include "Getter.h"

class HuffmanTree {
public:
    HuffmanTree(int16_t _c);
    HuffmanTree();

    static HuffmanTree *Merge(HuffmanTree *left, HuffmanTree *right);

    static void MakeCodeTable(HuffmanTree *curr, std::unordered_map<int16_t, std::string> &CodeTable);

    static HuffmanTree *MakePath(HuffmanTree *root, uint16_t sym, const std::string &path);

    static HuffmanTree *MakeTree(const std::unordered_map<uint16_t, std::string> &codetable);

    static void
    MakeCodeCounter(HuffmanTree *node, std::unordered_map<uint16_t, uint16_t> &code_bits, uint16_t codesize);

    uint16_t ResolveSymbol(Getter &reader);

private:
    bool isLeaf;
    int16_t lt;
    HuffmanTree *nxt[2];
};


#endif //ARCHIEVER_HUFFMANTREE_H
