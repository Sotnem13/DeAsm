cmake_minimum_required(VERSION 3.10)
project(DiAsm)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)


set(Diasm_lib_src src/translator.cpp)


add_library(Diasm ${Diasm_lib_src})

add_executable(DiAsmT main.cpp)
target_link_libraries(DiAsmT Diasm)


add_executable(tokenizer demo/tokenizer.cpp)
target_link_libraries(tokenizer Diasm)



add_executable(VMExpa demo/vm_experience.cpp)


add_executable(Expa demo/experience.cpp)
