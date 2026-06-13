#include "Library.h"
#include <iostream>
#include <cstdlib>

int main() {
    // 设置控制台编码为 UTF-8（Windows 下显示中文）
    #ifdef _WIN32
    system("chcp 65001 > nul");
    #endif

    std::cout << "========================================" << std::endl;
    std::cout << "      欢迎使用图书借阅管理系统 V1.0      " << std::endl;
    std::cout << "========================================" << std::endl;

    Library lib;
    lib.run();

    return 0;
}
