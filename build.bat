@echo off
chcp 65001 >nul
echo ========================================
echo   图书借阅管理系统 - 编译脚本
echo ========================================
echo.
echo 正在编译...

g++ -std=c++11 -Wall -o library_system.exe ^
  main.cpp ^
  User.cpp Student.cpp Teacher.cpp ^
  Item.cpp Book.cpp Magazine.cpp ^
  BorrowRecord.cpp Library.cpp

if %ERRORLEVEL% == 0 (
    echo.
    echo ========================================
    echo   编译成功！生成 library_system.exe
    echo ========================================
    echo.
    echo 运行命令: library_system.exe
) else (
    echo.
    echo 编译失败，请检查错误信息。
)
pause
