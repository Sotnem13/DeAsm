//
// Created by sotnem on 24.12.19.
//

#ifndef DIASM_UTILS_HPP
#define DIASM_UTILS_HPP

#include <memory>
#include <fstream>

template <typename T>
struct Free {
    void operator()(T* p) {
        free(p);
    }
};



//std::unique_ptr<char[], Free<char[]>> readFile(const char* filename) {
//    auto f = std::ifstream(filename);
//    f.seekg(0, f.end);
//    auto size = f.tellg();
//    f.seekg(0, f.beg);
//    auto data = std::unique_ptr<char[], Free<char[]>>((char*)malloc(size + 1));
//    f.read(data.get(), size);
//    data[size] = '\0';
//
//    return data;
//}


#endif //DIASM_UTILS_HPP
