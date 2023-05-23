#pragma once
#include <array>
#include "warehouse.hpp"


class Shelf : public Warehouse
{
    public:
        std::array<Pallet, 4> pallets;

        Shelf();

        bool swapPallet(int slot, int slot2);

};


