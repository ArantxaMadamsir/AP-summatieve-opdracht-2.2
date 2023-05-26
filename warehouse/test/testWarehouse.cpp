#include <iostream>
#include "include/catch.hpp"
#include "../src/include/warehouse.hpp"


//////////////////////////////////////////////////////////////////
//                                                              //
//                      Warehouse unittests                     //
//                                                              //
//////////////////////////////////////////////////////////////////
//                                                              //
//   This file contains all testcases for the Warehouse class.  //
//                                                              //
//////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////
//             Warehouse::rearrangeShelf test cases             //
//////////////////////////////////////////////////////////////////

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

TEST_CASE("Rearrange half full shelf", "Warehouse::rearrangeShelf") {
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


//////////////////////////////////////////////////////////////////
//              Warehouse::pickItems test cases                 //
//////////////////////////////////////////////////////////////////

TEST_CASE("Pick items when item is not in warehouse", "Warehouse::pickItems") {
    // Construct warehouse with empty shelf.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();

    warehouse.addEmployee(Employee("Bob", true));
    warehouse.addShelf(shelf1);

    // Check if shelf is empty
    // This shelf should be empty
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    // Pick 40 toys from warehouse when there are 0 available.
    bool successful1 = warehouse.pickItems("Toys", 40);
    // Should fail
    REQUIRE(!successful1);

    // Check if shelf has been picked from.
    // This shelf should not have been picked from.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);
}

TEST_CASE("Pick items when there is no available employee", "Warehouse::pickItems") {
    // Construct warehouse with shelf of books and toys.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Toys", 100, 20), 
        Pallet("Toys", 100, 5), 
        Pallet("Books", 100, 40), 
        Pallet("Books", 100, 10)
    };

    Employee employee1("Bob", true);
    employee1.setBusy(true);

    warehouse.addEmployee(employee1);
    warehouse.addShelf(shelf1);

    // Check if shelf has been picked from.
    // This shelf should not have been picked from.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 5);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 10);

    // Pick 3 toys from warehouse when there is no available employee.
    bool successful1 = warehouse.pickItems("Toys", 3);
    // Should fail
    REQUIRE(!successful1);

    // Pick 5 books from warehouse when there is no available employee.
    bool successful2 = warehouse.pickItems("Books", 5);
    // Should fail
    REQUIRE(!successful2);

    // Check if shelf has been picked from.
    // This shelf should not have been picked from.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 5);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 40);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 10);
}

TEST_CASE("Pick items when there is an available employee but not enough items", "Warehouse::pickItems") {
    // Construct warehouse with shelves of books and toys.
    Warehouse warehouse = Warehouse();
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

    Employee employee1("Bob", true);
    warehouse.addEmployee(employee1);

    warehouse.addShelf(shelf1);
    warehouse.addShelf(shelf2);

    // Check if shelves have been picked from.
    // These shelves should not have been picked from.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 10);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 2);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 3);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 1);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 0);

    // Pick 15 toys from warehouse when there are only 12 available.
    bool successful1 = warehouse.pickItems("Toys", 15);
    // Should fail
    REQUIRE(!successful1);

    // Pick 5 books from warehouse when there are only 4 available.
    bool successful2 = warehouse.pickItems("Books", 5);
    // Should fail
    REQUIRE(!successful2);

    // Check if shelves have been picked from.
    // These shelves should not have been picked from.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 10);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 2);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 3);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 1);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 0);
}

TEST_CASE("Pick items when there is an available employee and enough items", "Warehouse::pickItems") {
    // Construct warehouse with shelves of books and toys.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Toys", 100, 20), 
        Pallet("Toys", 100, 5), 
        Pallet("Books", 100, 4), 
        Pallet("Books", 100, 1)
    };

    Shelf shelf2 = Shelf();
    shelf2.pallets = {
        Pallet("Toys", 100, 10), 
        Pallet("Books", 100, 50),
        Pallet("Books", 100, 15), 
        Pallet()
    };
    
    Employee employee1("Bob", true);
    warehouse.addEmployee(employee1);

    warehouse.addShelf(shelf1);
    warehouse.addShelf(shelf2);

    // Check if shelves have been picked from.
    // These shelves should not already have been picked from.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 20);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 5);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 4);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 1);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 10);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 50);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 15);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 0);

    // Pick 35 toys from warehouse when there are 35 available.
    bool successful1 = warehouse.pickItems("Toys", 35);
    // Should be successful
    REQUIRE(successful1);

    // Pick 60 books from warehouse when there are 70 available.
    bool successful2 = warehouse.pickItems("Books", 60);
    // Should be successful
    REQUIRE(successful2);

    // Check if shelves have been picked from.
    // These shelves should have been picked from.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 10);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 0);
}


