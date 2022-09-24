/*  This class will store the primes up to certain threshold.*/
/*  We are consider the set of primes as an ordered set.*/

#include"SomeDataTypes.hpp"

/*  We need to save the prime and its position in the set of primes, that is the reason for the 'index'
    fied; for example: the number two has the index one, the number three has the index two, the number
    five has the index three and so on.*/
typedef struct prime
{
    ui64 primeNumber;
    ui32 index;
    struct prime *nextPrime;
}Prime;

typedef Prime* pointer_prime;

/*  Creates a new element for the list of pointers.*/
pointer_prime New_pointer_prime(ui64 primeNumber, ui32 index);

//-Returns a list of the primes smallers or equals than 'threshold'.
pointer_prime Create_Prime_List(ui64 threshold);

/*  Find the primes smallers or equals than threshold using the sieve of Eratosthenes.*/
pointer_prime Eratosthenes_sieve(const ui64 threshold);

/*  This function gives us the biggest integer that is smaller or equal than the square root of
    'number'.*/
ui64 Integral_square_root(ui64 number);

void Print_List(pointer_prime primes);

/*Realese used memory.*/
void Deallocate_List(pointer_prime primes);