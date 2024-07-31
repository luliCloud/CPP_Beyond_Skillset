# Outline of this RocksDB directory

## Introduction
This directory contains the implementation of each key concept in RocksDB, like SSTable, Bloom Filter, LSMTree, etc. It also contains basic usage of RocksDb in C++ projects and how to install the RocksDb in Ubuntu env. Please the detailed introduction of each file below:

### `install_rocksdb.sh`
How to install the rocksdb in the Unix-like system

### `write_read_rocks_simple_case1.cpp`
Demonstration of how to include Rocksdb in the project file, open, read and write database using Rocksdb's API

### `LSMtree.cpp`
Implementation of basic structure and simple API (flushLevel0, add, search) of LSMtree

### `SSTable.cpp`
Implementation of base SSTable (insert, search) and structure(data block, index for datablocks).

### `Bloom filter`
Implementation of Bloom filter, including the hash function using std lib, bitset that is the inner structure of bloom filter, and insert/search key inside bloom filter. 

### `compact_and_cache.cpp`
A simple example of compress data, store compressed data with key in cache, find kv in cache using key and decompressing data to the original one. 

### `mvcc.cpp (multiple-version concurrency control)`
Simple case to understand a key may corresponds to several keys. Each key correspond to a version num.

### `immutable_memtable.cpp`
The MemTable will be converted to immutable MemTable and flush to disk when the size reach a threshold. As a simple case, we labeled the old MemTable as immutable and it cannot be written anymore.

### `pointLookup_rangeLookup.cpp`
No matter point loop up or range loop up (the key falls into a range [key1, key2]), we always start the search in MemTable then SSTable

### `optimistic_lock.cpp`
Optimistic lock generally used to less-frequent read scenario. We implement it using atomic template with inner functions and compare_exchange_weak function.

### `read_write_process_isolate.cpp`
Isolating the write and read request (avoid mutex competition) using mutex and conditional variable, thread, and lambda for thread constructor"

### `thread_pool.cpp`
Thread pool using mutex, conditional variable, wait, thread, function. When the thread pool is originally created, all threads inside just wait, until the tasks queue has task being pushed. 

### `WAL.cpp`
Define WAL class. Write operation to WAL and replay the WAL after crash.

### `rockslib_persistence_config.cpp`
Using rocksdb lib to set persistence config such as forbid WAL, compression (not working yet)

### `performance_base_test.cpp`
Using chrono and thread to mimic the time cost of operation in database. Testing the real performance of db ope.

### `rocksdb`
Cloned rocksdb repository. 
