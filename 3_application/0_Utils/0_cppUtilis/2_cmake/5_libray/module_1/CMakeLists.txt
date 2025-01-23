cmake_minimum_required(VERSION 3.10)
project(BeRichProject_Module_1)

add_executable(Module1_executalbe main.cpp)

target_link_libraries(Module1_executalbe PRIVATE MyStaticLibrary)
target_include_directories(Module1_executalbe PRIVATE ${CMAKE_SOURCE_DIR}/3rdParty/MoneyComeDll)