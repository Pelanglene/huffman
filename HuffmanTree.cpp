//
// Created by ulad on 05.10.2021.
//

#include <iostream>
#include "headers/HuffmanTree.h"
#include "headers/Getter.h"

HuffmanTree::HuffmanTree(int16_t _c) {
    lt = _c;
    isLeaf = true;
    nxt[0] = nullptr;
    nxt[1] = nullptr;
}

HuffmanTree::HuffmanTree() {
    lt = 'F';
    isLeaf = false;
    nxt[0] = nullptr;
    nxt[1] = nullptr;
}

HuffmanTree *HuffmanTree::Merge(HuffmanTree *left, HuffmanTree *right) {
    auto *res = new(HuffmanTree);
    res->nxt[0] = left;
    res->nxt[1] = right;
    res->isLeaf = false;
    return res;
}

void HuffmanTree::MakeCodeTable(HuffmanTree *curr, std::unordered_map<int16_t, std::string>& CodeTable) {
    static std::string way;
    if (curr->isLeaf) {
        CodeTable[curr->lt] = way;
        return;
    }
    if (curr->nxt[0] != nullptr) {
        way += '0';
        HuffmanTree::MakeCodeTable(curr->nxt[0], CodeTable);
        way.pop_back();
    }
    if (curr->nxt[1] != nullptr) {
        way += '1';
        HuffmanTree::MakeCodeTable(curr->nxt[1], CodeTable);
        way.pop_back();
    }
}


HuffmanTree* HuffmanTree::MakePath(HuffmanTree* root, uint16_t sym, const std::string& path) {
    HuffmanTree* current = root;
    for (size_t i = 0; i < path.size(); ++i) {
        if (current->nxt[path[path.size() - i - 1] - '0'] == nullptr) {
            current->nxt[path[path.size() - i - 1] - '0'] = new HuffmanTree();
        }
        current = current->nxt[path[path.size() - i - 1] - '0'];
    }
    current->lt = sym;
    current->isLeaf = true;
    return current;
}

HuffmanTree* HuffmanTree::MakeTree(const std::unordered_map<uint16_t, std::string> &codetable) {
    auto* tree = new HuffmanTree();
    for (const auto& item : codetable) {
        MakePath(tree, item.first, item.second);
    }
    return tree;
}

void HuffmanTree::MakeCodeCounter(HuffmanTree *node, std::unordered_map<uint16_t, uint16_t>& code_bits,
                                  uint16_t codesize) {
    if (node->isLeaf) {
        code_bits[node->lt] = codesize;
    } else {
        if (node->nxt[0] != nullptr) {
            MakeCodeCounter(node->nxt[0], code_bits, codesize + 1);
        }
        if (node->nxt[1] != nullptr) {
            MakeCodeCounter(node->nxt[1], code_bits, codesize + 1);
        }
    }
}

uint16_t HuffmanTree::ResolveSymbol(Getter &reader) {
    HuffmanTree *current = this;
    while (!current->isLeaf) {
        int16_t nxtbit = reader.Get(1);
        current = current->nxt[nxtbit];
        //std::cout << nxtbit;
    }
    //std::cout << "!\n";
    return current->lt;
}