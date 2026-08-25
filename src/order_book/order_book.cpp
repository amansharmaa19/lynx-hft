#include "order_book/order_book.h"

void OrderBook::apply(const MarketDataEvent& event)
{
    switch (event.type)
    {
        case MarketDataEventType::Add:
            add_order(event);
            break;

        case MarketDataEventType::Execute:
            execute_order(event);
            break;

        case MarketDataEventType::Cancel:
            cancel_order(event);
            break;

        case MarketDataEventType::Delete:
            delete_order(event);
            break;

        case MarketDataEventType::Replace:
            replace_order(event);
            break;
    }
}

void OrderBook::add_order(const MarketDataEvent& event)
{
    Order order{
        event.order_id,
        event.side,
        event.price,
        event.quantity
    };

    orders_[event.order_id] = order;

    if (event.side == Side::Buy)
    {
        bids_[event.price] += event.quantity;
    }
    else
    {
        asks_[event.price] += event.quantity;
    }
}

void OrderBook::execute_order(const MarketDataEvent& event)
{
    auto it = orders_.find(event.order_id);

    if (it == orders_.end())
    {
        return;
    }

    Order& order = it->second;

    Quantity executed_quantity = event.quantity;

    if (executed_quantity >= order.quantity)
    {
        executed_quantity = order.quantity;
    }

    order.quantity -= executed_quantity;

    if (order.side == Side::Buy)
    {
        bids_[order.price] -= executed_quantity;

        if (bids_[order.price] == 0)
        {
            bids_.erase(order.price);
        }
    }
    else
    {
        asks_[order.price] -= executed_quantity;

        if (asks_[order.price] == 0)
        {
            asks_.erase(order.price);
        }
    }

    if (order.quantity == 0)
    {
        orders_.erase(it);
    }
}

void OrderBook::cancel_order(const MarketDataEvent& event)
{
    auto it = orders_.find(event.order_id);

    if (it == orders_.end())
    {
        return;
    }

    Order& order = it->second;

    Quantity cancelled_quantity = event.quantity;

    if (cancelled_quantity >= order.quantity)
    {
        cancelled_quantity = order.quantity;
    }

    order.quantity -= cancelled_quantity;

    if (order.side == Side::Buy)
    {
        bids_[order.price] -= cancelled_quantity;

        if (bids_[order.price] == 0)
        {
            bids_.erase(order.price);
        }
    }
    else
    {
        asks_[order.price] -= cancelled_quantity;

        if (asks_[order.price] == 0)
        {
            asks_.erase(order.price);
        }
    }

    if (order.quantity == 0)
    {
        orders_.erase(it);
    }
}

void OrderBook::delete_order(const MarketDataEvent& event)
{
    auto it = orders_.find(event.order_id);

    if (it == orders_.end())
    {
        return;
    }

    const Order& order = it->second;

    if (order.side == Side::Buy)
    {
        bids_[order.price] -= order.quantity;

        if (bids_[order.price] == 0)
        {
            bids_.erase(order.price);
        }
    }
    else
    {
        asks_[order.price] -= order.quantity;

        if (asks_[order.price] == 0)
        {
            asks_.erase(order.price);
        }
    }

    orders_.erase(it);
}

void OrderBook::replace_order(const MarketDataEvent& event)
{
    auto it = orders_.find(event.order_id);

    if (it == orders_.end())
    {
        return;
    }

    const Order old_order = it->second;

    // Remove old order from its price level.
    if (old_order.side == Side::Buy)
    {
        bids_[old_order.price] -= old_order.quantity;

        if (bids_[old_order.price] == 0)
        {
            bids_.erase(old_order.price);
        }
    }
    else
    {
        asks_[old_order.price] -= old_order.quantity;

        if (asks_[old_order.price] == 0)
        {
            asks_.erase(old_order.price);
        }
    }

    orders_.erase(it);

    // Add replacement as a new order.
    Order replacement{
        event.new_order_id,
        event.side,
        event.price,
        event.quantity
    };

    orders_[replacement.order_id] = replacement;

    if (replacement.side == Side::Buy)
    {
        bids_[replacement.price] += replacement.quantity;
    }
    else
    {
        asks_[replacement.price] += replacement.quantity;
    }
}

Price OrderBook::best_bid() const
{
    if (bids_.empty())
    {
        return 0;
    }

    return bids_.rbegin()->first;
}

Price OrderBook::best_ask() const
{
    if (asks_.empty())
    {
        return 0;
    }

    return asks_.begin()->first;
}

Price OrderBook::spread() const
{
    if (bids_.empty() || asks_.empty())
    {
        return 0;
    }

    return best_ask() - best_bid();
}

Price OrderBook::mid_price() const
{
    if (bids_.empty() || asks_.empty())
    {
        return 0;
    }

    return (best_bid() + best_ask()) / 2;
}

Quantity OrderBook::bid_quantity(Price price) const
{
    auto it = bids_.find(price);

    if (it == bids_.end())
    {
        return 0;
    }

    return it->second;
}

Quantity OrderBook::ask_quantity(Price price) const
{
    auto it = asks_.find(price);

    if (it == asks_.end())
    {
        return 0;
    }

    return it->second;
}