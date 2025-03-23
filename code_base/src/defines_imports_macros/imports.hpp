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
// #define max_first true
// #define min_first false
bool min_first = false, max_first = true;

struct Price
{
    // Price Attributes
    int integral, fractional, scaler;

    // Constructor
    Price()
    {
        scaler = 100;
        integral = -1;
        fractional = 0;
    }
    Price(float price)
    {
        scaler = 100;
        integral = (int)price;
        fractional = (int)((price - integral) * scaler);
    }

    // Struct Utilities
    bool operator==(const Price &otherPrice) const
    {
        return ((integral == otherPrice.integral) && (fractional == otherPrice.fractional) && (scaler == otherPrice.scaler));
    }
    bool operator>(const Price &otherPrice) const
    {
        if (integral > otherPrice.integral)
        {
            return true;
        }
        else if (integral == otherPrice.integral)
        {
            return (fractional > otherPrice.fractional);
        }
        return false;
    }
    bool operator>=(const Price &otherPrice) const
    {
        if (integral > otherPrice.integral)
        {
            return true;
        }
        else if (integral == otherPrice.integral)
        {
            return (fractional >= otherPrice.fractional);
        }
        return false;
    }

    void printPrice() const
    {
        // print("Integral: " << integral);
        // print("Fractional: " << fractional);
        // print("Scaler: " << scaler);
        print("Integral: " << integral << " | Fractional: " << fractional << " | Scaler: " << scaler);
    }

    float getPrice()
    {
        return (float)((float)integral + ((float)fractional / (float)scaler));
    }
};

namespace std
{
    template <>
    struct hash<Price>
    {
        auto operator()(const Price &price) const
        {
            return ((Hash<int>()(price.integral)) ^ (Hash<int>()(price.fractional)) ^ (Hash<int>()(price.scaler)));
        }
    };

} // namespace std





// comman utilities
// template <T>
void vector_merge(vector<Price *> *list, bool *reverse, int start, int mid, int end)
{
    // new sorted vector
    vector<Price *> sorted_list = vector<Price *>();

    // merge 2 pointers
    int i = start, j = mid;
    Price *A, *B;
    bool order = (*reverse) ? (*A > *B) : (*B > *A);
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
        else if (order)
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
    while (reverse && j <= end)
    {
        sorted_list.push_back((*list)[j++]);
    }
    while (i < mid)
    {
        sorted_list.push_back((*list)[i++]);
    }
    while ((!reverse) && j <= end)
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
void linear_sort(vector<Price *> *list, vector<Price *> *sorted_list, bool *reverse)
{
    int len = list->size();
    list->clear();
    switch (*reverse)
    {
    case true:
        for (auto i = 0; i < (len); i++)
        {
            list->push_back((*sorted_list)[i]);
        }
        break;
    default:
        for (auto i = len-1; i > (-1); i--)
        {
            list->push_back((*sorted_list)[i]);
        }
        break;
    }
}



