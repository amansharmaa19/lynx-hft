#pragma once

#include "common/side.h"
#include "order_book/order_book.h"

struct MarketDataUpdate
{
    Side side;
    Price price;
    Quantity quantity;
};