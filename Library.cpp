#include "Library.h"
#include "Student.h"
#include "Teacher.h"
#include "Book.h"
#include "Magazine.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

// ==================== 辅助查找函数 ====================

User* Library::findUser(const string& id) {
    for (auto u : users) {
        if (u->getId() == id) return u;
    }
    return nullptr;
}

Item* Library::findItem(const string& isbn) {
    for (auto it : items) {
        if (it->getIsbn() == isbn) return it;
    }
    return nullptr;
}

int Library::countBorrowedBy(const string& userId) {
    int cnt = 0;
    for (auto& r : records) {
        if (!r.isReturned() && r.getBorrower()->getId() == userId) {
            cnt++;
        }
    }
    return cnt;
}

// ==================== 析构函数 ====================

Library::~Library() {
    // 释放所有动态分配的 User 和 Item 对象
    for (auto u : users) delete u;
    for (auto it : items) delete it;
}

// ==================== 主菜单循环 ====================

void Library::run() {
    int choice;
    while (true) {
        cout << "\n";
        cout << "╔══════════════════════════════════════╗" << endl;
        cout << "║       图 书 借 阅 管 理 系 统       ║" << endl;
        cout << "╠══════════════════════════════════════╣" << endl;
        cout << "║  1. 图书管理                        ║" << endl;
        cout << "║  2. 读者管理                        ║" << endl;
        cout << "║  3. 借阅管理                        ║" << endl;
        cout << "║  0. 退出系统                        ║" << endl;
        cout << "╚══════════════════════════════════════╝" << endl;
        cout << "请选择操作：";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "输入无效，请重新输入！" << endl;
            continue;
        }

        switch (choice) {
        case 1: bookMenu();   break;
        case 2: userMenu();   break;
        case 3: borrowMenu(); break;
        case 0:
            cout << "感谢使用，再见！" << endl;
            return;
        default:
            cout << "无效选项，请重试。" << endl;
        }
    }
}

// ==================== 图书管理子菜单 ====================

void Library::bookMenu() {
    int ch;
    while (true) {
        cout << "\n--- 图书管理 ---" << endl;
        cout << "1. 添加图书" << endl;
        cout << "2. 添加杂志" << endl;
        cout << "3. 删除馆藏" << endl;
        cout << "4. 查询馆藏" << endl;
        cout << "5. 显示全部馆藏" << endl;
        cout << "0. 返回主菜单" << endl;
        cout << "请选择：";
        cin >> ch;

        switch (ch) {
        case 1: addBook();      break;
        case 2: addMagazine();  break;
        case 3: deleteItem();   break;
        case 4: searchItems();  break;
        case 5: listAllItems(); break;
        case 0: return;
        default: cout << "无效选项。" << endl;
        }
    }
}

void Library::addBook() {
    string title, isbn, author, publisher;
    int year, pages;

    cin.ignore();
    cout << "书名：";      getline(cin, title);
    cout << "ISBN：";      getline(cin, isbn);

    // 检查 ISBN 是否已存在
    if (findItem(isbn)) {
        cout << "该 ISBN 已存在，添加失败！" << endl;
        return;
    }

    cout << "作者：";      getline(cin, author);
    cout << "出版社：";    getline(cin, publisher);
    cout << "出版年份：";  cin >> year;
    cout << "页数：";      cin >> pages;

    Book* b = new Book(title, isbn, author, year, publisher, pages);
    items.push_back(b);
    cout << "图书添加成功！" << endl;
}

void Library::addMagazine() {
    string title, issn, editor;
    int year, issueNo, month;

    cin.ignore();
    cout << "刊名：";      getline(cin, title);
    cout << "刊号：";      getline(cin, issn);

    if (findItem(issn)) {
        cout << "该刊号已存在，添加失败！" << endl;
        return;
    }

    cout << "主编：";      getline(cin, editor);
    cout << "出版年份：";  cin >> year;
    cout << "期号：";      cin >> issueNo;
    cout << "月份：";      cin >> month;

    Magazine* m = new Magazine(title, issn, editor, year, issueNo, month);
    items.push_back(m);
    cout << "杂志添加成功！" << endl;
}

