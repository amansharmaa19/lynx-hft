#include "market_data/simulated_feed.h"

SimulatedFeed::SimulatedFeed()
    : events_{
          {
              MarketDataEventType::Add,
              1001,
              0,
              Side::Buy,
              10000,
              500
          },
          {
              MarketDataEventType::Add,
              1002,
              0,
              Side::Buy,
              9999,
              300
          },
          {
              MarketDataEventType::Add,
              2001,
              0,
              Side::Sell,
              10002,
              400
          },
          {
              MarketDataEventType::Add,
              2002,
              0,
              Side::Sell,
              10003,
              600
          },
          {
              MarketDataEventType::Add,
              2003,
              0,
              Side::Sell,
              10001,
              200
          },
      },
      current_index_(0)
{
}

bool SimulatedFeed::next_event(MarketDataEvent& event)
{
    if (current_index_ >= events_.size())
    {
        return false;
    }

    event = events_[current_index_++];

    return true;
}