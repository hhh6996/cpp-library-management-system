#pragma once
#include <string>
#include <iostream>

// 馆藏物品基类（抽象类）
class Item {
protected:
    std::string title;    // 书名/刊名
    std::string isbn;     // ISBN / 期刊号
    std::string author;   // 作者/主编
    int year;             // 出版年份
    bool available;       // 是否在库（未被借出）

public:
    Item(const std::string& title, const std::string& isbn,
         const std::string& author, int year);
    virtual ~Item() {}

    // 纯虚函数
    virtual void display() const = 0;          // 显示信息
    virtual std::string getType() const = 0;   // 类型名称：图书/杂志
    virtual int getMaxDays() const = 0;        // 最多可借多少天
    virtual double calcFine(int overdueDays) const = 0; // 逾期罚款计算

    // 普通函数
    std::string getIsbn()  const { return isbn; }
    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    bool isAvailable() const { return available; }
    void setAvailable(bool a) { available = a; }
};
