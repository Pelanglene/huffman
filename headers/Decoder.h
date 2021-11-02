//
// Created by ulad on 06.10.2021.
//

#ifndef HUFFMANARCHIVER_DECODER_H
#define HUFFMANARCHIVER_DECODER_H

#include <istream>
#include "Getter.h"
#include "HuffmanTree.h"
#include "config.h"

class Decoder {
public:
    static bool DecodeFileLast(Getter& reader);

    static std::unordered_map<uint16_t, std::string> ReadCodeTable(Getter& reader);
};

#endif //HUFFMANARCHIVER_DECODER_H