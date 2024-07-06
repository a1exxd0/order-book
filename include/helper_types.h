#ifndef HELPER_TYPES_H
#define HELPER_TYPES_H


/**
 * BUY: buy order
 * SELL: sell order
 */
enum buy_or_sell {
    BUY,
    SELL,
};

/**
 * MARKET: market order (execute at best current price,
 *         ignores price component of order).
 * LIMIT: limit order, executes if a trade is given at that price
 *        or better (for the incoming trader)
 */
enum order_type {
    MARKET,
    LIMIT,
};

/**
 * GOOD_FOR_DAY: cancel at the end of day
 * GOOD_TILL_CANCELLED: order stays until cancelled
 * GOOD_TILL_DATE: require date_cancel and cancel at start of that day
 * IMMEDIATE_OR_CANCEL: try and fulfil any possible order, then cancel
 * FILL_OR_KILL: execute the whole order or nothing
 */
enum time_constraint {
    GOOD_FOR_DAY,
    GOOD_TILL_CANCELLED,
    GOOD_TILL_DATE,
    IMMEDIATE_OR_CANCEL,
    FILL_OR_KILL,
};

#endif //HELPER_TYPES_H
