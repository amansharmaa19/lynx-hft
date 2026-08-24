#pragma once

#include "market_data/market_data_event.h"

class FeedHandler
{
public:
    virtual ~FeedHandler() = default;

    virtual bool next_event(MarketDataEvent& event) = 0;
};