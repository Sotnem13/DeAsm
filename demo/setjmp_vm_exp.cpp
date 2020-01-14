//
// Created by sotnem on 09.01.20.
//
#include <fstream>
#include <csetjmp>

#include <VM.hpp>

#define OpCase(OpCode) lb_##OpCode

//struct InstructionContext {
//
//} instruction_context;





int main() {



//    op ops[] = { stop, geta, getb, add, print };
//
//    glob_context.running = 1;
//
    char code[] = {1,1, 1,2, 2,1,2,0, 3,0, 0};

    void* ops[] = {&&stop, &&get, &&add, &&print};

    auto ip = &code[0];

    bool running = true;
    int reg[8] = {0};


    while (running) {
        goto *ops[*ip];
        ret: {
            ++ip;
        }
    }

    return 0;

    get: {
        auto r = *++ip;
        std::cin >> reg[r];
        goto ret;
    };

    stop: {
        running = false;
        goto ret;
    };

    add:
    {
        auto r1 = *++ip;
        auto r2 = *++ip;
        auto r3 = *++ip;
        reg[r3] = reg[r1] + reg[r2];
        goto ret;
    };


    print: {
        auto r1 = *++ip;
        std::cout << reg[r1] << std::endl;
        goto ret;
    };

}