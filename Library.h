#pragma once
#include <vector>
#include "User.h"
#include "Item.h"
#include "BorrowRecord.h"

// 图书馆管理类 —— 系统核心
class Library {
private:
    std::vector<User*> users;          // 所有读者（多态指针）
    std::vector<Item*> items;          // 所有馆藏（多态指针）
    std::vector<BorrowRecord> records; // 所有借阅记录

    // 内部查找辅助
    User* findUser(const std::string& id);
    Item* findItem(const std::string& isbn);
    int countBorrowedBy(const std::string& userId); // 某读者当前借了几本

    // 子菜单
    void bookMenu();    // 图书管理
    void userMenu();    // 读者管理
    void borrowMenu();  // 借阅管理

    // 具体操作函数
    void addBook();
    void addMagazine();
    void deleteItem();
    void searchItems();
    void listAllItems();

    void addStudent();
    void addTeacher();
    void deleteUser();
    void listAllUsers();

    void borrowItem();
    void returnItem();
    void listRecords();
    void listOverdue();

public:
    ~Library();
    void run();  // 启动主循环
};
