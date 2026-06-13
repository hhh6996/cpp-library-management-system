#pragma once
#include <string>

// 简单的日期结构体
struct Date {
    int year;
    int month;
    int day;
};

class User;
class Item;

// 借阅记录类
class BorrowRecord {
private:
    User* borrower;      // 借阅者（指针，指向 User 派生类对象）
    Item* item;          // 借阅物品（指针，指向 Item 派生类对象）
    Date borrowDate;     // 借出日期
    Date dueDate;        // 应还日期
    bool returned;       // 是否已归还

public:
    BorrowRecord(User* u, Item* it, const Date& bDate, int borrowDays);

    void display() const;                        // 显示借阅记录
    int calcOverdueDays(const Date& today) const; // 计算逾期天数
    double calcFine(const Date& today) const;     // 计算罚款金额
    void markReturned() { returned = true; }

    bool isReturned() const { return returned; }
    User* getBorrower() const { return borrower; }
    Item* getItem() const { return item; }
    std::string getBorrowerName() const;
    std::string getItemTitle() const;
    std::string getDueDateStr() const;  // 格式化应还日期字符串

    // 日期工具函数
    static Date getCurrentDate();                // 获取当前日期
    static int daysBetween(const Date& d1, const Date& d2); // 两个日期相差天数
};
