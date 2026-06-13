#pragma once
#include <string>
#include <iostream>

// 用户基类（抽象类）
class User {
protected:
    std::string name;   // 姓名
    std::string id;     // 编号（学号/工号）
    std::string phone;  // 电话

public:
    User(const std::string& name, const std::string& id, const std::string& phone);
    virtual ~User() {}

    // 纯虚函数 —— 派生类必须实现
    virtual void display() const = 0;
    virtual int getMaxBorrow() const = 0;   // 最多可借几本
    virtual int getBorrowDays() const = 0;  // 每本可借多少天
    virtual std::string getRole() const = 0; // 角色名称：学生/教师

    // 普通成员函数
    std::string getId()   const { return id; }
    std::string getName() const { return name; }
};
