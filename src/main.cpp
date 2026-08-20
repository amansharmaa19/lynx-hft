#include <iostream>

#include "market_data/simulated_feed.h"
#include "order_book/order_book.h"

int main()
{
    OrderBook book;
    SimulatedFeed feed;

    MarketDataUpdate update;

    while (feed.next_update(update))
    {
        if (update.side == Side::Buy)
        {
            book.update_bid(update.price, update.quantity);
        }
        else
        {
            book.update_ask(update.price, update.quantity);
        }

        std::cout
            << "Best Bid: " << book.best_bid()
            << " | Best Ask: " << book.best_ask()
            << " | Spread: " << book.spread()
            << '\n';
    }

    return 0;
}