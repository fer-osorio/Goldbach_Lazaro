//-Implementation of the algorithm developed by David Hernández Lázaro to write a prime number bigger
// than 2 as a sum of two primes.

#include"Goldbach_Lazaro.hpp"
#include"Error.hpp"


//-Given a even number bigger than two, it returns the a list containing all the numbers generated
// by the Lazaro method. We claim that the last element of this list is a pair of primes, whitch 
// sum is equal to the even number passed to the function.
i32_pair_list* Lazaro_Method(ui32 even_number){
    //-Even number must be bigger than 2.
    if(even_number < 3)
        Error("Goldbach_Lazaro.cpp, function Lazaro_Method: even_number < 3.");

    //-Guarding against odd numbers.
    if(even_number%2 != 0)
        Error("Goldbach_Lazaro.cpp, function Lazaro_Method: even_number%2 != 0.");

    //-Listing all the primes smallers than 'even_number'. Remember to deallocate this list.
    pointer_prime primes = Create_Prime_List(even_number);

    //-Debugging porpuses.
    //-Print_List(primes);

    //---------------------Warning: Possible source of memory leaks.--------------------------//
    i32_pair_list *trials = new i32_pair_list, *queue = trials;
    (queue->pair)[0] = even_number - 2;
    (queue->pair)[1] = 2;
    queue->next_pair = nullptr;

    //-The unique case where 'even_number - 2' is a prime.
    if (even_number == 4)
        return trials;

    ui32 counter = 1;

    bool both_are_primes = false;
    while(!both_are_primes && (queue->pair)[0] > 1){
        //--------------Warning, 'new' perator used.---------------------//
        queue->next_pair = new i32_pair_list;

        (queue->next_pair->pair)[0] = (queue->pair)[0] - counter;
        (queue->next_pair->pair)[1] = (queue->pair)[1] + counter;
        queue->next_pair->next_pair = nullptr;

        queue = queue->next_pair;

        //-Debugging porpuses.
        //std::cout << "(" << (queue->pair)[0] << ", " << (queue->pair)[1] << ")\n";

        both_are_primes = Find_in_list((queue->pair)[0], primes) >= 0 && Find_in_list((queue->pair)[1], primes) >= 0;

        //-Debugging porpuses.
        //std::cout << Find_in_list((queue->pair)[0], primes) << ", " << Find_in_list((queue->pair)[1], primes) << "\n";

        counter++;
    }
    if (!both_are_primes)
        std::cout << "\n-Lazaro_Method: Could not find the desired primes for the number " << even_number << '\n';

    Deallocate_List(primes);

    return trials;
}

//-Given a list it returns the last non-null element. If the list is empty it returns a null pointer.
i32_pair_list* Get_queue(i32_pair_list* list) {
    if (list == nullptr)
        return nullptr;
    while (list->next_pair != nullptr)
        list = list->next_pair;

    return list;
}

//-Printing a i32_pair_list list.
void Print_List(i32_pair_list* list){
    //-Length of the biggest number plus one.
    ui32 threshold_len = Length((list->pair)[0] + 2) + 1,
         //-This will be useful at the time to put jump line characters.
         counter = 1;
    while(list != nullptr){
        std::cout << "(";
        Print_spaces(threshold_len - Length((list->pair)[0]));
        std::cout << (list->pair)[0] << ", ";
        Print_spaces(threshold_len - Length((list->pair)[1]));
        std::cout << (list->pair)[1] << ")";
        if (list->next_pair != nullptr)
            std::cout << ", ";
        //-We want four columns.
        if (counter % 4 == 0)
            std::cout << "\n";
        counter++;
        list = list->next_pair;
    }
    std::cout << "\n";
}

//-Realised used memory.
void Deallocate_List(i32_pair_list* list){
    i32_pair_list* head = list;
    while(head != nullptr){
        list = head->next_pair;
        delete head;
        head = list;
    }
}