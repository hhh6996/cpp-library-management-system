#pragma once
#include "User.h"

// 学生类 —— 继承自 User
class Student : public User {
private:
    std::string grade;  // 年级，如 "2024级"
    std::string major;  // 专业，如 "计算机科学与技术"

public:
    Student(const std::string& name, const std::string& id,
            const std::string& phone, const std::string& grade,
            const std::string& major);

    // 重写基类虚函数
    void display() const override;
    int getMaxBorrow() const override;    // 学生最多借 5 本
    int getBorrowDays() const override;   // 学生可借 30 天
    std::string getRole() const override; // 返回 "学生"
};
