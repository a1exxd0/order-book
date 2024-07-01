#ifndef STOP_ORDER_1_H
#define STOP_ORDER_1_h
#include "order_1.h"


/**
 * @brief Class to store stop orders
 */
class stop_order {
private:
    order o;
    double stop_price;

public:

    /**
     * @brief constructor
     * 
     * @param _o: order to be sent when stop price is reached
     * @param _stop_price: price to execute order at
     */
    stop_order(const order &_o, const double _stop_price) : o(_o), stop_price(_stop_price) 
    {
        if (_stop_price < 0) {
            throw std::invalid_argument(
                "Stop orders must have a stop price of zero or greater."
            );
        }
    }

    stop_order(const stop_order &_o) = default;

    [[nodiscard]] inline order& get_order() { return this->o; }
    [[nodiscard]] inline const order& get_order() const { return this->o; }

    [[nodiscard]] inline double& get_stop_price() { return this->stop_price; }
    [[nodiscard]] inline const double& get_stop_price() const { return this->stop_price; }
};

[[nodiscard]] inline bool operator==(const stop_order &o1, const stop_order &o2)
{
    return (o1.get_order() == o2.get_order() && o1.get_stop_price() == o2.get_stop_price());
}

[[nodiscard]] inline bool operator!=(const stop_order &o1, const stop_order &o2)
{
    return !(o1 == o2);
}

/**
 * ONLY CHECKS STOP PRICE
 */
[[nodiscard]] inline bool operator<(const stop_order &o1, const stop_order &o2)
{
    return o1.get_stop_price() < o2.get_stop_price();
}

/**
 * ONLY CHECKS STOP PRICE
 */
[[nodiscard]] inline bool operator<=(const stop_order &o1, const stop_order &o2)
{
    return o1.get_stop_price() <= o2.get_stop_price();
}

/**
 * ONLY CHECKS STOP PRICE
 */
[[nodiscard]] inline bool operator>(const stop_order &o1, const stop_order &o2)
{
    return !(o1 <= o2);
}

/**
 * ONLY CHECKS STOP PRICE
 */
[[nodiscard]] inline bool operator>=(const stop_order &o1, const stop_order &o2)
{
    return !(o1 < o2);
}

#endif