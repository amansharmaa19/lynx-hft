#include "market_data/simulated_feed.h"

SimulatedFeed::SimulatedFeed()
    : updates_{
          {Side::Buy, 10000, 500},
          {Side::Buy, 9999, 300},
          {Side::Sell, 10002, 400},
          {Side::Sell, 10003, 600},
          {Side::Sell, 10001, 200},
      },
      current_index_(0)
{
}

bool SimulatedFeed::next_update(MarketDataUpdate& update)
{
    if (current_index_ >= updates_.size())
    {
        return false;
    }

    update = updates_[current_index_++];

    return true;
}