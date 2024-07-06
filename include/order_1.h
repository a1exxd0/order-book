#ifndef ORDER_1_HPP
#define ORDER_1_HPP

#include <string>
#include <utility>
#include <ctime>
#include <iostream>
#include "helper_types.h"

/**
 * @brief Class to store an order of any type that is not a pairs order or stop order
 */
class order 
{
    buy_or_sell buysell;
    std::size_t quantity;
    double price;
    std::string security_name;
    std::string user_id;
    order_type ordertype;
    time_constraint timeconstraint;

    // if the order is a good-till-date, need to know
    time_t date_cancel;

public:

    /**
     * @brief Order class with invalid errors for prices < 0
     * 
     * @param _buyorsell: BUY or SELL
     * @param _quantity: Number to trade with
     * @param _price: Price to trade at
     * @param _security_name: Name of security to trade
     * @param _user_id: Name of the person sending the order
     * @param _ordertype: MARKET, LIMIT, STOPLOSS, STOPLIMIT
     * @param _timeconstraint: GOOD_FOR_DAY, GOOD_TILL_CANCELLED, GOOD_TILL_DATE, 
     *                         IMMEDIATE_OR_CANCEL, FILL_OR_KILL
     * @param _date_cancel: time to cancel order at
     */
    order 
    (
        const buy_or_sell _buyorsell,
        const std::size_t _quantity,
        const double _price,
        std::string _security_name,
        std::string _user_id,
        const order_type _ordertype,
        const time_constraint _timeconstraint,
        const time_t _date_cancel = 0
    ) : buysell(_buyorsell),
        quantity(_quantity),
        price(_price),
        security_name(std::move(_security_name)),
        user_id(std::move(_user_id)),
        ordertype(_ordertype),
        timeconstraint(_timeconstraint),
        date_cancel(_date_cancel)
        {
            if (_price < 0) {
                throw std::invalid_argument(
                    "Orders must have a price >= 0."
                );
            }

            if (_timeconstraint == GOOD_TILL_CANCELLED) {
                time_t curr_time;
                std::time(&curr_time);
                if (date_cancel <= curr_time) {
                    throw std::invalid_argument(
                        "Order placed is a `good-till-cancelled` so must have a cancel date in the future."
                    );
                }
            }
        }

    /**
     * Copy constructor
     */
    order(const order &o) = default;

    [[nodiscard]] inline buy_or_sell& get_buy_or_sell() { return this->buysell; }
    [[nodiscard]] inline const buy_or_sell& get_buy_or_sell() const { return this->buysell; }

    [[nodiscard]] inline std::size_t& get_quantity() { return this->quantity; }
    [[nodiscard]] inline const std::size_t& get_quantity() const { return this->quantity; }

    [[nodiscard]] inline double& get_price() { return this->price; }
    [[nodiscard]] inline const double& get_price() const { return this->price; }

    [[nodiscard]] inline std::string& get_security() { return this->security_name; }
    [[nodiscard]] inline const std::string& get_security() const { return this->security_name; }

    [[nodiscard]] inline std::string& get_user_id() { return this->user_id; }
    [[nodiscard]] inline const std::string& get_user_id() const { return this->user_id; }

    [[nodiscard]] inline order_type& get_order_type() { return this->ordertype; }
    [[nodiscard]] inline const order_type& get_order_type() const { return this->ordertype; }

    [[nodiscard]] inline time_constraint& get_time_constraint() { return this->timeconstraint; }
    [[nodiscard]] inline const time_constraint& get_time_constraint() const { return this->timeconstraint; }

    [[nodiscard]] inline std::time_t& get_date_cancel() { return this->date_cancel; }
    [[nodiscard]] inline const std::time_t& get_date_cancel() const { return this->date_cancel; }

    // UNFINISHED
    [[nodiscard]] inline std::string to_string() const
    {
        std::string res;
        res += (buysell == BUY) ? "BUY " : "SELL ";
        res += "order from " + user_id + ":\n";
        res += "Quantity: " + std::to_string(quantity) + "\n";
        res += "Price: " + std::to_string(price) + "\n";

        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const order& o);
};

[[nodiscard]] inline bool operator==(const order &o1, const order &o2)
{
    return
        o1.get_buy_or_sell() == o2.get_buy_or_sell() &&
        o1.get_quantity() == o2.get_quantity() &&
        o1.get_price() == o2.get_price() &&
        o1.get_security() == o2.get_security() && 
        o1.get_user_id() == o2.get_user_id() &&
        o1.get_order_type() == o2.get_order_type() &&
        o1.get_time_constraint() == o2.get_time_constraint() &&

        // Only check this attribute if it is meaningful
        (o1.get_time_constraint() == GOOD_TILL_DATE) ?
            o1.get_date_cancel() == o2.get_date_cancel() : true;
}

[[nodiscard]] inline bool operator!=(const order &o1, const order &o2)
{
    return !(o1 == o2);
}

/**
 * @brief ONLY CHECKS RELEVANT INFORMATION AND WILL NOT CHECK IF ORDER TYPES MATCH UP
 * Assumes both orders being compared are the same.
 * 
 * To say o1 < o2 means o1 will be executed after o2 if both orders can be fulfilled,
 * ie, if o1 and o2 were bids, and o1 = 100, o2 = 101, o1 < o2.
 */
[[nodiscard]] inline bool operator<(const order &o1, const order &o2) 
{
    if (o1.get_buy_or_sell() == BUY) {
        return o1.get_price() < o2.get_price();
    } else {
        return o1.get_price() > o2.get_price();
    }
}

/**
 * @brief ONLY CHECKS RELEVANT INFORMATION AND WILL NOT CHECK IF ORDER TYPES MATCH UP
 * Assumes both orders being compared are the same.
 * 
 * To say o1 < o2 means o1 will be executed after o2 if both orders can be fulfilled,
 * ie, if o1 and o2 were bids, and o1 = 100, o2 = 101, o1 < o2.
 */
[[nodiscard]] inline bool operator<=(const order &o1, const order &o2) 
{
    if (o1.get_buy_or_sell() == BUY) {
        return o1.get_price() <= o2.get_price();
    } else {
        return o1.get_price() >= o2.get_price();
    }
}

/**
 * @brief ONLY CHECKS RELEVANT INFORMATION AND WILL NOT CHECK IF ORDER TYPES MATCH UP
 * Assumes both orders being compared are the same.
 * 
 * To say o1 > o2 means o2 will be executed after o1 if both orders can be fulfilled,
 * ie, if o1 and o2 were bids, and o2 = 100, o1 = 101, o1 > o2.
 */
[[nodiscard]] inline bool operator>(const order &o1, const order &o2) 
{
    return !(o1 <= o2);
}

/**
 * @brief ONLY CHECKS RELEVANT INFORMATION AND WILL NOT CHECK IF ORDER TYPES MATCH UP
 * Assumes both orders being compared are the same.
 * 
 * To say o1 > o2 means o2 will be executed after o1 if both orders can be fulfilled,
 * ie, if o1 and o2 were bids, and o2 = 100, o1 = 101, o1 > o2.
 */
[[nodiscard]] inline bool operator>=(const order &o1, const order &o2) 
{
    return !(o1 < o2);
}

#endif // ORDER_1_HPP