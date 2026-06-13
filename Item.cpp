#include "Item.h"

Item::Item(const std::string& t, const std::string& i,
           const std::string& a, int y)
    : title(t), isbn(i), author(a), year(y), available(true) {}
