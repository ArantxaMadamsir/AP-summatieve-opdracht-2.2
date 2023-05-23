#pragma once
#include <string>
#include "shelf.hpp"


class Pallet
{
    private:
        int itemCount;
        std::string itemName;
        int itemCapacity;

    public:
        Pallet();

        Pallet(std::string itemName, int itemCapacity, int itemCount);

        std::string getItemName();

        int getItemCount();

        int getRemainingSpace();

        bool relocateEmptyPallet(std::string itemName, int itemCapacity);

        bool takeOne();

        bool putOne();

};

