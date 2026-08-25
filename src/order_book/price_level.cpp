#include "order_book/price_level.h"

void PriceLevel::add_order(const Order& order)
{
    orders_.push_back(order);

    auto it = std::prev(orders_.end());

    order_index_[order.order_id] = it;

    total_quantity_ += order.quantity;
}

bool PriceLevel::remove_order(std::uint64_t order_id)
{
    auto index_it = order_index_.find(order_id);

    if (index_it == order_index_.end())
    {
        return false;
    }

    auto list_it = index_it->second;

    total_quantity_ -= list_it->quantity;

    orders_.erase(list_it);

    order_index_.erase(index_it);

    return true;
}

bool PriceLevel::reduce_order_quantity(
    std::uint64_t order_id,
    Quantity quantity)
{
    auto it = order_index_.find(order_id);

    if (it == order_index_.end())
    {
        return false;
    }

    Order& order = *it->second;

    if (quantity >= order.quantity)
    {
        total_quantity_ -= order.quantity;

        orders_.erase(it->second);
        order_index_.erase(it);

        return true;
    }

    order.quantity -= quantity;
    total_quantity_ -= quantity;

    return true;
}

Order* PriceLevel::find_order(std::uint64_t order_id)
{
    auto it = order_index_.find(order_id);

    if (it == order_index_.end())
    {
        return nullptr;
    }

    return &(*it->second);
}

const Order* PriceLevel::find_order(std::uint64_t order_id) const
{
    auto it = order_index_.find(order_id);

    if (it == order_index_.end())
    {
        return nullptr;
    }

    return &(*it->second);
}

Quantity PriceLevel::total_quantity() const
{
    return total_quantity_;
}

bool PriceLevel::empty() const
{
    return orders_.empty();
}

const PriceLevel::OrderList& PriceLevel::orders() const
{
    return orders_;
}
