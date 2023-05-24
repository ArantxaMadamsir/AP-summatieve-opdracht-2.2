#include "include/pallet.hpp"


Pallet::Pallet(): itemName("Unknown"), itemCapacity(0), itemCount(0) {}

Pallet::Pallet(std::string itemName, int itemCapacity, int itemCount): itemName(itemName), itemCapacity(itemCapacity), itemCount(itemCount) {}

std::string Pallet::getItemName() {
    return itemName;
}

int Pallet::getItemCount() {
    return itemCount;
}

int Pallet::getRemainingSpace() {
    return itemCapacity - itemCount;
}

bool Pallet::reallocateEmptyPallet(std::string itemName, int itemCapacity) {
    if (itemCount == 0) {
        this->itemName = itemName;
        this->itemCapacity = itemCapacity;
        return true;
    }
    else {
        return false;
    }
}

bool Pallet::takeOne() {
    if (itemCount > 0) {
        itemCount --;
        return true;
    }
    else {
        return false;
    }
}

bool Pallet::putOne() {
    if (itemCapacity > itemCount) {
        itemCount ++;
        return true;
    }
    else {
        return false;
    }
}

bool Pallet::isEmpty() const {
    return itemCount == 0;
}

bool Pallet::isFull() const {
    return itemCount == itemCapacity;
}
