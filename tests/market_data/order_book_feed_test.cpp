#include <gtest/gtest.h>

#include "market_data/simulated_feed.h"
#include "order_book/order_book.h"

TEST(MarketDataPipelineTest, SimulatedFeedBuildsOrderBook)
{
    SimulatedFeed feed;
    OrderBook book;

    MarketDataEvent event;

    while (feed.next_event(event))
    {
        book.apply(event);
    }

    EXPECT_EQ(book.best_bid(), 10000);
    EXPECT_EQ(book.best_ask(), 10001);

    EXPECT_EQ(book.bid_quantity(10000), 500);
    EXPECT_EQ(book.bid_quantity(9999), 300);

    EXPECT_EQ(book.ask_quantity(10001), 200);
    EXPECT_EQ(book.ask_quantity(10002), 400);
    EXPECT_EQ(book.ask_quantity(10003), 600);

    EXPECT_EQ(book.spread(), 1);
    EXPECT_EQ(book.mid_price(), 10000);
}

TEST(MarketDataPipelineTest, ReplayUpdatesBookStateAfterEachEvent)
{
    SimulatedFeed feed;
    OrderBook book;

    MarketDataEvent event;

    ASSERT_TRUE(feed.next_event(event));
    book.apply(event);

    EXPECT_EQ(book.best_bid(), 10000);
    EXPECT_EQ(book.best_ask(), 0);

    ASSERT_TRUE(feed.next_event(event));
    book.apply(event);

    EXPECT_EQ(book.best_bid(), 10000);
    EXPECT_EQ(book.best_ask(), 0);
    EXPECT_EQ(book.spread(), 0);

    ASSERT_TRUE(feed.next_event(event));
    book.apply(event);

    EXPECT_EQ(book.best_bid(), 10000);
    EXPECT_EQ(book.best_ask(), 10002);
    EXPECT_EQ(book.spread(), 2);

    ASSERT_TRUE(feed.next_event(event));
    book.apply(event);

    EXPECT_EQ(book.best_bid(), 10000);
    EXPECT_EQ(book.best_ask(), 10002);
    EXPECT_EQ(book.spread(), 2);

    ASSERT_TRUE(feed.next_event(event));
    book.apply(event);

    EXPECT_EQ(book.best_bid(), 10000);
    EXPECT_EQ(book.best_ask(), 10001);
    EXPECT_EQ(book.spread(), 2);

    EXPECT_FALSE(feed.next_event(event));
}
