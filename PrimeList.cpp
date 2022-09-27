/*  This class will store the primes up to a certain threshold.*/

#include <iostream>
#include "PrimeList.hpp"

//-Returns a list of the primes smallers or equals than 'threshold'. Remember to delete the list once it has 
// fulfilled its objective.
pointer_prime Create_Prime_List(ui64 threshold){;
    return Eratosthenes_sieve(threshold);
}

/*  This function gives us the biggest integer that is smaller or equal than the square root of
        'number'.*/
ui64 Integral_square_root(ui64 number){
    ui64 root = 1;
    while(root*root <= number) root++;

    return root-1;
}

/*  Creates a new element for the list of pointers. Remember to deallocate the memory used.*/
pointer_prime New_pointer_prime(ui64 primeNumber, ui32 index){
    /*New pointer prime (npp). Posible source of memory leaks.*/
    pointer_prime npp = new prime;
    npp->primeNumber = primeNumber;
    npp->index = index;
    npp->nextPrime = nullptr;

    return npp;
}

/* -Find the primes smallers or equals than threshold using the sieve of Eratosthenes. Remember to deallocate the
    memory used once the list is not more useful.*/
pointer_prime Eratosthenes_sieve(const ui64 threshold){
    /*  Whith the sieve algoritm, we just need to look up to the square root of the desire
        threshold.*/
    ui64 sieveThreshold = Integral_square_root(threshold), i, j, k;
    /*  This array is going to mark the 'sieved' numbers.*/
    ui08 * marketNumbers = new ui08[threshold + 1];
    for(j = 0; j <= threshold; j++)  marketNumbers[j] = '0';

    i = 2;
    /*  This while loop is going to put a '1' whenever the array index isn't a prime.*/
    while(i <= sieveThreshold){
        while(marketNumbers[i] == '1')    i++;
    
        j = 2; k = i*j;
        while(k <= threshold){
            /*Marking the numbers that are not */
            marketNumbers[k] = '1';
            j++; k = i*j;
        }
        i++;
    }

    // Debugging porpuses.
    /*for(i = 0; i < threshold; i++)
        std::cout << marketNumbers[i] << ",";
    std::cout << marketNumbers[threshold] << "\n";*/

    /*Creating and initializing our list of */
    pointer_prime listOfPrimes = New_pointer_prime(2,1);
    pointer_prime queue = listOfPrimes;

    /*Creating the list of prime from the 'marketNumbers' array.*/
    j = 2;
    for(i = 3; i <= threshold; i++)
        /*If marketNumbers[i] == '0', then the intex i is a prime.*/
        if(marketNumbers[i] == '0'){
            queue->nextPrime = New_pointer_prime(i,j);
            queue = queue->nextPrime;
            j++;
        }

    return listOfPrimes;
}

//-Looks for a number in a list of type prime. If it's found, return the index in the list. If it's not
// found, it returns -1.
int Find_in_list(ui32 number, pointer_prime list) {
    while (list != nullptr)
    {
        if (list->primeNumber == number)
            return list->index;

        list = list->nextPrime;
    }
    //-At this point we have reach the end of the list, so...
    return -1;
}

/*-Realese used memory.*/
void Deallocate_List(pointer_prime list){
    pointer_prime head = list;
    while(head != nullptr){
        list = list->nextPrime;
        delete head;
        head = list;
    }
}

//---------------------------------------- Printing porpuses ----------------------------------------------//

//-Returns the length of the string that represents the number in base 10.
ui32 Length(int number) {
    ui32 length = 0;
    //-Considering the minus sign.
    if (number < 0) {
        length = 1;
        number = -number;
    }
    if (number == 0)
        return 1;
    while (number > 0) {
        length++;
        //-'Removing' the last digit.
        number -= number % 10;
        number /= 10;
    }
    return length;
}

//-Prints the specified number of spaces.
void Print_spaces(ui32 numb_spcs) {
    for (ui32 i = 0; i < numb_spcs; i++)
        std::cout << " ";
}

//-Printing list of primes.
void Print_List(pointer_prime list) {
    while (list != nullptr) {
        std::cout << "(" << list->index << "," << list->primeNumber << ")\n";
        list = list->nextPrime;
    }
}