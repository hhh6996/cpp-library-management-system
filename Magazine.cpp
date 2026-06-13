#include "Magazine.h"
#include <iomanip>

Magazine::Magazine(const std::string& t, const std::string& i,
                   const std::string& a, int y,
                   int issue, int m)
    : Item(t, i, a, y), issueNo(issue), month(m) {}

void Magazine::display() const {
    using namespace std;
    cout << "┌────────── 杂志信息 ──────────┐" << endl;
    cout << "│ 刊名：" << setw(20) << left << title << " │" << endl;
    cout << "│ 刊号：" << setw(20) << left << isbn << " │" << endl;
    cout << "│ 主编：" << setw(20) << left << author << " │" << endl;
    cout << "│ 年份：" << setw(20) << left << year << " │" << endl;
    cout << "│ 期号：第" << setw(18) << left << issueNo << " │" << endl;
    cout << "│ 月份：" << setw(20) << left << month << " │" << endl;
    cout << "│ 状态：" << (available ? "在库" : "已借出") << "                    │" << endl;
    cout << "│ 类型：杂志，借期 15 天        │" << endl;
    cout << "└──────────────────────────────┘" << endl;
}

std::string Magazine::getType() const { return "杂志"; }

int Magazine::getMaxDays() const { return 15; }

double Magazine::calcFine(int overdueDays) const {
    if (overdueDays <= 0) return 0.0;
    return overdueDays * 1.0;  // 杂志逾期每天 1.0 元
}
