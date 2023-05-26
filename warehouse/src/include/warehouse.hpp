#pragma once
#include <string>
#include <vector>
#include "employee.hpp"
#include "shelf.hpp"


class Warehouse {
    public:
        std::vector<Employee> employees;

        std::vector<Shelf> shelves;

        Warehouse();

        void addEmployee(Employee employee);

        void addShelf(Shelf shelf);

        bool checkEmployeeAvailability();

        bool checkCertifiedEmployeeAvailability();

        bool rearrangeShelf(Shelf& shelf);

        bool checkEnoughItems(std::string itemName, int itemCount);

        bool pickItems(std::string itemName, int itemCount);

        bool checkEnoughRemainingSpace(std::string itemName, int itemCount);

        bool putItems(std::string itemName, int itemCount);
};
