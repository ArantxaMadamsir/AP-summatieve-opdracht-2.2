#pragma once
#include <iostream>
#include <array>
#include "pallet.hpp"
#include "icontainer.hpp"


class Shelf : public IContainer {
    public:
        std::array<Pallet, 4> pallets;

        Shelf();

        bool swapPallet(int slot, int slot2);

        bool isEmpty() const override;

        bool isFull() const override;

        friend std::ostream& operator<<(std::ostream& output, Shelf& shelf);
};
