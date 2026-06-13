#pragma once
#include "Item.h"

// 图书类 —— 继承自 Item
class Book : public Item {
private:
    std::string publisher;  // 出版社
    int pages;              // 页数

public:
    Book(const std::string& title, const std::string& isbn,
         const std::string& author, int year,
         const std::string& publisher, int pages);

    void display() const override;
    std::string getType() const override;
    int getMaxDays() const override;                     // 图书可借 30 天
    double calcFine(int overdueDays) const override;     // 逾期 0.5 元/天
};
