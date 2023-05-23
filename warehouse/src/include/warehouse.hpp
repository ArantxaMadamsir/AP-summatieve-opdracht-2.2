#pragma once
#include <string>
#include <vector>
#include "employee.hpp"
#include "shelf.hpp"


class Warehouse
{
    public:
        std::vector<Employee> Employees;
        std::vector<Shelf> Shelves;


    Warehouse();

    void addEmployee(Employee employee);

    void addShelf(Shelf shelf);

    bool rearrangeShelf(Shelf& shelf);

    bool pickItems(std::string itemName, int itemCount);

};

