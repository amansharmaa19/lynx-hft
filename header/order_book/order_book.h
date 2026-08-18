#pragma once

#include <cstdint>
#include <map>

using Price = std::int64_t;
using Quantity = std::int64_t;

class OrderBook
{
public:
    void update_bid(Price price, Quantity quantity);
    void update_ask(Price price, Quantity quantity);

    Price best_bid() const;
    Price best_ask() const;

    Price spread() const;
    Price mid_price() const;

private:
    std::map<Price, Quantity> bids_;
    std::map<Price, Quantity> asks_;
};
