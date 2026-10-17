### **WARNING: VERY VERY WORK IN PROGRESS.**
API is unstable, algorithms substitute each other, performance may vary etc., etc.
Do **NOT** use in your projects if you're not ready for massive refactoring.

## SDSH

SDSH stands for Sharded Deterministic State Handler.

### What's this?

General concept is to make pools for objects, every tick scan them, write
actions to perform on them and at phase two apply these actions. All that may
be slow and random, so this thing is gonna do it...
- a) multithreaded and lock-free
- b) cache-aware
- c) over C API
- d) sequentially within a tick (you define order of updates)
- e) deterministically* &lt;= this asterisk is VERY important

Why/how &lt;abcde&gt;? 
- a) 
  - Why: linearly faster, most production-grade engines don't use much cores
    while hardware they run on could provide this opportunity.
  - How: multithreaded architecture with lock-free structures where it's
    possible. 
- b)
  - Why: Faster, a lot. For example, on most Zen 4 (AMD microarchitecture)
    implementations read from non-cached DRAM has latency about 300-400 CPU
    cycles, while read from L3 (layer-3, biggest) cache costs 50* cycles, L2
    cache hit has latency of 14* cycles and L1D (Layer-1-Data) hit worths 4-5*
    cycles. Assuming 5.0 GHz clock, that's 60-80, 10, 2.8 and 0.95 nanoseconds
    of latency.
    *all cycle counts may vary between CPU models, motherboards and
    implementations, but scale is always pretty same.
- c)
  - Why: cross-language support (PL without C interop is probably dead PL),
    and because core is written in C.
  - How: entire library is written in C, so it has native C API.
- d)
  - Why: critical in terms of determinism. Deterministic engine must
    always perform A either before or after B, but this behaviour mustn't
    change between startups and even more so between tick updates.
  - How: user-defined call graph that describes which systems sees what.
- e)
  - Why: "works on my machine", huh? So, instead of Docker and VMs just use
    deterministic backend.
  - How: ask Kovarex and team, www.factorio.com.

### About asterisk

Driver calls user provided callbacks, so if they rely on external I/O driver
can't provide determinism at all. Also, use programmatically-defined formulas
to aproximate float/double trigonometry since hardware-defined variants
can vary between architectures, implementations etc. etc.

### Usage

This thing may be used for:
- Physics/game engines,
- simulations with many objects and complex logic,
- and everything you'll want it to work for. Just understand how it works
  and use as you wish, that's what "open source" means and what Apache 2.0 is
  for.

### News

We're moving to ECS-like layout, but determinism is still preferred. Command
buffers will be implemented as intended, but most per-entity data mutations now
will write in-place in one phase. So, now different systems can run in one
phase if they don't write or read other entities' data, or in two phases, if
they do so. This gives more flexibility, cache friendliness and lets you pass
same data once instead of twice.
