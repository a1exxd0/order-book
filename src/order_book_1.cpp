#include "order_book_1.h"
#include <utility>
#include <vector>
#include <iterator>
#include <algorithm>

/**
 * Execute a bid order. Will not check if the order is a bid order
 *
 * @param o bid order to be executed
 * @return matched offers
 */
[[nodiscard]] std::vector<order> order_book_1::execute_bid( const order &o) {
    // Case that order is not valid
    if (offers.empty() || offers.top().first.get_price() > o.get_price())
        return {};

    // Guaranteed no fail
    auto [best_offer, time] = offers.top();

    // Full case coverage
    if (best_offer.get_quantity() > o.get_quantity()) {
        offers.pop();
        auto traded = best_offer;
        traded.get_quantity() = o.get_quantity();
        best_offer.get_quantity() -= o.get_quantity();
        offers.emplace(traded, time);

        return {traded};
    } else if (best_offer.get_quantity() == o.get_quantity()) {
        offers.pop();
        std::ignore = check_stop_bids();
        return {best_offer};
    } else {
        offers.pop();
        std::vector<order> trades = {best_offer};

        // operation changes the heap permanently
        bool ignore = check_stop_bids();

        // then recall the execution
        order new_bid = o;
        new_bid.get_quantity() -= best_offer.get_quantity();
        auto to_append = execute_bid(new_bid);
        std::ranges::copy(to_append, std::back_inserter(trades));

        return trades;
    }
}

/**
 * Execute an offer order. Will not check if the order is an offer order
 *
 * @param o offer order to be executed
 * @return
 */
[[nodiscard]] std::vector<order> order_book_1::execute_offer (const order &o) {

}


// Note that after this executes, the order that caused the execution of this
// may no longer be a valid order to execute and so should be replaced to book
// if there are leftover order components to check
[[nodiscard]] bool order_book_1::check_stop_bids() {

}

// Note that after this executes, the order that caused the execution of this
// may no longer be a valid order to execute and so should be replaced to book
// if there are leftover order components to check
[[nodiscard]] bool order_book_1::check_stop_offers() {

}

void order_book_1::place_order(const order &o) {

}

[[nodiscard]] bool order_book_1::place_stop_order(const order &o) {

}

[[nodiscard]] either<std::string, std::string> order_book_1::make_order(const order &incoming) {

}

[[nodiscard]] either<std::string, std::string> order_book_1::make_stop_order(const stop_order &incoming) {

}