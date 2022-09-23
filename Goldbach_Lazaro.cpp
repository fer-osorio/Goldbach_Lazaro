//-Implementation of the algorithm developed by David Hernández Lázaro to write a prime number bigger
// than 2 as a sum of two primes.

#include"Goldbach_Lazaro.hpp"
#include"Error.hpp"

//-Looks for a number in a list of type prime. If it's found, return the index in the list. If it's not
// found, it returns -1.
ui32 Find_in_list(ui32 number, pointer_prime list){
    pointer_prime ptr_p = list;
    while (ptr_p != nullptr)
    {
        if(ptr_p->primeNumber == number)
            return ptr_p->index;
        ptr_p = ptr_p->nextPrime;
    }
    //-At this point we have reach the end of the list, so...
    return -1;    
}

//-Given a even number bigger than two, it returns the a list containing all the numbers generated
// by the Lazaro method. We claim that the last element of this list is a pair of primes, whitch 
// sum is equal to the even number passed to the function.
ui32_pair_list* Lazaro_Method(ui32 even_number){
    //Even number must be bigger than 2.
    if(even_number < 3)
        Error("Goldbach_Lazaro.cpp, function Lazaro_Method: even_number < 3.");

    //-Guarding against odd numbers.
    if(even_number%2 != 0)
        Error("Goldbach_Lazaro.cpp, function Lazaro_Method: even_number%2 != 0.");

    //-Listing all the primes smallers than 'even_number'.
    pointer_prime primes = Create_Prime_List(even_number);
    //---------------------Warning: Possible source of memory leaks.--------------------------//
    ui32_pair_list *trials = new ui32_pair_list, *queue = trials;
    (trials->pair)[0] = even_number - 2;
    (trials->pair)[1] = 2;

    ui32 counter = 1;

    bool both_are_primes = false;
    while(!both_are_primes && (trials->pair)[0] > 1){
        //--------------Warning, 'new' perator used.---------------------
        queue->next_pair = new ui32_pair_list;

        (queue->next_pair->pair)[0] = (queue->pair)[0] - counter;
        (queue->next_pair->pair)[1] = (queue->pair)[1] + counter;

        queue = queue->next_pair;

        both_are_primes = Find_in_list((queue->pair)[0], primes) >= 0 &&
                          Find_in_list((queue->pair)[1], primes) >= 0;

        counter++;
    }
    if(!both_are_primes)
        Error("Goldbach_Lazaro.cpp, function Lazaro_Method: Could not find the desired primes.");

    return trials;
}