void Library::deleteItem() {
    string keyword;
    cin.ignore();
    cout << "输入要删除的 ISBN/刊号：";
    getline(cin, keyword);

    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getIsbn() == keyword) {
            // 检查是否有任何关联的借阅记录（含已归还）
            // 否则删除后 BorrowRecord 中的 Item* 会变成悬空指针
            for (auto& r : records) {
                if (r.getItem() == *it) {
                    cout << "该物品存在借阅记录，无法删除！" << endl;
                    return;
                }
            }
            delete *it;
            items.erase(it);
            cout << "删除成功！" << endl;
            return;
        }
    }
    cout << "未找到该物品。" << endl;
}

void Library::searchItems() {
    string keyword;
    cin.ignore();
    cout << "输入搜索关键词（书名/ISBN/作者）：";
    getline(cin, keyword);

    bool found = false;
    for (auto it : items) {
        if (it->getTitle().find(keyword) != string::npos ||
            it->getIsbn().find(keyword) != string::npos ||
            it->getAuthor().find(keyword) != string::npos) {
            it->display();
            found = true;
        }
    }
    if (!found) cout << "未找到匹配的馆藏。" << endl;
}

void Library::listAllItems() {
    if (items.empty()) {
        cout << "馆藏为空。" << endl;
        return;
    }
    cout << "\n===== 全部馆藏（共 " << items.size() << " 件）=====" << endl;
    for (auto it : items) {
        it->display();  // 多态调用
    }
}

// ==================== 读者管理子菜单 ====================

void Library::userMenu() {
    int ch;
    while (true) {
        cout << "\n--- 读者管理 ---" << endl;
        cout << "1. 添加学生" << endl;
        cout << "2. 添加教师" << endl;
        cout << "3. 删除读者" << endl;
        cout << "4. 显示全部读者" << endl;
        cout << "0. 返回主菜单" << endl;
        cout << "请选择：";
        cin >> ch;

        switch (ch) {
        case 1: addStudent();    break;
        case 2: addTeacher();    break;
        case 3: deleteUser();    break;
        case 4: listAllUsers();  break;
        case 0: return;
        default: cout << "无效选项。" << endl;
        }
    }
}

void Library::addStudent() {
    string name, id, phone, grade, major;
    cin.ignore();
    cout << "姓名："; getline(cin, name);
    cout << "学号："; getline(cin, id);

    if (findUser(id)) {
        cout << "该学号已存在！" << endl;
        return;
    }

    cout << "电话："; getline(cin, phone);
    cout << "年级："; getline(cin, grade);
    cout << "专业："; getline(cin, major);

    users.push_back(new Student(name, id, phone, grade, major));
    cout << "学生添加成功！" << endl;
}

void Library::addTeacher() {
    string name, id, phone, title, dept;
    cin.ignore();
    cout << "姓名："; getline(cin, name);
    cout << "工号："; getline(cin, id);

    if (findUser(id)) {
        cout << "该工号已存在！" << endl;
        return;
    }

    cout << "电话："; getline(cin, phone);
    cout << "职称："; getline(cin, title);
    cout << "院系："; getline(cin, dept);

    users.push_back(new Teacher(name, id, phone, title, dept));
    cout << "教师添加成功！" << endl;
}

void Library::deleteUser() {
    string id;
    cin.ignore();
    cout << "输入要删除的读者编号：";
    getline(cin, id);

    for (auto it = users.begin(); it != users.end(); ++it) {
        if ((*it)->getId() == id) {
            // 检查是否有任何关联的借阅记录（含已归还）
            bool hasRecords = false;
            for (auto& r : records) {
                if (r.getBorrower()->getId() == id) {
                    hasRecords = true;
                    break;
                }
            }
            if (hasRecords) {
                cout << "该读者存在借阅记录，无法删除！" << endl;
                return;
            }
            delete *it;
            users.erase(it);
            cout << "删除成功！" << endl;
            return;
        }
    }
    cout << "未找到该读者。" << endl;
}

void Library::listAllUsers() {
    if (users.empty()) {
        cout << "暂无读者。" << endl;
        return;
    }
    cout << "\n===== 全部读者（共 " << users.size() << " 人）=====" << endl;
    for (auto u : users) {
        u->display();  // 多态调用
    }
}

