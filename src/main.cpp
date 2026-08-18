#include <iostream>

#include "order_book/order_book.h"

int main()
{
    OrderBook book;

    book.update_bid(10000, 500);
    book.update_bid(9990, 300);
    book.update_bid(9980, 800);

    book.update_ask(10010, 400);
    book.update_ask(10020, 700);
    book.update_ask(10030, 200);

    std::cout << "Best Bid: " << book.best_bid() << '\n';
    std::cout << "Best Ask: " << book.best_ask() << '\n';
    std::cout << "Spread: " << book.spread() << '\n';
    std::cout << "Mid: " << book.mid_price() << '\n';

    return 0;
}
