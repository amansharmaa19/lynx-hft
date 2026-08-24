#pragma once

#include <cstdint>
#include <map>
#include <unordered_map>

#include "common/side.h"
#include "common/types.h"
#include "market_data/market_data_event.h"

struct Order
{
    std::uint64_t order_id;
    Side side;
    Price price;
    Quantity quantity;
};

class OrderBook
{
public:
    void apply(const MarketDataEvent& event);

    Price best_bid() const;

    Price best_ask() const;

    Price spread() const;

    Price mid_price() const;

    Quantity bid_quantity(Price price) const;

    Quantity ask_quantity(Price price) const;

private:
    void add_order(const MarketDataEvent& event);

    void execute_order(const MarketDataEvent& event);

    void cancel_order(const MarketDataEvent& event);

    void delete_order(const MarketDataEvent& event);

    void replace_order(const MarketDataEvent& event);

    std::map<Price, Quantity> bids_;

    std::map<Price, Quantity> asks_;

    std::unordered_map<std::uint64_t, Order> orders_;
};