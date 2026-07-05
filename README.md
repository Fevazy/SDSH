### **WARNING: VERY VERY WORK IN PROGRESS.**
API is unstable, algorithms substitute each other, performance may vary etc., etc.
Do **NOT** use in your projects if you're not ready for massive refactoring.

## DAS

Das ist DAS. Das DAS ist das Deterministisch Aktion Scheduler, DAS.

(This is DAS. The DAS is the Deterministic Action Scheduler, DAS.)

General concept is to make pools for objects, every tick scan them, write
actions to perform on them and at phase two apply these actions. All that may
be slow and random, so this thing is gonna do it...
- a) multithreaded
- b) mostly lock-free
- c) over C API
- d) sequentially within a tick (you define order of updates)
- e) deterministically* &lt;= this asterisk is VERY important

Why/how [abcde]? Because of...
- a,b) 
    - Why: linearly faster, most production-grade engines don't use much cores
        while hardware they run on can provide this opportunity.
    - How: !(W&&R), or simpler - W^R. This driver will use two-phase
        tick update: first we select objects to act on using only reads,
        then switch to second phase and perform actions.
- c)
    - Why: cross-language support (PL without C interop is probably dead PL),
        and because core is written in C.
    - How: entire library is written in C, so it has native C API
- d)
    - Why: critical in terms of determinism. Deterministic engine must
        always perform A either before or after B, but this behaviour mustn't
        change between startups and even more so between tick updates
    - How: priorities.
- e)
    - Why: "works on my machine", huh? So, instead of Docker and VMs just use
        deterministic backend
    - How: ask Kovarex, www.factorio.com

This thing may be used for:
- Physics/game engines,
- simulations with many objects and complex logic,
- and everything you'll want it to work for. Just understand how it works
    and use as you wish, that's what "open source" means


