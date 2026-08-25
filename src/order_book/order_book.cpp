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

    auto& levels = (event.side == Side::Buy) ? bids_ : asks_;

    levels[event.price].add_order(order);

    order_prices_[event.order_id] = event.price;
}

void OrderBook::execute_order(const MarketDataEvent& event)
{
    auto price_it = order_prices_.find(event.order_id);

    if (price_it == order_prices_.end())
    {
        return;
    }

    Price price = price_it->second;

    auto& levels =
        (event.side == Side::Buy) ? bids_ : asks_;

    auto level_it = levels.find(price);

    if (level_it == levels.end())
    {
        return;
    }

    bool removed =
        level_it->second.reduce_order_quantity(
            event.order_id,
            event.quantity);

    if (!removed)
    {
        return;
    }

    if (level_it->second.empty())
    {
        order_prices_.erase(event.order_id);
        levels.erase(level_it);
    }
}

void OrderBook::cancel_order(const MarketDataEvent& event)
{
    auto price_it = order_prices_.find(event.order_id);

    if (price_it == order_prices_.end())
    {
        return;
    }

    Price price = price_it->second;

    auto& levels =
        (event.side == Side::Buy) ? bids_ : asks_;

    auto level_it = levels.find(price);

    if (level_it == levels.end())
    {
        return;
    }

    bool removed =
        level_it->second.reduce_order_quantity(
            event.order_id,
            event.quantity);

    if (!removed)
    {
        return;
    }

    if (level_it->second.empty())
    {
        order_prices_.erase(event.order_id);
        levels.erase(level_it);
    }
}

void OrderBook::delete_order(const MarketDataEvent& event)
{
    auto price_it = order_prices_.find(event.order_id);

    if (price_it == order_prices_.end())
    {
        return;
    }

    Price price = price_it->second;

    auto& levels = (event.side == Side::Buy) ? bids_ : asks_;

    auto level_it = levels.find(price);

    if (level_it == levels.end())
    {
        return;
    }

    if (!level_it->second.remove_order(event.order_id))
    {
        return;
    }

    order_prices_.erase(event.order_id);

    if (level_it->second.empty())
    {
        levels.erase(level_it);
    }
}

void OrderBook::replace_order(const MarketDataEvent& event)
{
    delete_order({
        MarketDataEventType::Delete,
        event.order_id,
        0,
        event.side,
        event.price,
        0
    });

    add_order(event);
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

    return it->second.total_quantity();
}

Quantity OrderBook::ask_quantity(Price price) const
{
    auto it = asks_.find(price);

    if (it == asks_.end())
    {
        return 0;
    }

    return it->second.total_quantity();
}