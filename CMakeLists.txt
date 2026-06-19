cmake_minimum_required(VERSION 3.15)
project(library_system LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# UTF-8 encoding for Chinese output in Windows console
if(MSVC)
    add_compile_options(/utf-8)
endif()

add_executable(library_system
    main.cpp
    User.cpp User.h
    Student.cpp Student.h
    Teacher.cpp Teacher.h
    Item.cpp Item.h
    Book.cpp Book.h
    Magazine.cpp Magazine.h
    BorrowRecord.cpp BorrowRecord.h
    Library.cpp Library.h
)
