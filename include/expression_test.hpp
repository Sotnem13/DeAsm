//
// Created by sotnem on 24.12.19.
//

#ifndef DIASM_EXPRESSION_TEST_HPP
#define DIASM_EXPRESSION_TEST_HPP


struct Expression {
    virtual std::string to_string() = 0;
    virtual double eval() = 0;
};

struct BinaryExpression : Expression {
    Expression* a;
    Expression* b;
    char operator_;

    std::string to_string() {
        return "(" +a->to_string() + operator_ + b->to_string() + ")";
    }

    double eval() {
        auto val1 = a->eval();
        auto val2 = b->eval();
        double res;
        switch (operator_) {
            case '+': res = val1 + val2; break;
            case '-': res = val1 - val2; break;
            case '*': res = val1 * val2; break;
            case '/': res = val1 / val2; break;
            default:
                throw std::runtime_error("Invalid operator");
        }
        return res;
    }


};

struct Number : Expression {
    double value;
    std::string to_string() {
        return std::to_string(value);
    }

    double eval() {
        return value;
    }
};

struct Var : Expression {
    double value;
    std::string to_string() {
        return std::to_string(value);
    }
};


Expression* randomExpression(int d = 4) {
    auto ops = "+-/*";
    auto ops_size = 4;
    auto r = rand() % 2;
    if (d > 0) {
        BinaryExpression* b = new BinaryExpression();
        b->operator_ = ops[rand() % ops_size];
        b->a = randomExpression(d - 1);
        b->b = randomExpression(d - 1);
        return b;
    } else {
        auto n = rand() % 1000;
        auto d = rand() % 1000;
        Number* num = new Number();
        num->value = 1.0 * n / d;
        return num;
    }
}


Expression* parse(const char* input) {
    auto c = input;
    auto ops = "+-/*";
    auto ops_size = 4;
    char op = 0;
    int ob = 0;
    char* a = 0, b = 0;
    for (; *c; ++c){
        if (ob < 0) throw std::runtime_error("Invalid expression");
        if (*c == '(') {++ob; continue; }
        if (*c == ')') {--ob; continue; }

        if (ob == 0) for (auto o = ops;*o; ++o) if (*c == *o) op = *c, a=c-1, b=c+1;
        if (op) break;
    }

}









#endif //DIASM_EXPRESSION_TEST_HPP
