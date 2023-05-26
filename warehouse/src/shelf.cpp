#include "include/shelf.hpp"


Shelf::Shelf(): 
    pallets({Pallet(), Pallet(), Pallet(), Pallet()}) {} 

bool Shelf::swapPallet(int slot, int slot2) { // Test if method works properly without = 
    if (slot < 0 or slot >= pallets.size() or slot2 < 0 or slot2 >= pallets.size()) {
        return false;
    }
    else {
        std::swap(pallets[slot], pallets[slot2]);
        return true;
    }
}

bool Shelf::isEmpty() const {
    int emptyPalletCount = 0;

    for (Pallet pallet : pallets) {
        if (pallet.isEmpty()) {
            emptyPalletCount ++;
        }
    }
    return emptyPalletCount == 4;
}

bool Shelf::isFull() const {
    int fullPalletCount = 0;

    for (Pallet pallet : pallets) {
        if (pallet.isFull()) {
            fullPalletCount ++;
        }
    }
    return fullPalletCount == 4;
}
