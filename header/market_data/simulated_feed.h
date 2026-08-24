#pragma once

#include <cstddef>
#include <vector>

#include "market_data/feed_handler.h"

class SimulatedFeed : public FeedHandler
{
public:
    SimulatedFeed();

    bool next_event(MarketDataEvent& event) override;

private:
    std::vector<MarketDataEvent> events_;

    std::size_t current_index_;
};