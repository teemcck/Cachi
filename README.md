# Cachi: a Multilevel Processor Cache Simulator

Cachi is a cache simulator written in C. It supports configurable cache
hierarchies and includes cache access and replacement policy code. A parser for
Valgrind Lackey memory traces is also available in the source, though the
command-line program does not yet connect trace parsing to hierarchy access.

## Build

From the project root, run:

```sh
make
```

This creates the `cache-simulator` executable.

## Run

Pass a cache hierarchy configuration file:

```sh
./cache-simulator tests/configs/example.cfg
```

The current command-line program loads the configuration and creates the cache
hierarchy. Trace-driven simulation is not yet wired into `main`.

## Configuration format

The configuration file defines one section per cache level. Capacity and block
size are in bytes; associativity is the number of ways per set.

```ini
[L1]
capacity = 32768
block_size = 64
associativity = 8
replacement = LRU
```

Supported replacement names are `LRU`, `FIFO`, `MRU`, and `RR` (random).

## Memory trace format

The trace parser accepts Valgrind Lackey records in the form
`operation address,size`, such as `L 7ff00000,8`. `L` is a read, `S` is a
write, `M` is treated as a read followed by a write, and `I` is ignored.

## Clean generated executables

```sh
make clean
```
