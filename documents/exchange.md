The exchange is basically a giant matching machine
                    EXCHANGE
                       │
          ┌────────────┴────────────┐
          │                         │
       BUY ORDERS               SELL ORDERS
          │                         │
          ▼                         ▼
       BID BOOK                  ASK BOOK
          │                         │
          └────────────┬────────────┘
                       │
                       ▼
                MATCHING ENGINE
                       │
                       ▼
                    TRADES


People send orders to the exchange.

The exchange maintains the order book.

When compatible buy and sell orders exist, the matching engine executes a trade.

That matching engine is one of the things we're going to build.


"I have 8 years of systems/C++ experience. I independently built a low-latency electronic trading platform, implemented market-data ingestion and L2 order-book reconstruction, developed a matching engine and market-making simulator, built market replay/backtesting, and profiled the system down to cache/CPU/network behavior."