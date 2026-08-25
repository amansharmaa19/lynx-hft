#include <gtest/gtest.h>

#include "order_book/order_book.h"

TEST(OrderBookTest, AddBid)
{
    OrderBook book;

    book.apply({
        MarketDataEventType::Add,
        1001,
        0,
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
        0,
        Side::Buy,
        10000,
        500
    });

    book.apply({
        MarketDataEventType::Add,
        1002,
        0,
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
        0,
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
        0,
        Side::Buy,
        10000,
        500
    });

    book.apply({
        MarketDataEventType::Add,
        2001,
        0,
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
        0,
        Side::Buy,
        10000,
        500
    });

    book.apply({
        MarketDataEventType::Add,
        2001,
        0,
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
        0,
        Side::Buy,
        10000,
        500
    });

    book.apply({
        MarketDataEventType::Add,
        2001,
        0,
        Side::Sell,
        10002,
        200
    });

    EXPECT_EQ(book.mid_price(), 10001);
}

TEST(OrderBookTest, ExecuteOrder)
{
    OrderBook book;

    book.apply({
        MarketDataEventType::Add,
        1001,
        0,
        Side::Buy,
        10000,
        500
    });

    book.apply({
        MarketDataEventType::Execute,
        1001,
        0,
        Side::Buy,
        10000,
        200
    });

    EXPECT_EQ(book.bid_quantity(10000), 300);
    EXPECT_EQ(book.best_bid(), 10000);
}

TEST(OrderBookTest, ExecuteEntireOrderRemovesOrder)
{
    OrderBook book;

    book.apply({
        MarketDataEventType::Add,
        1001,
        0,
        Side::Buy,
        10000,
        500
    });

    book.apply({
        MarketDataEventType::Execute,
        1001,
        0,
        Side::Buy,
        10000,
        500
    });

    EXPECT_EQ(book.bid_quantity(10000), 0);
    EXPECT_EQ(book.best_bid(), 0);
}

TEST(OrderBookTest, CancelOrder)
{
    OrderBook book;

    book.apply({
        MarketDataEventType::Add,
        1001,
        0,
        Side::Buy,
        10000,
        500
    });

    book.apply({
        MarketDataEventType::Cancel,
        1001,
        0,
        Side::Buy,
        10000,
        200
    });

    EXPECT_EQ(book.bid_quantity(10000), 300);
}

TEST(OrderBookTest, DeleteOrder)
{
    OrderBook book;

    book.apply({
        MarketDataEventType::Add,
        1001,
        0,
        Side::Buy,
        10000,
        500
    });

    book.apply({
        MarketDataEventType::Delete,
        1001,
        0,
        Side::Buy,
        10000,
        0
    });

    EXPECT_EQ(book.bid_quantity(10000), 0);
    EXPECT_EQ(book.best_bid(), 0);
}

TEST(OrderBookTest, MultipleOrdersAtSamePrice)
{
    OrderBook book;

    book.apply({
        MarketDataEventType::Add,
        1001,
        0,
        Side::Buy,
        10000,
        500
    });

    book.apply({
        MarketDataEventType::Add,
        1002,
        0,
        Side::Buy,
        10000,
        200
    });

    EXPECT_EQ(book.bid_quantity(10000), 700);

    book.apply({
        MarketDataEventType::Execute,
        1001,
        0,
        Side::Buy,
        10000,
        300
    });

    EXPECT_EQ(book.bid_quantity(10000), 400);
}

TEST(OrderBookTest, ReplaceOrder)
{
    OrderBook book;

    book.apply({
        MarketDataEventType::Add,
        1001,
        0,
        Side::Buy,
        10000,
        500
    });

    book.apply({
        MarketDataEventType::Replace,
        1001,
        1005,
        Side::Buy,
        10001,
        300
    });

    EXPECT_EQ(book.bid_quantity(10000), 0);
    EXPECT_EQ(book.bid_quantity(10001), 300);
    EXPECT_EQ(book.best_bid(), 10001);
}