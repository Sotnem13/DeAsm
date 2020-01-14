//
// Created by sotnem on 09.01.20.
//
#include <iostream>
#include <vector>
#include <cstring>
#include <map>


void vm(char* code) {
//    char code[] = {1,1, 1,2, 2,1,2,0, 3,0, 0};
    void* ops[] = {&&stop, &&get, &&add, &&print};
    auto ip = &code[0];
    bool running = true;
    int reg[8] = {0};
    while (running) {
        goto *ops[*ip];
        ret: { ++ip; }
    }
    return;
    get: {
    auto r = *++ip;
    reg[r] = std::rand()%100;
//    std::cin >> reg[r];
    goto ret;
};

    stop: {
    running = false;
    goto ret;
};

    add:{
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



struct Token {
    enum {
        read,
        reg,
        print_op,
        stop,
        eof,
        plus_op
    } type;
    int r = 0;
};

void testVM() {
    char code[] = {1,1, 1,2, 2,1,2,0, 3,0, 0};
    vm(code);
}


struct Translator {
    std::string out;
    void read() {
//        out +=
//        push_state();
//        restore_state();
//        pop_state();
//        saveC();

    }

};


struct BitStream {

    BitStream(){
        current_pos = 0;
        data = nullptr;
        size = 0;
    }

    BitStream(void* data, uint64_t size) {
        current_pos = 0;
        this->data = static_cast<uint8_t *>(data);
        this->size = size;
    }

    bool eos() {
        return current_pos >= size;
    }

    uint8_t read8() {
        return data[current_pos++];
    }
    uint16_t read16() {
        auto data_ = (uint16_t*)(data + current_pos);
        current_pos += 2;
        return *data_;
    }
    uint32_t read32() {
        auto data_ = (uint32_t*)(data + current_pos);
        current_pos += 4;
        return *data_;

    }
    uint64_t read64() {
        auto data_ = (uint64_t*)(data + current_pos);
        current_pos += 8;
        return *data_;
    }

    void reserve(uint64_t _size) {
        if (current_pos + _size < size) {
            return;
        }
        auto new_size = size * 3 / 2 + _size;
        auto new_data = malloc(new_size);

        if (data) {
            memcpy(new_data, data, size);
            free(data);
        }
        data = static_cast<uint8_t *>(new_data);
        size = new_size;
    }

    void write8(uint8_t val) {
        reserve(sizeof(val));
        data[current_pos] = val;
        current_pos++;
    }

    void write16(uint16_t val) {
        reserve(sizeof(val));
        *(uint16_t*)(data+current_pos) = val;
        current_pos+=2;
    }

    void write32(uint32_t val) {
        reserve(sizeof(val));
        *(uint32_t*)(data+current_pos) = val;
        current_pos+=4;
    }

    void write64(uint64_t val) {
        reserve(sizeof(val));
        *(uint64_t*)(data+current_pos) = val;
        current_pos+=8;
    }

//    template <class T>
//    void write(T val) {
//        *(T*)(data+current_pos) = val;
//        current_pos += sizeof(T);
//    }

    void setPos(uint64_t pos) {
        current_pos = pos;
    }

    uint64_t current_pos;
    uint64_t size;
    uint8_t *data;
};

//void readOP(BitStream& tokens, BitStream& code) {
//    code.write(READ_OP);
//    auto reg_id = tokens.read8();
//    auto reg = regs[reg_id];
//    code.write(reg);
//}
//
//
//void plusOp(BitStream& tokens, BitStream& code) {
//
//    code.write(Opcodes::plus().code);
//    auto token = tokens.read();
////    token.type
//
//
//    code.write(regs[tokens.read8()]);
//    code.write(regs[tokens.read8()]);
//    code.write(regs[tokens.read8()]);
//}

//struct Token


struct VMContext {
    int cmp_flag;
    uint64_t regs[8];
    BitStream code;
    bool running;
};

void mov(VMContext& vm) {
    auto reg = vm.code.read8();
    vm.regs[reg] = vm.code.read8();
}
void print(VMContext& vm) {
    auto reg_id = vm.code.read8();
    auto reg = vm.regs[reg_id];
    std::cout << reg << std::endl;
}

void inc(VMContext& vm) {
    auto reg_id = vm.code.read8();
    vm.regs[reg_id] += 1;
}

void jmp(VMContext& vm) {
    auto addr = vm.code.read64();
    vm.code.setPos(addr);
}

void cmp(VMContext& vm) {
    auto reg_id = vm.code.read8();
    auto val = vm.code.read64();
    auto reg = vm.regs[reg_id];
    vm.cmp_flag = (int)long(reg - val);
}
void jl(VMContext& vm) {
    auto addr = vm.code.read64();
    if (vm.cmp_flag < 0) {
        vm.code.setPos(addr);
    }
}

void eval(VMContext& vm) {
    using Op = void (*)(VMContext&);
    Op ops[] = {mov, print, inc, jmp, cmp, jl};
    vm.running = true;
    while(vm.running && !vm.code.eos()) {
        auto op = vm.code.read8();
        ops[op](vm);
    }
}

//mov r1, 0
//
//loop:
//print r1
//inc r1
//cmp r1, 10
//jl loop
//

int main() {

    /// simple label processor
    /// LabelName -> address
    std::map<std::string, uint64_t> label_addressed;
    // first pass
    // label_addressed[label] = current_pos
    // when linking step:
    // label_pos = label_addressed[label]


//    uint64_t a = 6, b = 10;

//    std::cout <<  << std::endl;

    VMContext vm;

    vm.code.write8(0);
    vm.code.write8(0);
    vm.code.write8(0);
    //24
    vm.code.write8(1); // print
    vm.code.write8(0);

    vm.code.write8(2); // inc
    vm.code.write8(0);

    vm.code.write8(4); //cmp
    vm.code.write8(0);
    vm.code.write64(10);

    vm.code.write8(5); //cmp
    vm.code.write64(3);
//    vm.code.write64(10);

    vm.code.setPos(0);

    eval(vm);

//    testVM();

    std::vector<Token> tokens;

    tokens.push_back({Token::read});
    tokens.push_back({Token::reg, 1});

    tokens.push_back({Token::read});
    tokens.push_back({Token::reg, 2});

    tokens.push_back({Token::plus_op});
    tokens.push_back({Token::reg, 1});
    tokens.push_back({Token::reg, 2});
    tokens.push_back({Token::reg, 0});

    tokens.push_back({Token::print_op});
    tokens.push_back({Token::reg, 0});

    tokens.push_back({Token::stop});
}