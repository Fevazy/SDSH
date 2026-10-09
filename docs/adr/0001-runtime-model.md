# ADR-XXXX. ADR name

---
date: 2026-10-07

status: accepted, pending
---
:

> TL;DR: Replace the two-phase AoS model with global command buffer and
> per-entity callbacks with an ECS-like chunked AoSoA. Determinism over
> systems' call dependencies.

## Context

SDSH, by design, must guarantee understandable data flow and deterministic
ticks that consume only the data that has been handled by all calls it was
intended to be handled by. The original model guaranteed this by routing *all*
mutations through global bucketed lock-free command buffer, so that callbacks
read first, then their commands get applied. This caused some problems as
cache-unfriendly behaviour in both phases due to misses between reads from
command buffers and the application of the commands if offset between
processed entity and command buffer is bigger than L2. In the opposite, AoS
was considered as better way to deal with cache, since all callbacks worked on
one entity at one time, therefore probably wouldn't produce massive cache
misses - in the contrary, would hit the cache in every interaction. 

## Considered alternatives

### A1. Alternative 1

Description for alternative 1.

### A2. Alternative 2

Description for alternative 2.

## Consequences

### A1. Alternative 1:
- `+` What's better
- `-` What's worse
- `*` Important note

### A2. Alternative 2:
- `+` What's better
- `-` What's worse
- `*` Important note

## Decision

State what you've chosen, and why.

## References

- Benchmark: [name of bench](https://example.com)
- Research: [name of research](https://example.com)

## Delete this line and all below in final ADR
status must be one of:
    proposed
    accepted, pending
    accepted, partial
    accepted, complete
    superseded by ADR-XXXX
    rejected
    deprecated

Reference benchmarks, tests and manuals while writing consequences and
decision sections.
