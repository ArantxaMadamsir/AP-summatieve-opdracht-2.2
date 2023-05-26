#include "include/warehouse.hpp"
#include <iostream>


Warehouse::Warehouse(): 
    employees({}), shelves({}) {}

void Warehouse::addEmployee(Employee employee) {
    employees.push_back(employee);
}

void Warehouse::addShelf(Shelf shelf) {
    shelves.push_back(shelf);
}

bool Warehouse::checkEmployeeAvailability() {
    for (Employee employee : employees) {
        if (!employee.getBusy()) {
            return true;
        }
    }
    return false;
}

bool Warehouse::checkCertifiedEmployeeAvailability() {
    for (Employee employee : employees) {
        if (employee.getForkliftCertificate() && !employee.getBusy()) {
            return true;
        }
    }
    return false;
}

bool Warehouse::rearrangeShelf(Shelf& shelf) { 
    if (checkCertifiedEmployeeAvailability()) {
        bool shelfRearranged = true;
        while (shelfRearranged) {
            shelfRearranged = false;
            int j = 0;

            while (j < shelf.pallets.size() - 1) {
                if (shelf.pallets[j].getItemCount() > shelf.pallets[j+1].getItemCount()) {
                    shelf.swapPallet(j, j+1);
                    shelfRearranged = true;
                }
                j++;
            }
        }
        return true;
    }
    return false;
}

bool Warehouse::checkEnoughItems(std::string itemName, int itemCount) {
    int totalItemCount = 0;
    for (Shelf& shelf : shelves) {
        for (Pallet& pallet : shelf.pallets) {
            if (pallet.getItemName() == itemName) {
                totalItemCount += pallet.getItemCount();
            }
        }
    }
    return totalItemCount >= itemCount;
}

bool Warehouse::pickItems(std::string itemName, int itemCount) {
    if (!checkEmployeeAvailability() || !checkEnoughItems(itemName, itemCount)) {
        return false;
    }

    int itemsPicked = 0;
    for (Shelf& shelf : shelves) {
        for (Pallet& pallet : shelf.pallets) {
            if (pallet.getItemName() == itemName) {
                while (pallet.getItemCount() > 0 && itemsPicked != itemCount) {
                    if (pallet.takeOne()) {
                        itemsPicked++; // Remove this because it's redundant?
                    } 
                }
            }
        }
    }
    return true;
}

bool Warehouse::checkEnoughRemainingSpace(std::string itemName, int itemCount) {
    int totalRemainingSpace = 0;
    for (Shelf& shelf : shelves) {
        for (Pallet& pallet : shelf.pallets) {
            if (pallet.getItemName() == itemName) {
                totalRemainingSpace += pallet.getRemainingSpace();
            }
        }
    }
    return totalRemainingSpace >= itemCount;
}

bool Warehouse::putItems(std::string itemName, int itemCount) {
    if (!checkEmployeeAvailability() || !checkEnoughRemainingSpace(itemName, itemCount)) {
        return false;
    }

    int itemsPut = 0;
    for (Shelf& shelf : shelves) {
        for (Pallet& pallet : shelf.pallets) {
            if (pallet.getItemName() == itemName && !pallet.isFull()) {
                while (pallet.getRemainingSpace() >= itemCount) {
                    if (pallet.putOne()) {
                        itemsPut++; // Remove this because it's redundant?
                    }
                }
            }
        }
    }
    return true;
}
