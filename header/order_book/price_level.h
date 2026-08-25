#pragma once

#include <cstdint>
#include <list>
#include <unordered_map>

#include "order_book/order.h"

class PriceLevel
{
public:
    using OrderList = std::list<Order>;

    void add_order(const Order& order);

    bool remove_order(std::uint64_t order_id);

    bool reduce_order_quantity(
        std::uint64_t order_id,
        Quantity quantity
    );

    Order* find_order(std::uint64_t order_id);

    const Order* find_order(std::uint64_t order_id) const;

    Quantity total_quantity() const;

    bool empty() const;

    const OrderList& orders() const;

private:
    OrderList orders_;

    std::unordered_map<std::uint64_t, OrderList::iterator> order_index_;

    Quantity total_quantity_{0};
};
