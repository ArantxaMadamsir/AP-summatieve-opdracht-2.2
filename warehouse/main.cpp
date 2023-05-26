#include <iostream>
#include "src/include/warehouse.hpp"

int main(void) {
    std::cout << "====== WAREHOUSE ======" << "\n" << "\n";

    // Create warehouse
    Warehouse warehouse;

    // Add employees
    Employee employee1("Bob", true);
    Employee employee2("Bill", true);
    Employee employee3("Zara", false);

    employee1.setBusy(false);
    employee2.setBusy(false);
    employee3.setBusy(true);

    warehouse.addEmployee(employee1);
    warehouse.addEmployee(employee2);
    warehouse.addEmployee(employee3);
    
    // Add shelves
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Toys", 100, 10), 
        Pallet("Toys", 100, 2), 
        Pallet("Books", 100, 0), 
        Pallet()
    };

    Shelf shelf2 = Shelf();
    shelf2.pallets = {
        Pallet(), 
        Pallet("Books", 100, 3),
        Pallet("Books", 100, 1), 
        Pallet()
    };

    Shelf shelf3 = Shelf();

    warehouse.addShelf(shelf1);
    warehouse.addShelf(shelf2);
    warehouse.addShelf(shelf3);

    std::cout << warehouse;
}
