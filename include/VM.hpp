//
// Created by sotnem on 24.12.19.
//

#ifndef DIASM_VM_HPP
#define DIASM_VM_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <cstring>
#include <bitset>
#include <stack>

template <size_t s>
struct Mem {
    uint8_t* data = nullptr;
    Mem() {
        data = (uint8_t*)malloc(s);
        memset(data, 0, s);
    }
    ~Mem() {
        free(data);
    }

    uint8_t& operator[](size_t i) {
        return *(data + i);
    }

    template <class T>
    void write(uint64_t addr, T val) {
        *(T*)(&data[addr]) = val;
    }

};


//#define DEBUG 1

struct CPU {

    enum Ops {
        MOV  = 0b00001,
        INT  = 0b00010,
        CMP  = 0b00011,
        JE   = 0b00100,
        ADD  = 0b00101,
        JMP  = 0b00110,
        RET  = 0b00111,
        CALL = 0b01000,
    };

    Mem<1024*16> mem;

    std::stack<uint64_t> callstack;
//    Mem<1024*16> callstack;

    size_t ip;
    std::array<uint64_t,4> regs;



    int64_t cmp_flag;

    bool done;


    void run(uint64_t addr) {
        ip = addr;
        done = false;

        while(!done) {
            next(); ++ip;
//            mem[ip]
        }
    }

    void next() {
        auto command = mem[ip];
//        auto op = command >> 4;
//        auto arg1 = command & 0b1111;

        switch (command) {
            case MOV: // MOV
                mov();
                break;
            case CMP: // CMP
                cmp();
                break;

            case INT:
                int_();
                break;

            case CALL:
                call_op();
                break;
            case JE:
                je_op();
                break;
            case ADD:
                add_op();
                break;
            case JMP:
                jmp_op();
                break;
            case RET:
                ret_op();
                break;


            default:
                throw std::runtime_error("not Implemented");
        }
//        ops[op]
    }


    uint64_t read64b() {
        auto val =  *(uint64_t*)&mem[++ip];
        ip+=7;
        return val;
    }

    uint64_t readByte(){
        return mem[++ip];
    }


    void mov() {

#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif

        auto ops = mem[++ip];
        auto arg1_reg = ops >> 3 & 1;
        auto arg2_reg = ops >> 2 & 1;
        auto mwrite = ops >> 1 & 1;
        auto mread = ops & 1;

        uint64_t *o = 0;
        uint64_t i = 0;

        if (arg1_reg) {
            auto r1 = mem[++ip];
            o = &regs[r1];
        } else {
            if (mwrite) {
                auto addr = read64b();
                o = (uint64_t *)(&mem[addr]);
            } else throw std::runtime_error("Bad Instruction");
        }
        if (mwrite && arg1_reg) {
            auto addr = *o;
            o = (uint64_t *)(&mem[addr]);
        }
        if (arg2_reg) {
            auto r1 = mem[++ip];
            i = regs[r1];
        } else {
            i = read64b();
        }
        if (mread) {
            i = mem[i];
        }
        *o = i;
    }

    void cmp() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto arg = mem[++ip];
        auto reg2 = arg >> 7 & 1;
        auto r1  = arg & 0b1111111;
        if (reg2) {
            auto r2 = mem[++ip];
            cmp_flag = (regs[r1] > regs[r2] ? 1 : (regs[r1] < regs[r2] ? -1 : 0));
        } else {
            auto v2 = read64b();
            cmp_flag = (regs[r1] > v2 ? 1 : (regs[r1] < v2 ? -1 : 0));
        }
    }


    void call_op() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto addr = read64b();
        callstack.push(ip);
        ip = addr - 1;
    }


    void je_op() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto addr = read64b();
        if (cmp_flag == 0) {
            ip = addr - 1;
        };
    }

    void add_op() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto reg = readByte();
        uint64_t  val = 0;
        if (reg) {
            auto r1 = readByte();
            val = regs[r1];
        } else {
            val = read64b();
        }
        regs[0] += val;
    }


    void jmp_op() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto addr = read64b();
        ip = addr - 1;
    }

    void ret_op() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        if (callstack.empty()) done = true;
        auto addr = callstack.top();
        callstack.pop();
        ip = addr;
    }



    void int_() {
#ifdef DEBUG
        std::cout << __func__ << std::endl;
#endif
        auto arg = mem[++ip];
        if (arg == 1) {
            std::cout << (char)regs[0];
        } else if (arg == 2) {
            std::cout << &mem[regs[0]] << std::endl;
        } else {
            done = true;
        };
    }

};


#endif //DIASM_VM_HPP
