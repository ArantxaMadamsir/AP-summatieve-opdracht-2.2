#include <iostream>
#include <array>

int main(void){
    std::cout << "Hello world" << std::endl;

    std::array<int, 4> pallets = {1, 2, 3};

    for (int pallet : pallets)
    {
        std::cout<< pallet << "\n";
    }

}
