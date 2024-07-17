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

### `rocksdb`
Cloned rocksdb repository. 