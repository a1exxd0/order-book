#include "order_book_1.h"
#include <utility>
#include <vector>


namespace {
    /**
     * Execute a bid order. Will not check if the order is a bid order
     *
     * @param o bid order to be executed
     * @param offers offer queue in book
     * @return
     */
    [[nodiscard]] std::vector<order> execute_bid(
        const order &o,
        order_book_1::offer_queue_t &offers
        ) {

    }

    /**
     * Execute an offer order. Will not check if the order is an offer order
     *
     * @param o offer order to be executed
     * @param bids bid queue in book
     * @return
     */
    [[nodiscard]] std::vector<order> execute_offer(
        const order &o,
        order_book_1::bid_queue_t &bids
        ) {

    }

}

[[nodiscard]] bool order_book_1::check_stop_bids(const double &curr_offer_price) {

}

[[nodiscard]] bool order_book_1::check_stop_offers(const double &curr_bid_price) {

}

[[nodiscard]] std::vector<order> order_book_1::execute_order(const order &o) {

}

[[nodiscard]] either<std::string, std::string> order_book_1::make_order(const order &incoming) {

}

[[nodiscard]] either<std::string, std::string> order_book_1::make_stop_order(const order &incoming) {

}