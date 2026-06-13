#pragma once
#include "User.h"

// 教师类 —— 继承自 User
class Teacher : public User {
private:
    std::string title;       // 职称，如 "教授"
    std::string department;  // 院系

public:
    Teacher(const std::string& name, const std::string& id,
            const std::string& phone, const std::string& title,
            const std::string& department);

    void display() const override;
    int getMaxBorrow() const override;    // 教师最多借 10 本
    int getBorrowDays() const override;   // 教师可借 60 天
    std::string getRole() const override; // 返回 "教师"
};
