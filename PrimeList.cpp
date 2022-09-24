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

//Printing list of primes.
void Print_List(pointer_prime primes){
    pointer_prime ptr_p = primes;
    while(ptr_p != nullptr){
        std::cout << "(" << ptr_p->index << "," << ptr_p->primeNumber << ")" << "\n";
        ptr_p = ptr_p->nextPrime;
    }
}

/*Realese used memory.*/
void Deallocate_List(pointer_prime primes){
    pointer_prime ptr_p = primes;
    while(ptr_p != nullptr){
        primes = primes->nextPrime;
        delete ptr_p;
        ptr_p = primes;
    }
}