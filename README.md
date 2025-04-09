# MiniDb - A Minimal Storage Engine Implementation in C++
A lightweight key-value storage engine that simulates low-level storage engine internals:
- Custom binary page format
- Disk paging with a paper
- In-memory indexing
- Persistent `GET/PUT` operations

## Features
- Fixed-size pages (4KB)
- Binary on-disk format
- In-memory index for fast lookups
- Unit-tested with Google Test
- Easy to extend with WAL, concurrency, or SQL support (future implementation considerations)

## Build The Program

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

## Run The Program

After having built the application, run this command:
```bash
./minidb
```

## Sample Usage

```bash
> PUT 42 hello
> PUT 100 world
> GET 42
hello
> SCAN
42: hello
100: world
```




