//
// Created by sotnem on 24.12.19.
//

#include <fstream>
#include <VM.hpp>




struct {

    int a;
    int b;
    int c;

    bool running;
    char* cur;

} glob_context;



using op = void (*)();



void add(){
    glob_context.c = glob_context.a + glob_context.b;
}

void geta() {
    std::cin >> glob_context.a;
}

void getb() {
    std::cin >> glob_context.b;
}

void stop() {
    glob_context.running = false;
}

void print() {
    std::cout << glob_context.c << std::endl;
}

int main() {


    op ops[] = { stop, geta, getb, add, print };

    glob_context.running = 1;

    char code[] = {1,2,3,4,0};

    auto ip = &code[0];

    while (glob_context.running && *ip) {
        ops[*ip++]();
    }


//    CPU c;

//    auto f = std::ifstream("o");
//    f.read(reinterpret_cast<char *>(&c.mem[0]), 106);


//    c.run(57);

}