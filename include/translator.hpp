//
// Created by sotnem on 24.12.19.
//

#ifndef DIASM_COMPILER_HPP
#define DIASM_COMPILER_HPP

#include <deque>
#include <string>

#include "utils.hpp"

bool isLabel(const char* line);

struct Token {
    std::string text;
    enum {
        EOF,
        Comment,
    } type;
};


struct Tokenizer {

    struct Pos {
        std::string file;
        uint64_t pos;
        uint64_t col;
        uint64_t line;
        uint64_t data_size;
        char* data;
        bool allocated;
    };

    std::deque<Pos> files;
    char c;
    void addData(std::string filename, char* data = 0, size_t size = 0) {
        Pos p;
        p.col = p.line = 1;
        p.pos = 0;
        p.file = filename;
        p.allocated = false;
        if (!data) {
            p.allocated = true;
            auto f = std::ifstream(filename); f.seekg(0, f.end);
            size = f.tellg(); f.seekg(0, f.beg);
            data = (char*)malloc(size);
            f.read(data, size);
            data[size] = '\0';
        }
        p.data = data;
        p.data_size = size;
        files.push_back(p);
    }

    Pos* currentPos() {
        if (files.empty()) return nullptr; //throw std::runtime_error("")
        return &files.front();
    }

    char getChar() {
        auto cp = currentPos();
        if (!cp) return 0;
        auto pos = cp->pos;
        if (pos >= cp->data_size) return 0;
        return cp->data[pos];
    }

//    char c() {
//        if ()
//        return getChar();
//    }

    void nexChar() {
        auto cp = currentPos();
        if (!cp) return;
        auto pos = ++cp->pos;
        if (pos >= cp->data_size) {
            files.pop_front(); return;
        } else {
//            while ()
            if (cp->data[pos] == '\n') {
//                ++cp->pos;
                ++cp->line; cp->col = 1;
            } else {
                ++cp->col;
            }
        }
        c = getChar();
    }

//    template <class ... Args>
//    bool m(Args... a) {
//        auto res = ( (c == a) || ... );
//        return res;
//    }
    bool m(char c) {
        return c == this->c;
    }

    bool m(char *s) {
        auto res = false;
        for (;*s && !(res = m(*s)); ++s);
        return res;
    }

    void skipSpaces() {
        while (m(" \t\n")) nexChar();
    }
    void skipComment() {
        if (m(';')) while (nexChar(), !m('\n'));
        nexChar();
    }


    Token getToken() {
        skipSpaces();
        skipComment();

        Token t;

        if (m('\0')) {
            t.type = EOF;
            return t;
        }
        if (m("\'\"")) {
            char string_type = c;
            t.text = "";
            while (!m("'\"")) {
                if (m(0))  t.text += c;
            }
        }

//        while ()
    }


};


#endif //DIASM_COMPILER_HPP
