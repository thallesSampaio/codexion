*This project has been created as part of the 42 curriculum by thasampa.*

# Codexion

## Description

**Codexion** Codexion is a concurrency simulation written in C using POSIX threads.

The project models multiple coders sitting in a circular shared workspace. Each coder is represented by a thread and needs two neighboring USB dongles in order to compile.

After compiling, a coder goes through debugging and refactoring phases before trying to compile again.

The main goal of the project is to correctly synchronize access to shared resources while preventing deadlocks, starvation, race conditions, and incorrect timing behavior.

The simulation supports two scheduling policies for dongle requests:

- FIFO (First In, First Out)
- EDF (Earliest Deadline First) 

The simulation stops when either:

- one coder burns out because it did not start compiling before its deadline;
- all coders reach the required number of compilations.

## Instructions
Run:  `make ; make clean`
The executable generated is: ./codexion

#### Execution:
The program expects exactly eight arguments:

`./codexion number_of_coders time_to_burnout time_to_compile \
time_to_debug time_to_refactor number_of_compiles_required \
dongle_cooldown scheduler`

<strong>Example:<strong/>
`./codexion 5 800 200 200 100 3 50 fifo`

## Resources
- LunnaBoo codexion guide: https://github.com/LunnaBoo/42_Codexion/wiki
- Dining Philosophers problem
- Deadlock and Coffman conditions
- pthread manual pages

## AI Usage
They were mainly used for:

- understanding the project subject;
- reviewing concurrency concepts;
- discussing project architecture;
- identifying possible race conditions and deadlock situations;
- reviewing parser and heap logic;
- suggesting test cases;
- reviewing synchronization and cleanup logic;

All generated suggestions were reviewed, tested, and adapted before being included in the project.

## Blocking cases handled

- **Deadlock prevention:** dongle mutexes are always locked in a consistent order, preventing circular wait, one of Coffman's deadlock conditions.
- **Starvation prevention:** each dongle uses a heap-based priority queue with FIFO or EDF scheduling.
- **Cooldown handling:** a released dongle can only be reused after `dongle_cooldown` milliseconds.
- **Burnout detection:** a dedicated monitor thread checks `last_compile_start + time_to_burnout` and stops the simulation when a coder misses its deadline.
- **Log serialization:** all output is protected by a logging mutex, preventing mixed messages.
- **Single coder case:** with only one dongle available, the coder cannot compile and eventually burns out.

## Thread synchronization mechanisms

Each coder runs in its own `pthread_t`, while a separate monitor thread checks burnout and completion.

- **Dongle mutexes:** protect dongle usage, cooldown data, and request queues.
- **Coder state mutexes:** protect `last_compile_start` and `compiles_done` from race conditions between coder threads and the monitor.
- **Global state mutex:** protects the simulation stop flag.
- **Logging mutex:** serializes terminal output.
- **Condition variables:** associated with dongles and used to broadcast state changes and wake threads during shutdown.

Coders and the monitor communicate through shared mutex-protected state. For example, a coder updates `last_compile_start` under its state mutex, and the monitor reads the same value under that mutex when checking burnout.