// ==================== 借阅管理子菜单 ====================

void Library::borrowMenu() {
    int ch;
    while (true) {
        cout << "\n--- 借阅管理 ---" << endl;
        cout << "1. 借书" << endl;
        cout << "2. 还书" << endl;
        cout << "3. 查看借阅记录" << endl;
        cout << "4. 逾期记录" << endl;
        cout << "0. 返回主菜单" << endl;
        cout << "请选择：";
        cin >> ch;

        switch (ch) {
        case 1: borrowItem();   break;
        case 2: returnItem();   break;
        case 3: listRecords();  break;
        case 4: listOverdue();  break;
        case 0: return;
        default: cout << "无效选项。" << endl;
        }
    }
}

void Library::borrowItem() {
    string userId, isbn;

    if (users.empty()) {
        cout << "系统中没有读者，请先添加读者。" << endl;
        return;
    }
    if (items.empty()) {
        cout << "馆藏为空，请先添加图书或杂志。" << endl;
        return;
    }

    cin.ignore();
    cout << "读者编号："; getline(cin, userId);
    User* u = findUser(userId);
    if (!u) {
        cout << "未找到该读者！" << endl;
        return;
    }

    // 检查借阅数量上限
    int current = countBorrowedBy(userId);
    if (current >= u->getMaxBorrow()) {  // 多态调用
        cout << "借阅已达上限（" << u->getRole() << "最多可借 "
             << u->getMaxBorrow() << " 本）！" << endl;
        return;
    }

    cout << "物品 ISBN/刊号："; getline(cin, isbn);
    Item* it = findItem(isbn);
    if (!it) {
        cout << "未找到该物品！" << endl;
        return;
    }
    if (!it->isAvailable()) {
        cout << "该物品已被借出！" << endl;
        return;
    }

    // 执行借阅
    it->setAvailable(false);
    Date today = BorrowRecord::getCurrentDate();
    int days = u->getBorrowDays();  // 多态调用
    records.push_back(BorrowRecord(u, it, today, days));

    cout << "借阅成功！" << endl;
    cout << "借阅人：" << u->getName() << " (" << u->getRole() << ")" << endl;
    cout << "物品：" << it->getTitle() << " (" << it->getType() << ")" << endl;
    cout << "应还日期：" << records.back().getDueDateStr() << endl;
}

void Library::returnItem() {
    string isbn;
    cin.ignore();
    cout << "归还物品 ISBN/刊号：";
    getline(cin, isbn);

    // 查找该物品的未归还记录
    for (auto& r : records) {
        if (!r.isReturned() && r.getItem()->getIsbn() == isbn) {
            r.markReturned();
            r.getItem()->setAvailable(true);

            Date today = BorrowRecord::getCurrentDate();
            double fine = r.calcFine(today);
            int overdue = r.calcOverdueDays(today);

            cout << "归还成功！" << endl;
            if (overdue > 0) {
                cout << "逾期 " << overdue << " 天，需缴纳罚款："
                     << fine << " 元" << endl;
            } else {
                cout << "按时归还，无罚款。" << endl;
            }
            return;
        }
    }
    cout << "未找到该物品的借阅记录，或已归还。" << endl;
}

void Library::listRecords() {
    if (records.empty()) {
        cout << "暂无借阅记录。" << endl;
        return;
    }
    cout << "\n===== 全部借阅记录（共 " << records.size() << " 条）=====" << endl;
    for (auto& r : records) {
        r.display();
    }
}

void Library::listOverdue() {
    Date today = BorrowRecord::getCurrentDate();
    bool found = false;

    cout << "\n===== 逾期未还记录 =====" << endl;
    for (auto& r : records) {
        if (!r.isReturned() && r.calcOverdueDays(today) > 0) {
            r.display();
            cout << "  → 逾期 " << r.calcOverdueDays(today)
                 << " 天，罚款 " << r.calcFine(today) << " 元" << endl;
            found = true;
        }
    }
    if (!found) cout << "没有逾期记录。" << endl;
}
