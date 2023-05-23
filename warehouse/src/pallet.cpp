#include "include/pallet.hpp"


Pallet::Pallet(): itemName("Unknown"), itemCapacity(0), itemCount(0) {}

Pallet::Pallet(std::string itemName, int itemCapacity, int itemCount): itemName(itemName), itemCapacity(itemCapacity), itemCount(itemCount) {}

std::string Pallet::getItemName()
{
    return itemName;
}

int Pallet::getItemCount()
{
    return itemCount;
}

int Pallet::getRemainingSpace()
{
    return itemCapacity;
}

bool Pallet::relocateEmptyPallet(std::string itemName, int itemCapacity)
{
    // Still to do
}

bool Pallet::takeOne()
{
    // Still to do
}

bool Pallet::putOne()
{
    // Still to do
}

