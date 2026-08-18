#include <gtest/gtest.h>

#include "order_book/order_book.h"

TEST(OrderBookTest, BestBid)
{
    OrderBook book;

    book.update_bid(10000, 500);
    book.update_bid(9999, 300);

    EXPECT_EQ(book.best_bid(), 10000);
}

TEST(OrderBookTest, BestAsk)
{
    OrderBook book;

    book.update_ask(10001, 200);
    book.update_ask(10002, 400);

    EXPECT_EQ(book.best_ask(), 10001);
}

TEST(OrderBookTest, Spread)
{
    OrderBook book;

    book.update_bid(10000, 500);
    book.update_ask(10001, 200);

    EXPECT_EQ(book.spread(), 1);
}

TEST(OrderBookTest, MidPrice)
{
    OrderBook book;

    book.update_bid(10000, 500);
    book.update_ask(10002, 200);

    EXPECT_EQ(book.mid_price(), 10001);
}

TEST(OrderBookTest, RemovePriceLevel)
{
    OrderBook book;

    book.update_bid(10000, 500);
    book.update_bid(9999, 300);

    EXPECT_EQ(book.best_bid(), 10000);

    book.update_bid(10000, 0);

    EXPECT_EQ(book.best_bid(), 9999);
}