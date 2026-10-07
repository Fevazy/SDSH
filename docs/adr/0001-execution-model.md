# ADR-0001
---
date: 2026-10-07
status: accepted, pending
---

> TL;DR: moving from two phases and AoS with per-entity callbacks to flexible
> more ECS-like design - entities by ID and archetypes, systems as state
> mutation mechanism and per-component SoA memory layout, but still with
> command buffers.

## Context

SDSH must guarantee understandable, deterministic ticks that get data only from
previous ticks by design. Original model guaranteed that by routing ***all***
mutations through a command buffers, then applying in second phase. That
enforces threads to pass over the same data at least twice.

AoS was considered as better practice since every object was handled
independently, so callbacks that read and write only to affected object, had
minimal cache misses, but cross-entity interactions also happen very often,
and cache locality is useless here since it's imposiible to predict which
entity reads from and writes to without analyzing callback code, but it's very
hard to algorithmically analyze hot paths on static code and make no mistakes.

Also, command buffer was planned as global bucketed per-entity and per-priority
lock-free structure. New architecture includes per-component command buffer
stored in-place or in range of L2 cache reachability, so cache friendliness
grows a lot.

We still have to satisfy determinism, so to guarantee system A sees only data
that system A haven't affected yet (ex. reading from entity that is already
handled by A with another thread), we keep command buffers here, so write to
entity's component is now cached until system A affected all entities in pools,
then purged.

## Decision

Combined system: command buffers for cross-entity RW systems to 

## Consequences

+ Better SIMD support
+ Better cache locality
- Cross-entity RW systems must be treated as pure functions within the bounds
  of the system appliance
