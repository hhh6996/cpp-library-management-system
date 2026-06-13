#pragma once
#include "Item.h"

// 杂志类 —— 继承自 Item
class Magazine : public Item {
private:
    int issueNo;    // 期号
    int month;      // 发行月份

public:
    Magazine(const std::string& title, const std::string& isbn,
             const std::string& author, int year,
             int issueNo, int month);

    void display() const override;
    std::string getType() const override;
    int getMaxDays() const override;                  // 杂志可借 15 天
    double calcFine(int overdueDays) const override;  // 逾期 1.0 元/天
};
