#!/bin/sh
set -eu

build_dir="/workspace/build/podman/cmake"
build_type="${BUILD_TYPE:-Release}"
jobs="${JOBS:-$(nproc)}"

emcmake cmake \
    -S /workspace \
    -B "$build_dir" \
    -DCMAKE_BUILD_TYPE="$build_type" \
    -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=/workspace/build/podman

cmake --build "$build_dir" --parallel "$jobs"

printf '\nWebAssembly build complete. Files are in /workspace/build/podman.\n'
