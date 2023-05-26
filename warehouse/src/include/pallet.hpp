#pragma once
#include <string>
#include "icontainer.hpp"


class Pallet : public IContainer {
    private:
        int itemCount;

        std::string itemName;
        
        int itemCapacity;

    public:
        Pallet();

        Pallet(std::string itemName, int itemCapacity, int itemCount);

        std::string getItemName();

        int getItemCapacity();

        int getItemCount();

        int getRemainingSpace();

        bool reallocateEmptyPallet(std::string itemName, int itemCapacity);

        bool takeOne();

        bool putOne();

        bool isEmpty() const override;

        bool isFull() const override;
};
