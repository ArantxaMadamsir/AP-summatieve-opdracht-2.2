#include "include/shelf.hpp"


Shelf::Shelf(): pallets({Pallet(), Pallet(), Pallet(), Pallet()}) {} 


bool Shelf::swapPallet(int slot, int slot2)
{
    // Still to do
}

bool Shelf::isEmpty() const
{
    for (const auto& pallet : pallets)
    {
        if (!pallet.isEmpty())
        {
            return false;
        }
    }
    return true;
}

bool Shelf::isFull() const
{
    for (const auto& pallet : pallets)
    {
        if (!pallet.isFull())
        {
            return false;
        }
    }
    return true;
}

