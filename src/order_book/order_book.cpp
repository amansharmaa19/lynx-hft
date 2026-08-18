#include "order_book/order_book.h"

void OrderBook::update_bid(Price price, Quantity quantity)
{
    if (quantity == 0)
    {
        bids_.erase(price);
        return;
    }

    bids_[price] = quantity;
}

void OrderBook::update_ask(Price price, Quantity quantity)
{
    if (quantity == 0)
    {
        asks_.erase(price);
        return;
    }

    asks_[price] = quantity;
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
