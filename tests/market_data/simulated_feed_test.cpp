#include <gtest/gtest.h>

#include "market_data/simulated_feed.h"

TEST(SimulatedFeedTest, ProducesEvents)
{
    SimulatedFeed feed;

    MarketDataEvent event;

    EXPECT_TRUE(feed.next_event(event));

    EXPECT_EQ(event.type, MarketDataEventType::Add);
    EXPECT_EQ(event.order_id, 1001);
    EXPECT_EQ(event.side, Side::Buy);
    EXPECT_EQ(event.price, 10000);
    EXPECT_EQ(event.quantity, 500);
}

TEST(SimulatedFeedTest, EventuallyEnds)
{
    SimulatedFeed feed;

    MarketDataEvent event;

    int count = 0;

    while (feed.next_event(event))
    {
        ++count;
    }

    EXPECT_EQ(count, 5);

    EXPECT_FALSE(feed.next_event(event));
}