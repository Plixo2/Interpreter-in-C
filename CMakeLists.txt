cmake_minimum_required(VERSION 3.21)
project(data-processing-intermediate)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "-O1")
set(CMAKE_CXX_FLAGS_RELEASE "-O1")

add_executable(data-processing-intermediate main.cpp Tokenizer.cpp IterableStream.h Vm.h Math.h Gc.h LexerC.cpp LexerC.h DPI_Syntax.h DPI_Syntax.cpp Tokenizer.h Translator.h Translator.cpp DPI_Types.h)
