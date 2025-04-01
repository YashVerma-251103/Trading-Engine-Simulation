// * Main wrapper
#include <iostream>

// * STLs
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

// * Testing libraries
#include <assert.h>

// ? Name-space defines and macros
#define size_t std::size_t
#define vector std::vector
#define Hash std::hash
#define hashmap std::unordered_map
#define string std::string
#define pair std::pair
#define shObj(obj) std::make_shared<obj>
#define shPtr(obj) std::shared_ptr<obj>

// ? Utility macros
#define print(obj) (std::cout << obj)
#define println(obj) (std::cout << obj << std::endl)
#define filled true
#define not_filled false

bool min_first = false, max_first = true;

// ! Structs and enums macros and defines
#define BuyOrSell enum BuyOrSell
BuyOrSell{
    // * Options
    Bid = 0,
    Ask = 1};
