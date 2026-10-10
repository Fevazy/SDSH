# ADR-0001. Runtime model

**Date:** 2026-10-07

**Status:** accepted, pending

---

> TL;DR: Replace the two-phase AoS model, global command buffer and per-entity
> callbacks with an ECS-like chunked AoSoA and chunk-local cache-aware buffers.
> Determinism comes from systems' call dependencies. Chosen: A2.

## Context

SDSH, by design, must guarantee understandable data flow and deterministic ticks
that consume only the data that has been handled by all calls it was intended to
be handled by. The original model guaranteed this by routing *all* mutations
through global bucketed lock-free command buffer, so that callbacks read first,
then their commands get applied. This caused some problems as cache-unfriendly
behaviour in both phases due to misses between reads from command buffers and
the application of the commands if the offset between processed entity and the
command buffer is bigger than L2. In contrast, AoS was considered as a better
way to deal with cache, since all callbacks worked on one entity at one time,
therefore probably wouldn't produce massive cache misses - on the contrary,
would hit the cache in every interaction.

## Considered alternatives

### A1. AoS with chunk-local command buffers

Move command buffers closer to the object that this command buffer belongs to
and make them with entities fit into L2 cache-sized chunks so no cache miss
happens between reading from command buffer and writing to the entity.

### A2. ECS with chunk-local command buffers

Use ECS-like layout: store components of archetypes as SoA. If we target
multithreading (what SDSH actually does), we still have to provide determinism,
so command buffers are necessary to keep unprocessed data available to read and
store new values to write them later. As in A1, we should keep command buffers
local to provide cache-friendliness, which is also required.

## Consequences

### A1. AoS with chunk-local command buffers
- `+` Better cache-awareness
- `-` Limited parallelism between independent operations

### A2. ECS with chunk-local command buffers
- `+` Better cache-awareness
- `+` More flexibility in operation ordering within a single tick - system
  can be ordered before or after another one.
- `+` Independent systems can run in parallel threads
- `-` More complex criteria to satisfy to provide determinism (dependency DAG,
  system ordering, thread scheduling)

## Decision

A2 is chosen due to better performance ceiling provided by better parallelism
capabilities. A1 caps parallelism between independent systems, which actually is
important. A2 can parallelize that by analyzing systems' call DAG.  Complex
algorithms are acceptable if they get implemented after MVP as performance
enhancement.
