#!/bin/bash

# Update package list
sudo apt update

# Install dependencies
sudo apt install -y build-essential cmake libsnappy-dev zlib1g-dev libbz2-dev libgflags-dev liblz4-dev libzstd-dev

# Clone RocksDB repository
git clone https://github.com/facebook/rocksdb.git
cd rocksdb

# Build RocksDB
mkdir build && cd build
cmake ..
make -j$(nproc)
sudo make install

echo "RocksDB installation complete."

# run this sh under the working dir you will run your script. otherwise defined the 
# searching pathway when compile for include (header files) and lib files
# chmod 667 install_rocskdb.sh
# sudo ./install_rocksdb.sh