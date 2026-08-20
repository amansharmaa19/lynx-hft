#include <gtest/gtest.h>

#include "market_data/simulated_feed.h"

TEST(SimulatedFeedTest, ProducesUpdates)
{
    SimulatedFeed feed;

    MarketDataUpdate update;

    EXPECT_TRUE(feed.next_update(update));

    EXPECT_EQ(update.side, Side::Buy);
    EXPECT_EQ(update.price, 10000);
    EXPECT_EQ(update.quantity, 500);
}

TEST(SimulatedFeedTest, EventuallyEnds)
{
    SimulatedFeed feed;

    MarketDataUpdate update;

    int count = 0;

    while (feed.next_update(update))
    {
        ++count;
    }

    EXPECT_EQ(count, 5);
}