/*Error handling*/
#include"Error.hpp"

void Error(std::string msj1, std::string msj2 = ""){
    std::cout << "\n Somenting went wrong on " << msj1 << " " << msj2 << "\n";
    exit(EXIT_FAILURE);
}