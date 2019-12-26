//
// Created by sotnem on 24.12.19.
//

#include <fstream>
#include <VM.hpp>


int main() {



    CPU c;

    auto f = std::ifstream("o");
    f.read(reinterpret_cast<char *>(&c.mem[0]), 106);


    c.run(57);

}