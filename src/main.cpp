#include <iostream>

#include "market_data/simulated_feed.h"
#include "order_book/order_book.h"

int main()
{
    OrderBook book;

    SimulatedFeed feed;

    MarketDataEvent event;

    while (feed.next_event(event))
    {
        book.apply(event);
    }

    std::cout << "Best bid: " << book.best_bid() << '\n';
    std::cout << "Best ask: " << book.best_ask() << '\n';
    std::cout << "Spread: " << book.spread() << '\n';
    std::cout << "Mid price: " << book.mid_price() << '\n';

    return 0;
}