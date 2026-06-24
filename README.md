# 图书借阅管理系统

> ⚠️ **说明：** 本项目为大学 C++ 课程设计作业，仅供学习参考。请勿直接抄袭代码或报告，否则按所在学校学术诚信规定处理。

## 项目简介

基于控制台的图书借阅管理系统，使用 C++ 面向对象编程实现。支持图书/杂志的增删查改、学生/教师的注册管理、借书还书操作及逾期罚款自动计算。

## 功能模块

- **图书管理** — 添加/删除/搜索 图书和杂志
- **读者管理** — 添加/删除 学生和教师（不同借阅权限）
- **借阅管理** — 借书/还书/逾期查询/罚款计算

## 技术栈

- 语言：C++11
- 构建：CMake（VS2022）或 g++ 命令行
- 依赖：仅 C++ 标准库，无第三方依赖

## 类设计

```
User (抽象基类)        Item (抽象基类)
  ├── Student            ├── Book
  └── Teacher            └── Magazine

BorrowRecord ──→ Library (管理核心)
```

共 8 个类，双继承树结构。Library 通过 `vector<User*>` 和 `vector<Item*>` 基类指针统一管理，利用虚函数多态实现不同类型读者的差异化借阅规则。

## 编译运行

**VS2022：** 文件 → 打开 → CMake → 选择 `CMakeLists.txt` → Ctrl+F5

**g++：**
```bash
g++ -std=c++11 -Wall -o library_system.exe *.cpp
./library_system.exe
```

或双击 `build.bat`

## 文件结构

```
├── CMakeLists.txt          # CMake 构建配置
├── build.bat               # g++ 一键编译
├── main.cpp                # 程序入口
├── User.h/cpp              # 读者抽象基类
├── Student.h/cpp           # 学生派生类
├── Teacher.h/cpp           # 教师派生类
├── Item.h/cpp              # 馆藏抽象基类
├── Book.h/cpp              # 图书派生类
├── Magazine.h/cpp          # 杂志派生类
├── BorrowRecord.h/cpp      # 借阅记录 + 日期工具
└── Library.h/cpp           # 系统管理核心
```

## 许可

本项目仅用于学习交流，不提供任何商业用途授权。
