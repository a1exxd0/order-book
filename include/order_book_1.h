#ifndef ORDER_BOOK_1_HPP
#define ORDER_BOOK_1_HPP

#include "order_1.h"
#include "stop_order_1.h"
#include <queue>
#include <utility>
#include <set>

template<typename _ok, typename _err>
struct either {
    _ok ok;
    _err err;
};

template<typename _cmp=std::less<order>>
    struct compare_pairs_for_book {
    [[nodiscard]] inline bool operator()(const std::pair<order, std::time_t> &o1, const std::pair<order, std::time_t> &o2)
    const {
        _cmp cmp;
        return cmp(o1.first, o2.first);
    }
};

class order_book_1 {
public:
    using bid_queue_t = 
    std::priority_queue<
        std::pair<order, std::time_t>,
        std::vector<std::pair<order, std::time_t>>, 
        compare_pairs_for_book<std::greater<>>>;

    using offer_queue_t = 
    std::priority_queue<
        std::pair<order, std::time_t>, 
        std::vector<std::pair<order, std::time_t>>, 
        compare_pairs_for_book<>>;
private:
    // Stores the pair<order, time_t> of bids. Should only contain limit orders.    
    bid_queue_t bids;

    // Stores the pair<order, time_t> of offers. Should only contain limit orders.
    offer_queue_t offers;

    // Stores the pair<time_t, order> of bids. Should only contain stop bids.
    // Iterates from smallest to biggest
    std::set<stop_order> stop_bids;

    // Stores the pair<time_t, order> of bids. Should only contain stop offers.
    // Iterates from smallest to biggest
    std::set<stop_order> stop_offers;

    /**
     * Bid order
     *
     * @param o order that is executable
     * @return vector of orders (or components of the order) it matched with
     */
    [[nodiscard]] std::vector<order> execute_bid (const order &o);

    /**
     * Offer order
     *
     * @param o order that is executable
     * @return vector of orders (or components of the order) it matched with
     */
    [[nodiscard]] std::vector<order> execute_offer (const order &o);

    /**
     * Places an order into queue. MUST HAVE AN INPUT OF AN ORDER NOT MATCHED WITH ANOTHER.
     * @param o order to be inserted into queue
     */
    void place_order(const order &o);

    /**
     * Places a stop order into queue. MUST HAVE AN INPUT OF AN ORDER NOT MATCHED WITH ANOTHER.
     * @param o order to be inserted into queue
     * @return true if the order ended up in stop queue, false if it was directly sent to make_order
     */
    [[nodiscard]] bool place_stop_order(const order &o);

    /**
     *
     * @return True if a bid was queued, false otherwise
     */
    [[nodiscard]] bool check_stop_bids();

    /**
     *
     * @return True if an offer was queued, false otherwise
     */
    [[nodiscard]] bool check_stop_offers();



public:

    [[nodiscard]] inline const bid_queue_t& get_bids() const { return this->bids; }
    [[nodiscard]] inline const offer_queue_t& get_offers() const { return this->offers; }
    [[nodiscard]] inline const std::set<stop_order>& get_stop_bids() const { return this->stop_bids; }
    [[nodiscard]] inline const std::set<stop_order>& get_stop_offers() const { return this->stop_offers; }
    [[nodiscard]] order get_top_bid() const { return bids.top().first; }
    [[nodiscard]] order get_top_offer() const { return offers.top().first; }

    /**
     * Make an order
     * @param incoming incoming order
     * @return either the result of execution or an error code
     */
    [[nodiscard]] either<std::string, std::string> make_order(const order &incoming);

    /**
     * Make a stop order
     * @param incoming incoming stop order
     * @return either the result of execution or an error code
     */
    [[nodiscard]] either<std::string, std::string> make_stop_order(const stop_order &incoming);
    
};

#endif // ORDER_BOOK_1_HPP
