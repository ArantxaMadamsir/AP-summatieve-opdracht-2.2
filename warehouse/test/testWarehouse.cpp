#include <iostream>
#include "include/catch.hpp"
#include "../src/include/warehouse.hpp"


///////////////////////////////////////////////////////////////
//                                                           //
//                    Warehouse unittests                    //
//                                                           //
///////////////////////////////////////////////////////////////
//                                                           //
// This file contains all testcases for the Warehouse class. //
//                                                           //
///////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
//           Warehouse::rearrangeShelf test cases            //
///////////////////////////////////////////////////////////////

TEST_CASE("Rearrange empty shelf", "Warehouse::rearrangeShelf") {
    // Construct empty warehouse and add empty shelf and forklift certified Employee.
    Warehouse warehouse = Warehouse();
    warehouse.addShelf(Shelf());
    warehouse.addEmployee(Employee("Bob", true));

    // Check if shelf is already arranged.
    // Empty shelf should already be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    // Rearrange the first and only shelf of the warehouse.
    bool successful = warehouse.rearrangeShelf(warehouse.shelves[0]);
    // Should be successful
    REQUIRE(successful);

    // Check if shelf is now correctly arranged.
    // Empty shelf should still be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);
}

TEST_CASE("Rearrange full shelf", "Warehouse::rearrangeShelf") {
    // Construct warehouse with unsorted shelf of books.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Books", 100, 20), 
        Pallet("Books", 100, 40), 
        Pallet("Books", 100, 30), 
        Pallet("Books", 100, 10)
    };

    warehouse.addEmployee(Employee("Bob", true));
    warehouse.addShelf(shelf1);

    // Check if shelf is already arranged.
    // This shelf should not already be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 10);

    // Rearrange the first and only shelf of the warehouse.
    bool successful = warehouse.rearrangeShelf(warehouse.shelves[0]);
    // Should be successful
    REQUIRE(successful);

    // Check if shelf is now correctly arranged.
    // Shelf should now be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 10);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 40);
}

TEST_CASE("Rearrange half filled shelf", "Warehouse::rearrangeShelf") {
    // Construct empty warehouse and unsorted shelf of books.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Books", 100, 40), 
        Pallet("Books", 100, 20), 
        Pallet(), 
        Pallet()
    };
    
    warehouse.addEmployee(Employee("Bob", true));
    warehouse.addShelf(shelf1);

    // Check if shelf is already arranged.
    // This shelf should not already be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    // Rearrange the first and only shelf of the warehouse.
    bool successful = warehouse.rearrangeShelf(warehouse.shelves[0]);
    // Should be successful
    REQUIRE(successful);

    // Check if shelf is now correctly arranged.
    // Shelf should now be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 40);
}

TEST_CASE("Rearrange shelf without qualified employee", "Warehouse::rearrangeShelf") {
    // Construct warehouse with unsorted shelf of books.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Books", 100, 20), 
        Pallet("Books", 100, 40), 
        Pallet("Books", 100, 30), 
        Pallet("Books", 100, 10)
    };
    
    warehouse.addEmployee(Employee("Bert", false));
    warehouse.addShelf(shelf1);

    // Check if shelf is already arranged.
    // This shelf should not already be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 10);

    // Rearrange the first and only shelf of the warehouse.
    bool successful = warehouse.rearrangeShelf(warehouse.shelves[0]);
    // Should fail
    REQUIRE(!successful);

    // Check if shelf is now correctly arranged.
    // Shelf should now still not be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 10);
}

TEST_CASE("Rearrange shelf with qualified, but busy, employee", "Warehouse::rearrangeShelf") {
    // Construct warehouse with unsorted shelf of books.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Books", 100, 20), 
        Pallet("Books", 100, 40), 
        Pallet("Books", 100, 30), 
        Pallet("Books", 100, 10)
    };
    
    Employee bert = Employee("Bert", true);
    bert.setBusy(true);

    warehouse.addEmployee(bert);
    warehouse.addShelf(shelf1);

    // Check if shelf is already arranged.
    // This shelf should not already be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 10);

    // Rearrange the first and only shelf of the warehouse.
    bool successful = warehouse.rearrangeShelf(warehouse.shelves[0]);
    // Should fail
    REQUIRE(!successful);

    // Check if shelf is now correctly arranged.
    // Shelf should now still not be arranged.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 30);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 10);
}


///////////////////////////////////////////////////////////////
//           Warehouse::pickItems test cases                 //
///////////////////////////////////////////////////////////////

TEST_CASE("Pick items when there aren't enough available", "Warehouse::pickItems") {
    // Construct warehouse with shelves of books and toys.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Toys", 100, 20), 
        Pallet("Toys", 100, 5), 
        Pallet("Books", 100, 40), 
        Pallet("Books", 100, 10)
    };

    Shelf shelf2 = Shelf();
    shelf2.pallets = {
        Pallet("Toys", 100, 10), 
        Pallet("Books", 100, 5),
        Pallet("Books", 100, 10), 
        Pallet()
    };

    warehouse.addShelf(shelf1);
    warehouse.addShelf(shelf2);

    // Check if shelves have been picked from.
    // These shelves should not already have been picked from.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 5);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 10);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 10);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 5);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 10);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 0);

    // Pick 40 toys from warehouse when there are only 35 available.
    bool successful1 = warehouse.pickItems("Toys", 40);
    // Should fail
    REQUIRE(!successful1);

    // Pick 70 books from warehouse when there are only 65 available.
    bool successful2 = warehouse.pickItems("Books", 70);
    // Should fail
    REQUIRE(!successful2);

    // Check if shelves have been picked from.
    // These shelves should not have been picked from.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 5);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 10);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 10);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 5);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 10);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 0);
}

TEST_CASE("Pick items when there are enough available", "Warehouse::pickItems") {
    // Construct warehouse with shelves of books and toys.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Toys", 100, 20), 
        Pallet("Toys", 100, 5), 
        Pallet("Books", 100, 40), 
        Pallet("Books", 100, 10)
    };

    Shelf shelf2 = Shelf();
    shelf2.pallets = {
        Pallet("Toys", 100, 10), 
        Pallet("Books", 100, 5),
        Pallet("Books", 100, 10), 
        Pallet()
    };

    warehouse.addShelf(shelf1);
    warehouse.addShelf(shelf2);

    // Check if shelves have been picked from.
    // These shelves should not already have been picked from.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 5);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 10);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 10);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 5);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 10);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 0);

    // Pick 35 toys from warehouse when there are 35 available.
    bool successful1 = warehouse.pickItems("Toys", 35);
    // Should be successful
    REQUIRE(successful1);

    // Pick 60 books from warehouse when there are 65 available.
    bool successful2 = warehouse.pickItems("Books", 60);
    // Should be successful
    REQUIRE(successful2);

    // Check if shelves have been picked from.
    // These shelves should not have been picked from.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 5);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 0);
}
