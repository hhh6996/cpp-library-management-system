#include "BorrowRecord.h"
#include "User.h"
#include "Item.h"
#include <iostream>
#include <iomanip>
#include <ctime>

BorrowRecord::BorrowRecord(User* u, Item* it, const Date& bDate, int borrowDays)
    : borrower(u), item(it), borrowDate(bDate), returned(false)
{
    // 根据借出日期和可借天数计算应还日期
    dueDate = borrowDate;
    dueDate.day += borrowDays;

    // 简化月份进位处理
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    while (dueDate.day > daysInMonth[dueDate.month]) {
        dueDate.day -= daysInMonth[dueDate.month];
        dueDate.month++;
        if (dueDate.month > 12) {
            dueDate.month = 1;
            dueDate.year++;
        }
    }
}

void BorrowRecord::display() const {
    using namespace std;
    cout << "借阅人：" << getBorrowerName()
         << " | 物品：" << getItemTitle()
         << " | 借出：" << borrowDate.year << "-" << borrowDate.month << "-" << borrowDate.day
         << " | 应还：" << dueDate.year << "-" << dueDate.month << "-" << dueDate.day
         << " | 状态：" << (returned ? "已还" : "未还") << endl;
}

int BorrowRecord::calcOverdueDays(const Date& today) const {
    if (returned) return 0;
    int diff = daysBetween(dueDate, today);
    return diff > 0 ? diff : 0;  // 未逾期返回 0
}

double BorrowRecord::calcFine(const Date& today) const {
    int overdue = calcOverdueDays(today);
    if (overdue <= 0) return 0.0;
    return item->calcFine(overdue);  // 多态调用：不同物品罚款不同
}

std::string BorrowRecord::getBorrowerName() const {
    return borrower->getName();
}

std::string BorrowRecord::getItemTitle() const {
    return item->getTitle();
}

std::string BorrowRecord::getDueDateStr() const {
    return std::to_string(dueDate.year) + "-" +
           std::to_string(dueDate.month) + "-" +
           std::to_string(dueDate.day);
}

// ---------- 日期工具函数 ----------

Date BorrowRecord::getCurrentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    Date d;
    d.year = 1900 + ltm->tm_year;
    d.month = 1 + ltm->tm_mon;
    d.day = ltm->tm_mday;
    return d;
}

int BorrowRecord::daysBetween(const Date& d1, const Date& d2) {
    // 简易天数计算：近似每月 30 天
    // 用于演示目的，不考虑精确闰年
    int total1 = d1.year * 365 + d1.month * 30 + d1.day;
    int total2 = d2.year * 365 + d2.month * 30 + d2.day;
    return total2 - total1;
}
