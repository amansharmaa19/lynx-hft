#pragma once

#include <cstdint>

#include "common/side.h"
#include "common/types.h"

struct Order
{
    std::uint64_t order_id;
    Side side;
    Price price;
    Quantity quantity;
};
