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