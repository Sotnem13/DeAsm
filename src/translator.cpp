//
// Created by sotnem on 24.12.19.
//


//#


#include <cstddef>

bool isSpace(char c) {
    return ' ' == c || '\t' == c || '\n' == c;
}

bool isDigit(char c) {
    return '0' <= c && c <= '9';
}

bool isChar(char c) {
    return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z' || c == '_';
}


bool isLabel(const char* line) {
    enum {
        start = 0,
        qtext = 3,
        text = 2,
        need2 = 1,
        done = 4,
        fail = 5,
    } s = start;

    auto c = line;
    for (;*c && s != fail;++c) {
        if (s == start) {
            if (isSpace(*c)) continue;
            s = fail;
            if (isChar(*c)) s = text;
            if (*c == '\'') s = qtext;
        } else
        if (s == qtext) {
            if (isChar(*c) || isDigit(*c)) continue;
            s = fail;
            if (*c == '\'') s = need2;
        } else
        if (s == need2) {
            if (*c == ':') s = done;
            else s = fail;
        } else
        if (s == text) {
            if (isChar(*c) || isDigit(*c)) continue;
            s = fail;
            if (*c == ':') s = done;
        } else
        if (s == done) {
            if (isSpace(*c)) continue;
            s = fail;
        }
    }

    return s == done;
}


//struct


size_t opSize(const char* beg, const char* end) {

}



void* translate(const char*) {

}


struct Translator {

//    const char* data;
//    size_t cur;

//    std::string next(){
//        data[cur]
//    }

};






