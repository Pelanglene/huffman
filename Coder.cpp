//
// Created by ulad on 05.10.2021.
//

#include <iostream>
#include <algorithm>
#include "headers/Coder.h"
#include "headers/config.h"
#include "headers/HuffmanTree.h"
#include "headers/Heap.h"

int16_t StrToInt(std::string &s) { /// bitstring
    int16_t ans = 0;
    for (auto u : s) {
        ans <<= 1;
        if (u == '1') {
            ans |= 1;
        }
    }
    return ans;
}

int16_t CountBits(int16_t a) {
    int16_t cnt = 0;
    while (a) {
        ++cnt;
        a >>= 1;
    }
    return cnt;
}

Coder::Coder() {
    SymbolCount = 0;
}

std::string IntToStr(int16_t ch, int16_t bits) {
    std::string res;
    while (bits--) {
        res += (ch & 1) + '0';
        ch >>= 1;
    }
    std::reverse(res.begin(), res.end());
    return res;
}

void ToCanonical(std::unordered_map<int16_t, std::string> &CodeTable, std::vector<int16_t> canonical) {
    std::unordered_map<int16_t, int16_t> CanTable;
    for (auto u : CodeTable) {
        CanTable[u.first] = StrToInt(u.second);
    }
    CanTable[canonical[0]] = 0;
    for (size_t i = 1; i < canonical.size(); ++i) {
        size_t len_diff = CodeTable[canonical[i]].size() - CodeTable[canonical[i - 1]].size();
        CanTable[canonical[i]] = CanTable[canonical[i - 1]] + 1;
        CanTable[canonical[i]] <<= len_diff;
    }

    for (auto u : CanTable) {
        CodeTable[u.first] = IntToStr(u.second, CodeTable[u.first].size());
    }
}


void Coder::MakeTable(Getter &read, const std::string& filename) {
    uint16_t curr_byte = 0;
    table.clear();
    table.resize(300);
    while (true) {
        try {
            curr_byte = read.Get(8);
            table[curr_byte] += 1;
        } catch (int64_t err) {
            std::cout << err << "\n";
            break;
        }
    }

    for (auto u : filename) {
        ++table[u];
    }

    ++table[ARCHIVE_END];
    ++table[FILENAME_END];
    ++table[ONE_MORE_FILE];

    //std::vector<std::pair<int16_t, HuffmanTree *> > Trees;
    Heap Trees;

    for (size_t i = 0; i < table.size(); ++i) {
        if (!table[i]) {
            continue;
        }
        ++SymbolCount;
        canonical.push_back(static_cast<int16_t>(i));
        auto *nw = new HuffmanTree(static_cast<int16_t>(i));
        Trees.AddElement({table[i], nw});
        //std::cout << i << " : " << table[i] << "!\n";
    }

    //std::sort(Trees.begin(), Trees.end());
    //std::reverse(Trees.begin(), Trees.end());

    while (static_cast<int>(Trees.Size()) != 1) {
        size_t pos = Trees.Size() - 1;
        auto f1 = Trees.TopElement();
        Trees.DelElement();
        auto f2 = Trees.TopElement();
        Trees.DelElement();
        std::pair<int16_t, HuffmanTree *> f3 = {f1.first + f2.first, HuffmanTree::Merge(f1.second, f2.second)};
        Trees.AddElement(f3);
        //Trees.PrintHeap();
    }
    //Trees.PrintHeap();

    HuffmanTree::MakeCodeTable(Trees.TopElement().second, this->CodeTable);
    sort(canonical.begin(), canonical.end(), [&](int16_t a, int16_t b) {
        if (this->CodeTable[a].size() < this->CodeTable[b].size()) {
            return true;
        }
        if (this->CodeTable[a].size() > this->CodeTable[b].size()) {
            return false;
        }
        if (this->CodeTable[a] < this->CodeTable[b]) {
            return true;
        }
        return false;
    });
    //std::cout << "----------HUFFMAN CODE----------\n";
    //for (auto u : canonical) {
    //    std::cout << u << ":\t\t " << this->CodeTable[u] << "\n";
    //}
    //std::cout << "-------------------------\n";
    // to canonical

    ToCanonical(this->CodeTable, this->canonical);

    //std::cout << "----------CANONICAL CODE--------\n";
    //for (auto u : canonical) {
    //    std::cout << u << ":\t\t " << this->CodeTable[u] << "\n";
    //}
    //std::cout << "-------------------------\n";

}

void Coder::Code(const std::string& filename, Getter &reader, Putter &writer,
                 bool isArchiveEnd) {
    writer.Put(SymbolCount, 9);
    //std::cout << "INFO: " << "wrote " << SymbolCount << " to " << filename << "\n";
    std::vector<int16_t> counts(300 + 3);
    for (auto u : canonical) {
        writer.Put(u, 9);
        //std::cout << "INFO: " << "wrote " << u << " to " << filename << "\n";
        ++counts[CodeTable[u].size() - 1];
    }

    int64_t was = 0;
    for (int16_t count : counts) {
        was += count;
        writer.Put(count, 9);
        //std::cout << "INFO: " << "wrote(counts) " << count << " to " << filename << "\n";
        if (was == SymbolCount) {
            break;
        }
    }

    for (auto u : filename) {
        std::string to_debug = this->CodeTable[u];
        //std::reverse(to_debug.begin(), to_debug.end());
        //std::cout << "Put " << to_debug << "\n";
        writer.Put(StrToInt(this->CodeTable[u]), this->CodeTable[u].size());
    }

    //std::cout << "after end\n";
    //std::cout << "Put " << this->CodeTable[FILENAME_END] << "\n";
    writer.Put(StrToInt(this->CodeTable[FILENAME_END]), this->CodeTable[FILENAME_END].size());
    int16_t curr_byte;
    while (true) {
        try {
            curr_byte = reader.Get(8);
            //std::cout << "Put " << this->CodeTable[curr_byte] << "\n";
            writer.Put(StrToInt(this->CodeTable[curr_byte]), this->CodeTable[curr_byte].size());
        } catch (int64_t err) {
            //std::cout << err << "\n";
            break;
        }
    }

    if (isArchiveEnd) {
        //std::cout << "Put " << this->CodeTable[ARCHIVE_END] << "\n";
        writer.Put(StrToInt(this->CodeTable[ARCHIVE_END]), this->CodeTable[ARCHIVE_END].size());
    } else {
        //std::cout << "Put " << this->CodeTable[ONE_MORE_FILE] << "\n";
        writer.Put(StrToInt(this->CodeTable[ONE_MORE_FILE]), this->CodeTable[ONE_MORE_FILE].size());
    }
    //writer.Close();
}