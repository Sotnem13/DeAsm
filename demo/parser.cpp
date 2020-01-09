//
// Created by sotnem on 09.01.20.
//

#include <iostream>

struct Arith;


using ArithPrt = Arith*;

struct Arith {

    union {
        struct {
            char op;
            Arith* a;
            Arith* b;
        };
        long d;
    };

    enum {
        Plus, Minus, Mul, Num, Op
    } type;

};


// from fp -> Haskell parser
//arith = plus <|> minus <|> expression

//plus  = (\a _ b -> Plus  a b) <$> expression <*> char '+' <*> arith
//minus = (\a _ b -> Minus a b) <$> expression <*> char '-' <*> arith
//expression = mul <|> num
//      mul = (\a _ b -> Mul a b) <$> num <*> char '*' <*> expression
//num = ((\_ e _ -> e ) <$> char '(' <*> arith <*> char ')' ) <|> (Number <$> number)


struct ParseRes {
    Arith* r;
    const char* rest;
};

bool digit(char c) {
    return c >= '0' && c <= '9';
}

ParseRes num(const char* input);
ParseRes plus(const char* input);
ParseRes minus(const char* input);
ParseRes expression(const char* input);
ParseRes mul(const char* input);


ParseRes arith(const char* input) {
    auto r = plus(input);
    if (r.r) return r;
    r = minus(input);
    if (r.r) return r;
    return expression(input);
}

ParseRes plus(const char* input) {
    Arith *res = new Arith;
    res->type = Arith::Plus;

    auto r = expression(input);
    if (!r.r || *r.rest != '+') {
        return {0, input};
    }
    res->a = r.r;
    auto r2 = arith(r.rest+1);
    if (!r2.r) {
        return {0, input};
    }
    res->b = r2.r;
    return {res, r2.rest};
}

ParseRes minus(const char* input) {
    Arith *res = new Arith;
    res->type = Arith::Minus;

    auto r = expression(input);
    if (!r.r || *r.rest != '-') {
        return {0, input};
    }
    res->a = r.r;
    auto r2 = arith(r.rest+1);
    if (!r2.r) {
        return {0, input};
    }
    res->b = r2.r;
    return {res, r2.rest};
}

ParseRes expression(const char* input) {
    auto r = mul(input);
    if (r.r) { return r; }
    return num(input);
}

ParseRes mul(const char* input) {

    Arith *res = new Arith;
    res->type = Arith::Mul;

    auto r = num(input);
    if (!r.r || *r.rest != '*') {
        return {0, input};
    }
    res->a = r.r;
    auto r2 = expression(r.rest+1);
    if (!r2.r) {
        return {0, input};
    }
    res->b = r2.r;
    return {res, r2.rest};
//    return {0, input};
}


ParseRes num(const char* input) {
    auto c = input;
    if (*c == '(') {
        auto r = arith(c+1);
        if (r.r && *r.rest == ')') {
            ++r.rest;
            return r;
        }
    }
    Arith *res = nullptr;
    bool negate = false;
    if (*c == '-') {negate = true; ++c;};
    while (digit(*c)) {
        if (!res) {res = new Arith; res->d = 0; res->type = Arith::Num;}
        res->d = res->d*10 + *c - '0';
        ++c;
    }
    if (negate) {
        if (res) {
            res->d = -res->d;
        } else {
            c = --c;
        }
    }
    return {res, c};
}

double eval(Arith* ar) {
    switch (ar->type) {
        case Arith::Plus:  return eval(ar->a) + eval(ar->b);
        case Arith::Minus: return eval(ar->a) - eval(ar->b);
        case Arith::Mul:   return eval(ar->a) * eval(ar->b);
        case Arith::Num:   return ar->d;
    }
    throw std::runtime_error("Eval error");
}

int main() {

    std::string input;
    while (input != "exit") {
        std::cin >> input;
        auto r = arith(input.c_str());
        if (!r.r) {
            std::cout << "Failed" << std::endl;
        } else {
            std::cout << eval(r.r) << std::endl;
        }

    }



}