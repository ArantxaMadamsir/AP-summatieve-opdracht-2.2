#include "include/warehouse.hpp"


Warehouse::Warehouse(): employees({}), shelves({}) {}

void Warehouse::addEmployee(Employee employee) {
    employees.push_back(employee);
}

void Warehouse::addShelf(Shelf shelf) {
    shelves.push_back(shelf);
}

bool Warehouse::rearrangeShelf(Shelf& shelf) {
    // Check if there is an employee with a forklift certificate available
    bool employeeAvailable = false;
    int i = 0;

    while (!employeeAvailable && i < employees.size()) {
        Employee& employee = employees[i];

        // If there is, make them rearrange the shelf in ascending order of itemCount
        if (employee.getForkliftCertificate() && !employee.getBusy()) {
            employeeAvailable = true;
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
        }

        i++;
    }

    if (employeeAvailable) {
        return true;
    }
    else {
        return false;
    }
}

bool Warehouse::pickItems(std::string itemName, int itemCount) {
    // Check if there are enough items available
    int totalItemCount = 0;

    for (Shelf& shelf: shelves) {
        for (Pallet& pallet: shelf.pallets) {
            if (pallet.getItemName() == itemName) {
                totalItemCount += pallet.getItemCount();
            }
        }
    }

    // Return false if there are not enough items are available
    if (itemCount > totalItemCount) {
        return false;
    }

    // Pick items from the pallets
    int itemsPicked = 0;

    for (Shelf& shelf: shelves) {
        for (Pallet& pallet: shelf.pallets) {
            if (pallet.getItemName() == itemName) {
                while (pallet.getItemCount() > 0 && itemsPicked != itemCount) {
                    if (pallet.takeOne()) {
                        itemsPicked++;
                    }

                    else {
                        return false;
                    }
                }
            }

            if (itemsPicked == itemCount) {
                return true;
            }
        }
    }

    return false;
}

bool Warehouse::putItems(std::string itemName, int itemCount) {
    // Still to do
}
