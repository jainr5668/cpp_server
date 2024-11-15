#!/bin/sh
set -e

# Create build directory if it doesn't exist
mkdir -p build

# Go to build directory
cd build

# Run cmake if CMakeCache.txt doesn't exist
if [ ! -f CMakeCache.txt ]; then
    cmake ..
fi

# Build the project
make

# Run the server
./server

# Keep container running if server exits
exec "$@"