//////////////////////////////////////////////////////////////////
//              Warehouse::putItems test cases                  //
//////////////////////////////////////////////////////////////////

TEST_CASE("Put items when item is not in warehouse", "Warehouse::putItems") {
    // Construct warehouse with empty shelf.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();

    warehouse.addEmployee(Employee("Bob", true));

    warehouse.addShelf(shelf1);

    // Check if shelf is empty
    // This shelf should be empty
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    // Put 12 toys in warehouse when there aren't any already in it.
    bool successful1 = warehouse.putItems("Toys", 12);
    // Should fail
    REQUIRE(!successful1);

    // Check if shelf has been filled.
    // This shelf should not have been filled.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);
}

TEST_CASE("Put items when there is not enough space for them", "Warehouse::putItems") {
    // Construct warehouse with shelves of books and toys.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Toys", 100, 90), 
        Pallet(), 
        Pallet("Books", 100, 100), 
        Pallet()
    };

    Shelf shelf2 = Shelf();
    shelf2.pallets = {
        Pallet(), 
        Pallet("Books", 100, 100),
        Pallet("Books", 100, 95), 
        Pallet()
    };

    Employee employee1("Bob", true);
    warehouse.addEmployee(employee1);

    warehouse.addShelf(shelf1);
    warehouse.addShelf(shelf2);

    // Check if shelves have been filled.
    // These shelves should not have been filled.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 90);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 100);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 100);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 95);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 0);

    // Put 15 toys in warehouse when there is only space for 10.
    bool successful1 = warehouse.putItems("Toys", 15);
    // Should fail
    REQUIRE(!successful1);

    // Put 10 books in warehouse when there is only space for 5.
    bool successful2 = warehouse.putItems("Books", 10);
    // Should fail
    REQUIRE(!successful2);

    // Check if shelves have been filled.
    // These shelves should not have been filled.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 90);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 100);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 0);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 0);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 100);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 95);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 0);
}

TEST_CASE("Put items when there is enough space for items", "Warehouse::putItems") {
    // Construct warehouse with shelves of books and toys.
    Warehouse warehouse = Warehouse();
    Shelf shelf1 = Shelf();
    shelf1.pallets = {
        Pallet("Toys", 100, 100), 
        Pallet(), 
        Pallet("Books", 100, 10), 
        Pallet("Books", 100, 100)
    };

    Shelf shelf2 = Shelf();
    shelf2.pallets = {
        Pallet("Toys", 100, 90), 
        Pallet("Books", 100, 100),
        Pallet("Books", 100, 95), 
        Pallet()
    };
    
    Employee employee1("Bob", true);

    warehouse.addShelf(shelf1);
    warehouse.addShelf(shelf2);

    // Check if shelves have been filled.
    // These shelves should not already have been filled.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 100);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 10);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 100);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 90);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 100);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 95);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 0);

    // Put 60 toys in warehouse when there is space for 60.
    bool successful1 = warehouse.putItems("Toys", 10);
    // Should be successful
    REQUIRE(successful1);

    // Put 60 books in warehouse when there is space for 95.
    bool successful2 = warehouse.putItems("Books", 60);
    // Should be successful
    REQUIRE(successful2);

    // Check if shelves have been filled.
    // These shelves should have been filled.
    REQUIRE(warehouse.shelves[0].pallets[0].getItemCount() == 100);
    REQUIRE(warehouse.shelves[0].pallets[1].getItemCount() == 0);
    REQUIRE(warehouse.shelves[0].pallets[2].getItemCount() == 70);
    REQUIRE(warehouse.shelves[0].pallets[3].getItemCount() == 100);

    REQUIRE(warehouse.shelves[1].pallets[0].getItemCount() == 100);
    REQUIRE(warehouse.shelves[1].pallets[1].getItemCount() == 100);
    REQUIRE(warehouse.shelves[1].pallets[2].getItemCount() == 95);
    REQUIRE(warehouse.shelves[1].pallets[3].getItemCount() == 0);
}
