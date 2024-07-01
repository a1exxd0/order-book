#include "order_book_1.h"
#include <utility>


[[nodiscard]] either<std::string, std::string> order_book_1::make_order(const order &incoming) 
{
    return {};
}

[[nodiscard]] either<std::string, std::string> order_book_1::make_stop_order(const order &incoming) 
{
    return {};
}