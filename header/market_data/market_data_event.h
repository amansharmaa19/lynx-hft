#pragma once

#include <cstdint>

#include "common/side.h"
#include "common/types.h"

enum class MarketDataEventType
{
    Add,
    Execute,
    Cancel,
    Delete,
    Replace
};

struct MarketDataEvent
{
    MarketDataEventType type;

    std::uint64_t order_id;

    std::uint64_t new_order_id;

    Side side;

    Price price;

    Quantity quantity;
};