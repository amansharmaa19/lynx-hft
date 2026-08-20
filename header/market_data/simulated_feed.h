#pragma once

#include <vector>
#include <cstddef>

#include "market_data/feed_handler.h"

class SimulatedFeed : public FeedHandler
{
public:
    SimulatedFeed();

    bool next_update(MarketDataUpdate& update) override;

private:
    std::vector<MarketDataUpdate> updates_;
    std::size_t current_index_;
};