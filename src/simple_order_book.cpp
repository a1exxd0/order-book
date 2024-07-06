#include "simple_order_book.h"
#include <iostream>

inline void print_trade(const simple_offer &o) {
    std::cout << "Offer lifted from " << o._uid << ":\n";
    std::cout << "Price: " << o._price << ", Quantity: " << o._quantity << "\n";
}

inline void print_trade(const simple_bid &o) {
    std::cout << "Bid lifted from " << o._uid << ":\n";
    std::cout << "Price: " << o._price << ", Quantity: " << o._quantity << "\n";
}

inline void print_made(const simple_offer &o) {
    std::cout << "Offer inserted into book from " << o._uid << ":\n";
    std::cout << "Price: " << o._price << ", Quantity: " << o._quantity << "\n";
}

inline void print_made(const simple_bid &o) {
    std::cout << "Bid inserted into book from " << o._uid << ":\n";
    std::cout << "Price: " << o._price << ", Quantity: " << o._quantity << "\n";
}

inline void overmatched_order(
    std::priority_queue<simple_offer, std::vector<simple_offer>, cmp> &offers,
    const simple_bid &incoming) {

    simple_offer remake_offer { offers.top() };
    offers.pop();

    // Print trade
    simple_offer traded { remake_offer };
    traded._quantity = incoming._quantity;
    print_trade(traded);

    remake_offer._quantity -= incoming._quantity;
    offers.push(remake_offer);
}

inline void overmatched_order(
    std::priority_queue<simple_bid, std::vector<simple_bid>, cmp> &bids,
    const simple_offer &incoming) {

    simple_bid remake_bid { bids.top() };
    bids.pop();

    // Print trade
    simple_bid traded { remake_bid };
    traded._quantity = incoming._quantity;
    print_trade(traded);

    remake_bid._quantity -= incoming._quantity;
    bids.push(remake_bid);
}

inline void full_order(
    std::priority_queue<simple_offer, std::vector<simple_offer>, cmp> &offers,
    const simple_bid &incoming) {
    simple_offer traded { offers.top() };
    traded._quantity = incoming._quantity;
    print_trade(offers.top());
    offers.pop();
}

inline void full_order(
    std::priority_queue<simple_bid, std::vector<simple_bid>, cmp> &bids,
    const simple_offer &incoming) {
    simple_bid traded { bids.top() };
    traded._quantity = incoming._quantity;
    print_trade(bids.top());
    bids.pop();
}

[[nodiscard]] bool simple_order_book::make_bid(simple_bid o) {
    // There must be an offer to compare to
    // If best offer is more expensive than bid made, no cross
    if (offers.empty() or offers.top()._price > o._price) {
        bids.push(o);
        print_made(o);

        return false; // no trade made
    }

    // If best offer matches or is less than, check if it fulfills
    // incoming bid by itself
    if (offers.top()._quantity > o._quantity) {
        overmatched_order(offers, o);
        return true;
    }

    // If best offer is the same quantity as incoming
    else if (offers.top()._quantity == o._quantity) {
        full_order(offers, o);
        return true;
    }

    // Fulfill max
    else {
        bool trade_fulfilled = true;
        while (!offers.empty() && trade_fulfilled) {
            if (offers.top()._price > o._price || o._quantity == 0) {
                trade_fulfilled = false;
            } else if (offers.top()._quantity > o._quantity) {
                overmatched_order(offers, o);
                o._quantity = 0;
            } else if (offers.top()._quantity == o._quantity) {
                full_order(offers, o);
                o._quantity = 0;
            } else {
                const std::size_t remainder
                    = o._quantity - offers.top()._quantity;
                full_order(offers, o);
                o._quantity = remainder;
            }
        }
        return true;
    }

}

[[nodiscard]] bool simple_order_book::make_offer(simple_offer o) {

}

[[nodiscard]] bool simple_order_book::make_market_bid(std::size_t quantity) {

}

[[nodiscard]] bool simple_order_book::make_market_offer(std::size_t quantity) {

}

[[nodiscard]] bool simple_order_book::cancel_bid(simple_bid o) {

}

[[nodiscard]] bool simple_order_book::cancel_offer(simple_offer o) {

}