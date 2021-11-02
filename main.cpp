#include <iostream>
#include "headers/config.h"
#include "headers/Getter.h"
#include "headers/Putter.h"
#include "headers/Coder.h"
#include "headers/Parser.h"
#include "headers/CoderTester.h"
#include "headers/Decoder.h"
#include <fstream>

std::vector<std::string> filenames;
std::string ArchiveName;

int main(int argc, char* argv[]) {
    Parser parser;
    try {
        parser.ParseFlags(argc, argv, filenames, ArchiveName);
    } catch (int64_t err) {
        Parser::PrintHelp();
        return 0;
    }
    for (const auto& u: filenames) {
        std::cout << u << "\n";
    }
    //return 0;
    // for file in files :
    if (parser.Option()) {
        std::ofstream fout(ArchiveName);
        Putter writer(fout);
        size_t id = 0;
        for (const auto& filename : filenames) {
            ++id;
            std::ifstream fin1(filename);
            std::ifstream fin2(filename);
            Getter reader1(fin1);
            Getter reader2(fin2);
            Coder coder;
            coder.MakeTable(reader1, filename);
            coder.Code(filename, reader2, writer, (id == filenames.size()));
            fin1.close();
            fin2.close();
        }
        writer.Close();
        fout.close();
    } else {
        std::ifstream fin(ArchiveName);
        Getter reader(fin);
        while (!Decoder::DecodeFileLast(reader)) {
            std::cout << "next file\n";
        }
    }

    return 0;
}
