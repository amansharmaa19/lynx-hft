#pragma once

#include "market_data/market_data_update.h"

class FeedHandler
{
public:
    virtual ~FeedHandler() = default;
    virtual bool next_update(MarketDataUpdate& update) = 0;
};