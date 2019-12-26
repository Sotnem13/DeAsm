//
// Created by sotnem on 25.12.19.
//

#include <translator.hpp>
#include <iostream>
#include <iomanip>


auto printFile() {
    Tokenizer tokenizer;
    tokenizer.addData("hello_world.dasm");
    tokenizer.addData("test.dasm");

    uint64_t last_line = 1;
    char c = tokenizer.getChar();
    std::cout << std::setw(3) << 1 << "|";
    while(c) {
        auto pos = tokenizer.currentPos();
        if (!pos) break;
        c = tokenizer.c;
        std::cout << c;
        tokenizer.nexChar();

        while(pos->line != last_line) {
            std::cout << '\n' << std::setw(3) << pos->line << "|";
            last_line = pos->line;
            tokenizer.nexChar();
        }

//        c = tokenizer.getChar();


    }
}

int main() {

//    printFile();

    Tokenizer tokenizer;
    tokenizer.addData("hello_world.dasm");
    tokenizer.addData("hello_world.dasm");
    tokenizer.addData("test.dasm");

    std::cout << "\'    \"" << std::endl;


}