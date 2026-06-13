#include "Book.h"
#include <iomanip>

Book::Book(const std::string& t, const std::string& i,
           const std::string& a, int y,
           const std::string& pub, int pg)
    : Item(t, i, a, y), publisher(pub), pages(pg) {}

void Book::display() const {
    using namespace std;
    cout << "┌────────── 图书信息 ──────────┐" << endl;
    cout << "│ 书名：" << setw(20) << left << title << " │" << endl;
    cout << "│ ISBN：" << setw(20) << left << isbn << " │" << endl;
    cout << "│ 作者：" << setw(20) << left << author << " │" << endl;
    cout << "│ 出版社：" << setw(18) << left << publisher << " │" << endl;
    cout << "│ 年份：" << setw(20) << left << year << " │" << endl;
    cout << "│ 页数：" << setw(20) << left << pages << " │" << endl;
    cout << "│ 状态：" << (available ? "在库" : "已借出") << "                    │" << endl;
    cout << "│ 类型：图书，借期 30 天        │" << endl;
    cout << "└──────────────────────────────┘" << endl;
}

std::string Book::getType() const { return "图书"; }

int Book::getMaxDays() const { return 30; }

double Book::calcFine(int overdueDays) const {
    if (overdueDays <= 0) return 0.0;
    return overdueDays * 0.5;  // 图书逾期每天 0.5 元
}
