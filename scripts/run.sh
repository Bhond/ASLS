#!/bin/sh

# Remove build folder
rm -rf ../build

# Rebuild all package
mkdir ../build && cd ../build
cmake ..

# Compile
cmake --build .