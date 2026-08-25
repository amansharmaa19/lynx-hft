#include <gtest/gtest.h>

#include "order_book/price_level.h"

TEST(PriceLevelTest, AddsOrdersInFIFOOrder)
{
    PriceLevel level;

    level.add_order({
        1001,
        Side::Buy,
        10000,
        500
    });

    level.add_order({
        1002,
        Side::Buy,
        10000,
        200
    });

    ASSERT_EQ(level.orders().size(), 2);

    auto it = level.orders().begin();

    EXPECT_EQ(it->order_id, 1001);
    EXPECT_EQ(it->quantity, 500);

    ++it;

    EXPECT_EQ(it->order_id, 1002);
    EXPECT_EQ(it->quantity, 200);

    EXPECT_EQ(level.total_quantity(), 700);
}

TEST(PriceLevelTest, ReducesOrderQuantity)
{
    PriceLevel level;

    level.add_order({
        1001,
        Side::Buy,
        10000,
        500
    });

    EXPECT_TRUE(
        level.reduce_order_quantity(1001, 200));

    const Order* order = level.find_order(1001);

    ASSERT_NE(order, nullptr);

    EXPECT_EQ(order->quantity, 300);
    EXPECT_EQ(level.total_quantity(), 300);
}

TEST(PriceLevelTest, RemovesOrderWhenFullyExecuted)
{
    PriceLevel level;

    level.add_order({
        1001,
        Side::Buy,
        10000,
        500
    });

    EXPECT_TRUE(
        level.reduce_order_quantity(1001, 500));

    EXPECT_EQ(level.find_order(1001), nullptr);
    EXPECT_EQ(level.total_quantity(), 0);
    EXPECT_TRUE(level.empty());
}

TEST(PriceLevelTest, CannotReduceUnknownOrder)
{
    PriceLevel level;

    EXPECT_FALSE(
        level.reduce_order_quantity(9999, 100));
}

TEST(PriceLevelTest, PartialExecutionPreservesFIFOOrder)
{
    PriceLevel level;

    level.add_order({
        1001,
        Side::Buy,
        10000,
        500
    });

    level.add_order({
        1002,
        Side::Buy,
        10000,
        300
    });

    level.add_order({
        1003,
        Side::Buy,
        10000,
        200
    });

    // Fully execute the first order.
    EXPECT_TRUE(
        level.reduce_order_quantity(1001, 500));

    // First order should be gone.
    ASSERT_EQ(level.orders().size(), 2);

    auto it = level.orders().begin();

    // Second order should now be first.
    EXPECT_EQ(it->order_id, 1002);
    EXPECT_EQ(it->quantity, 300);

    ++it;

    // Third order remains behind it.
    EXPECT_EQ(it->order_id, 1003);
    EXPECT_EQ(it->quantity, 200);

    EXPECT_EQ(level.total_quantity(), 500);
}

TEST(PriceLevelTest, PartialExecutionPreservesTimePriority)
{
    PriceLevel level;

    level.add_order({
        1001,
        Side::Buy,
        10000,
        500
    });

    level.add_order({
        1002,
        Side::Buy,
        10000,
        300
    });

    level.add_order({
        1003,
        Side::Buy,
        10000,
        200
    });

    // Partially execute the first order.
    EXPECT_TRUE(
        level.reduce_order_quantity(1001, 200));

    ASSERT_EQ(level.orders().size(), 3);

    auto it = level.orders().begin();

    // Order 1001 must remain first.
    EXPECT_EQ(it->order_id, 1001);
    EXPECT_EQ(it->quantity, 300);

    ++it;

    EXPECT_EQ(it->order_id, 1002);
    EXPECT_EQ(it->quantity, 300);

    ++it;

    EXPECT_EQ(it->order_id, 1003);
    EXPECT_EQ(it->quantity, 200);

    EXPECT_EQ(level.total_quantity(), 800);
}