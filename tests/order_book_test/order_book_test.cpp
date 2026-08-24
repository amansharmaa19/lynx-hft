#include <gtest/gtest.h>

#include "order_book/order_book.h"

TEST(OrderBookTest, AddBid)
{
    OrderBook book;

    book.apply({
        MarketDataEventType::Add,
        1001,
        Side::Buy,
        10000,
        500
    });

    EXPECT_EQ(book.best_bid(), 10000);
}

TEST(OrderBookTest, AddMultipleBids)
{
    OrderBook book;

    book.apply({
        MarketDataEventType::Add,
        1001,
        Side::Buy,
        10000,
        500
    });

    book.apply({
        MarketDataEventType::Add,
        1002,
        Side::Buy,
        9999,
        300
    });

    EXPECT_EQ(book.best_bid(), 10000);
}

TEST(OrderBookTest, AddAsk)
{
    OrderBook book;

    book.apply({
        MarketDataEventType::Add,
        2001,
        Side::Sell,
        10001,
        200
    });

    EXPECT_EQ(book.best_ask(), 10001);
}

TEST(OrderBookTest, BestBidAndAsk)
{
    OrderBook book;

    book.apply({
        MarketDataEventType::Add,
        1001,
        Side::Buy,
        10000,
        500
    });

    book.apply({
        MarketDataEventType::Add,
        2001,
        Side::Sell,
        10001,
        200
    });

    EXPECT_EQ(book.best_bid(), 10000);
    EXPECT_EQ(book.best_ask(), 10001);
}

TEST(OrderBookTest, Spread)
{
    OrderBook book;

    book.apply({
        MarketDataEventType::Add,
        1001,
        Side::Buy,
        10000,
        500
    });

    book.apply({
        MarketDataEventType::Add,
        2001,
        Side::Sell,
        10002,
        200
    });

    EXPECT_EQ(book.spread(), 2);
}

TEST(OrderBookTest, MidPrice)
{
    OrderBook book;

    book.apply({
        MarketDataEventType::Add,
        1001,
        Side::Buy,
        10000,
        500
    });

    book.apply({
        MarketDataEventType::Add,
        2001,
        Side::Sell,
        10002,
        200
    });

    EXPECT_EQ(book.mid_price(), 10001);
}