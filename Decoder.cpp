//
// Created by ulad on 06.10.2021.
//

#include <vector>
#include <fstream>
#include <iostream>
#include "headers/Decoder.h"
#include "headers/Putter.h"

std::unordered_map<uint16_t, std::string> Decoder::ReadCodeTable(Getter& reader) {
    uint16_t symbols_count = reader.Get(9);
    //std::cout << "symbols_count: " << symbols_count << "\n";
    std::vector<uint16_t> symbols(symbols_count);
    for (uint16_t& symbol : symbols) {
        symbol = reader.Get(9);
        //std::cout << "symbol: " << symbol << "\n";
    }

    std::unordered_map<uint16_t, std::string> result_table;
    uint16_t total_sizes = 0;
    uint16_t processed = 0;
    uint16_t code_now = 0;
    uint16_t code_length = 1;
    while (total_sizes < symbols_count) {
        uint16_t ln_size = reader.Get(9);
        //std::cout << "count:" << ln_size << "\n";
        total_sizes += ln_size;
        while (ln_size > 0) {
            --ln_size;
            std::string to_save;
            for (uint16_t i = 0; i < code_length; ++i) {
                if (((code_now >> i) & 1) == 0) {
                    to_save += '0';
                } else {
                    to_save += '1';
                }
            }
            result_table[symbols[processed]] = to_save;
            ++code_now;
            ++processed;
        }
        code_now <<= 1;
        ++code_length;
    }

    //for (uint16_t& symbol : symbols) {
    //    std::cout << "symbol: \t" << symbol << " : \t\t" << result_table[symbol] << "\n";
    //}

    //++result_table[ARCHIVE_END];
    //++result_table[];

    return result_table;
}

bool Decoder::DecodeFileLast(Getter& reader) {
    std::unordered_map<uint16_t, std::string> codetable = Decoder::ReadCodeTable(reader);
    //works
    HuffmanTree* sym_tree = HuffmanTree::MakeTree(codetable);

    int16_t current_char = 0;
    std::string filename;
    while (current_char != FILENAME_END) {
        //std::cout << filename + " aboba"; std::cout.flush();
        current_char = sym_tree->ResolveSymbol(reader);
        //std::cout << "Got: " << current_char << "\n";
        if (current_char < 256) {
            filename += static_cast<char>(current_char);
        }
        if (current_char == ONE_MORE_FILE || current_char == ARCHIVE_END) {
            throw BLYA;
        }
    }

    std::ofstream file_output(filename);
    Putter writer(file_output);

    while (current_char != ONE_MORE_FILE && current_char != ARCHIVE_END) {
        current_char = sym_tree->ResolveSymbol(reader);
        if (current_char < 256) {
            writer.Put(current_char, 8);
        }
        if (current_char == FILENAME_END) {
            throw BLYA;
        }
    }
    writer.Close();
    file_output.close();
    return current_char == ARCHIVE_END;
}