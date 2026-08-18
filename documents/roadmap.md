Now that you understand the mechanics, our roadmap becomes:

Phase 1 — Exchange mechanics
Order
PriceLevel
OrderBook
MatchingEngine


Phase 2 — Market data
WebSocket
   ↓
Parser
   ↓
Snapshot
   ↓
Incremental updates
   ↓
OrderBook


Phase 3 — Strategy
Spread
Mid price
Imbalance
Order flow
Inventory


Phase 4 — Execution
Order Manager
Limit orders
Market orders
Cancel
Modify
Partial fills


Phase 5 — Backtesting
Recorded feed
      ↓
Market replay
      ↓
Strategy
      ↓
Simulated fills
      ↓
P&L


Phase 6 — Performance
Benchmark
    ↓
perf
    ↓
Cache analysis
    ↓
Memory optimization
    ↓
Lock-free
    ↓
CPU affinity
    ↓
Networking


Phase 7 — Advanced
Kernel bypass
DPDK
Multicast
FPGA concepts
CUDA