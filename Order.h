#pragma once
#include "Price4.h"
#include <string>
class Order
{   
    const long time;
    const long id;              
    /// a boolean determining whether the order id a buy (true) or sell (false)
    const bool is_buy;
    /// the number of shares in the order
    int quantity;
    /// the limit price for the order (market price if market order)
    const Price4 price;
    const Price4 neg_price;
    /// symbol
    const std::string symbol;
    /// the limit this order falls under
    explicit Order(int id_, bool is_buy_, int quantity_, Price4 price4_);

public:
    explicit Order(time_t time_, long id_, bool is_buy_,
        int quantity_, long price_, std::string symbol_);
    long get_id();
    bool get_is_buy();
    int get_quantity();
    Price4 get_price();
    Price4 get_neg_price();
    void set_quantity(int new_q);
};

