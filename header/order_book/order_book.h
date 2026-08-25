#pragma once

#include <cstdint>
#include <map>
#include <unordered_map>

#include "market_data/market_data_event.h"
#include "order_book/order.h"
#include "order_book/price_level.h"

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

    using PriceLevels = std::map<Price, PriceLevel>;

    PriceLevels bids_;

    PriceLevels asks_;

    std::unordered_map<std::uint64_t, Price> order_prices_;
};