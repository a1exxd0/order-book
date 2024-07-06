#ifndef SIMPLE_ORDER_BOOK_H
#define SIMPLE_ORDER_BOOK_H

#include <string>
#include <queue>

#include "helper_types.h"

class simple_bid {
public:
    std::size_t _quantity;
    double _price;
    std::string _uid;

    simple_bid(
        const std::size_t quantity,
        const double price,
        std::string uid
        ) :
    _quantity(quantity),
    _price(price),
    _uid(std::move(uid)) {}

    simple_bid(const simple_bid &o) = default;
};

class simple_offer {
public:
    std::size_t _quantity;
    double _price;
    std::string _uid;

    simple_offer(
        const std::size_t quantity,
        const double price,
        std::string uid
        ) :
    _quantity(quantity),
    _price(price),
    _uid(std::move(uid)) {}

    simple_offer(const simple_offer &o) = default;
};

inline bool operator==(const simple_bid &o1, const simple_bid &o2) {
    return o1._price == o2._price;
}

inline bool operator==(const simple_offer &o1, const simple_offer &o2) {
    return o1._price == o2._price;
}

struct cmp {
    bool operator()(const simple_bid &o1, const simple_bid &o2) const {
        return o1._price < o2._price;
    }

    bool operator()(const simple_offer &o1, const simple_offer &o2) const {
        return o1._price > o2._price;
    }
};

class simple_order_book {
    std::priority_queue<simple_bid, std::vector<simple_bid>, cmp>
        bids;

    std::priority_queue<simple_offer, std::vector<simple_offer>, cmp>
        offers;

public:

    [[nodiscard]] bool make_bid(simple_bid o);
    [[nodiscard]] bool make_offer(simple_offer o);
    [[nodiscard]] bool make_market_bid(std::size_t quantity);
    [[nodiscard]] bool make_market_offer(std::size_t quantity);

    [[nodiscard]] bool cancel_bid(simple_bid o);
    [[nodiscard]] bool cancel_offer(simple_offer o);
};



#endif //SIMPLE_ORDER_BOOK_H
