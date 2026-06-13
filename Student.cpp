#include "Student.h"
#include <iomanip>

Student::Student(const std::string& n, const std::string& i,
                 const std::string& p, const std::string& g,
                 const std::string& m)
    : User(n, i, p), grade(g), major(m) {}

void Student::display() const {
    using namespace std;
    cout << "┌────────── 学生信息 ──────────┐" << endl;
    cout << "│ 姓名：" << setw(20) << left << name << " │" << endl;
    cout << "│ 学号：" << setw(20) << left << id << " │" << endl;
    cout << "│ 电话：" << setw(20) << left << phone << " │" << endl;
    cout << "│ 年级：" << setw(20) << left << grade << " │" << endl;
    cout << "│ 专业：" << setw(20) << left << major << " │" << endl;
    cout << "│ 身份：学生                    │" << endl;
    cout << "│ 最多可借：5 本，借期 30 天    │" << endl;
    cout << "└──────────────────────────────┘" << endl;
}

int Student::getMaxBorrow() const { return 5; }

int Student::getBorrowDays() const { return 30; }

std::string Student::getRole() const { return "学生"; }
