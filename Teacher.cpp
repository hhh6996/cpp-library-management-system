#include "Teacher.h"
#include <iomanip>

Teacher::Teacher(const std::string& n, const std::string& i,
                 const std::string& p, const std::string& t,
                 const std::string& d)
    : User(n, i, p), title(t), department(d) {}

void Teacher::display() const {
    using namespace std;
    cout << "┌────────── 教师信息 ──────────┐" << endl;
    cout << "│ 姓名：" << setw(20) << left << name << " │" << endl;
    cout << "│ 工号：" << setw(20) << left << id << " │" << endl;
    cout << "│ 电话：" << setw(20) << left << phone << " │" << endl;
    cout << "│ 职称：" << setw(20) << left << title << " │" << endl;
    cout << "│ 院系：" << setw(20) << left << department << " │" << endl;
    cout << "│ 身份：教师                    │" << endl;
    cout << "│ 最多可借：10 本，借期 60 天   │" << endl;
    cout << "└──────────────────────────────┘" << endl;
}

int Teacher::getMaxBorrow() const { return 10; }

int Teacher::getBorrowDays() const { return 60; }

std::string Teacher::getRole() const { return "教师"; }
