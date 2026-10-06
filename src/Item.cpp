#include "Item.h"
std::string Item::searchableText() const {
    return name + " " + category + " " + description + " " + location;
}
std::string toString(ItemType type) {
    return type == ItemType::LOST ? "LOST" : "FOUND";
}
std::string toString(ItemStatus status) {
    switch (status) {
        case ItemStatus::ACTIVE: return "ACTIVE";
        case ItemStatus::CLAIMED: return "CLAIMED";
        case ItemStatus::RETURNED: return "RETURNED";
    }
    return "UNKNOWN";
}
