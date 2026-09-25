#!/usr/bin/env bash
set -e

mkdir -p build
g++ -std=c++17 -Wall -Wextra -Wpedantic -O2 \
    src/main.cpp src/calculator.cpp \
    -o build/calculator

echo "Build complete: build/calculator"
