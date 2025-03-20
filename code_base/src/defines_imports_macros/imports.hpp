#include <iostream>

// Testing Libs
#include <assert.h>
// #define NDEBUG

// STLs included
#include <vector>
#include <unordered_map>
#include <string>

// Namespace defines
#define size_t std::size_t
#define vector std::vector
#define Hash std::hash
#define hashmap std::unordered_map
#define string std::string
#define spair std::pair

// utility macros
#define print(obj) (std::cout << obj << std::endl)
#define print_ne(obj) (std::cout << obj)

// Value enums and respective macros
enum BuyOrSell
{
    // Options
    Bid = 0,
    Ask = 1
};
#define BuyOrSell enum BuyOrSell

// Defines for orders for better understanding
#define filled true
#define not_filled false
#define max_first true
#define min_first false

// comman utilities
// template <T>
void vector_merge(vector<Price *> *list, bool *reverse, int start, int mid, int end)
{
    // new sorted vector
    vector<Price *> sorted_list = vector<Price *>();

    // merge 2 pointers
    int i = start, j = mid;
    Price *A, *B;
    while (i < mid && j <= end)
    {
        A = (*list)[i];
        B = (*list)[j];

        if ((*A) == (*B))
        {
            sorted_list.push_back(A);
            i++;
            sorted_list.push_back(B);
            j++;
        }
        else if (*A > *B)
        {
            sorted_list.push_back(B);
            j++;
        }
        else
        {
            sorted_list.push_back(A);
            i++;
        }
    }
    free(A);
    free(B);

    // filling if some are left
    while (i < mid)
    {
        sorted_list.push_back((*list)[i++]);
    }
    while (j <= end)
    {
        sorted_list.push_back((*list)[j++]);
    }

    // original filler loop
    i = start;
    for (const auto &price : sorted_list)
    {
        (*list)[i++] = price;
    }

    //  TODO :need to solve this problem
    // i want to free the created vector but i am not able to. 
    // free(sorted_list);

}
void vector_sort(vector<Price *> *list, bool *reverse, int start, int end)
{
    if (start <= end)
    {
        // Single Element
        if (start == end)
        {
            return;
        }

        int mid = (int)(((end - start) / 2) + start);
        // left sort
        vector_sort(list, reverse, start, mid);
        // right sort
        vector_sort(list, reverse, mid + 1, end);

        // merging sorted lists
        vector_merge(list, reverse, start, mid, end);
    }
}