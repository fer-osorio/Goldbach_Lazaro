#include"Goldbach_Lazaro.hpp"
#include"Error.hpp"
#include<iostream>

int main(int argc, char *argv[]){
    int number;
    std::cout << "Introduce a even number bigger than 2:\n";
    std::cin >> number;

    if (number < 3)
        Error("The number must be bigger than 2.");
    if (number%2 != 0)
        Error("The number must be an even number.");

    ui32 i, threshold = number / 2;
    i32_pair_list* LG_list = nullptr;
    for (i = 2; i <= threshold; i++) {
        LG_list = Lazaro_Method(i*2);
        if ((Get_queue(LG_list)->pair)[0] <= 0) {
            std::cout << "\nThe numbers generated by the Lazaro Method are:\n";
            Print_List(LG_list);
            Deallocate_List(LG_list);
            LG_list = nullptr;
        }
    }

    return 0;
}