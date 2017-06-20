#!/bin/bash

set -e

dirname=$(dirname "${BASH_SOURCE[0]}")
dirname=$(cd "$dirname" && pwd)

builddir="$dirname/../build"

cd "$builddir"
cmake ..
make
make test
