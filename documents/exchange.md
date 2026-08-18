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
