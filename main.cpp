#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <cstring>
#include <unordered_map>
#include <functional>
#include <bits/unordered_map.h>
#include "translator.hpp"


//#

struct Token {

    std::string text;

    enum {
        OP,
        Number,
        Label,
        Register,
        Unknown,
        NewLine,
        EOS
    } type;

};

template<char A>
bool m(char a) {
    return a == A;
};
template<char A, char B, char ... Args>
bool m(char a) {
    return a == A || m<B,Args...>(a);
}

std::vector<Token> tokenize(const char* line) {
    std::vector<Token> res;
    res.reserve(3);

    bool tokenizing = true;
    auto c = line;

    while (tokenizing) {
        while (m<' ', '\t', ','>(*c)) ++c;
        auto beg = c;
        while (!m<' ', ',', '\n', '\0'>(*c)) { ++c; }
        Token token;
        token.text = std::string(beg, c);
        token.type = Token::Unknown;
        res.push_back(token);
        if (m<'\n'>(*c)) {
            token.text = "newLine";

            token.type = Token::NewLine;
            res.push_back(token);

        }
        if (m<'\0'>(*c)) {
            token.text = "EOS";

            token.type = Token::EOS;
            tokenizing = false;
            res.push_back(token);

        }


    }
    return res;
}

void* translate(const char* line) {


    char op[10] = {0};
    char* o = op;

//    while (*c != ' ' && o - op < sizeof(op)) *o++ = *c++;

//    char op[10] = {0};

    std::cout << line << std::endl;
    std::cout << op << std::endl;

    std::cout << std::strncmp(line, "mov", 3) << std::endl;
    return 0;
}



template <class Lamb>
struct lambdaArg : lambdaArg<decltype(&Lamb::operator())> {};

//template <class Lamb>
//struct lambdaArg<Lamb> : lambdaArg<decltype(&Lamb::operator())> {};

template <class Arg, class Ret, class Obj>
struct lambdaArg<Ret(Obj::*)(Arg) const> {
    using type = typename std::remove_cv<Arg>::type;
};

template <class Arg, class Obj>
struct lambdaArg<void(Obj::*)(Arg*) const> {
    using type = typename std::remove_cv<Arg>::type;
};


struct Wola {

    using func_ = std::function<void(void*)>;



    struct InterFunc {
        func_ f;


        template <class Lamb>
        void operator=(Lamb lamb) {
            using type = typename lambdaArg<Lamb>::type;
            f = [lamb](void* data) {
                lamb((type*)data);
            };
        };


        template <class RetType, class T>
        void operator=(std::function<RetType(T*)> a) {
            f = [a](void* data){
                a((T*)data);
            };
        }

        void operator=(nullptr_t) {
            f = nullptr;
        }

        void operator()(void* data) {
            if(f) f(data);
        }
    };


    template <class T>
    InterFunc& operator[](T* data){
        return func_tabl[data];
    };

    void eval() {
        for (auto& p: func_tabl) {
            p.second(p.first);
        }
    }


    std::unordered_map<void*, InterFunc> func_tabl;

} func_tabl;



int main() {

    int i;
    double d;
    auto lamb = [](int* a) {
        std::cout << *a << " " << std::endl;
    };

//    std::cout << typeid(lambdaArg<decltype(lamb)>::type).name() << std::endl;
//    std::cout << typeid(&decltype(lamb)::operator()).name() << std::endl;

    func_tabl[&i] = lamb;

    d = 3.14;
    i = 4;
    func_tabl.eval();


//
////        translate("       m1535434534535 rax, 50");
//    auto res = tokenize("       m1535434534535 rax, 50");
//
//
//    for (auto&r : res) {
//        std::cout << r.text << std::endl;
//    }
//        std::cout << m< '4', 'c', ','>('c') << std::endl;


/*
    {
        std::string a = "123456789012345";
        std::cout << sizeof(std::string) << std::endl;
        std::cout << (void *) &a << " " << (void *) a.c_str() << std::endl;
        std::cout << (char *) &a - (char *) a.c_str() << std::endl;
    }
    {
        std::string a = "1234567890123456";
        std::cout << sizeof(std::string) << std::endl;
        std::cout << (void *) &a << " " << (void *) a.c_str() << std::endl;
        std::cout << (char *) &a - (char *) a.c_str() << std::endl;
    }
    */
//    BinaryExpression


//    auto data = readFile("test.dasm");
//    std::cout << data.get() << std::endl;

//    auto c = translate(data);
//    auto expr = randomExpression();
//    std::cout << expr->to_string() << "=" << expr->eval() << std::endl;

    return 0;


}