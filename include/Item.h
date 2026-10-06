#pragma once
#include <string>
enum class ItemType { LOST, FOUND };
enum class ItemStatus { ACTIVE, CLAIMED, RETURNED };
struct Item {
    int id{};
    ItemType type{ItemType::LOST};
    std::string name, category, description, location, date;
    ItemStatus status{ItemStatus::ACTIVE};
    std::string searchableText() const;
};
std::string toString(ItemType type);
std::string toString(ItemStatus status);
