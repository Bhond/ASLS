#!/usr/bin/env sh
# Robust build script for ASLS
# Usage:
#   ./scripts/build.sh                # debug build, build/ directory
#   BUILD_DIR=../out/build ./scripts/build.sh
#   BUILD_TYPE=Release ./scripts/build.sh
#   PARALLEL=8 ./scripts/build.sh

set -euo pipefail

# Repo root detection: prefer git top-level if available, otherwise current dir
REPO_ROOT="$(git rev-parse --show-toplevel 2>/dev/null || pwd)"
BUILD_DIR="${BUILD_DIR:-${REPO_ROOT}/build}"
BUILD_TYPE="${BUILD_TYPE:-Debug}"
# Optional override for parallel jobs (otherwise auto-detect)
PARALLEL="${PARALLEL:-}"

printf "Repo root: %s\n" "$REPO_ROOT"
printf "Build dir: %s\n" "$BUILD_DIR"
printf "Build type: %s\n" "$BUILD_TYPE"

# Remove previous build if present
if [ -d "$BUILD_DIR" ]; then
  printf "Removing previous build dir: %s\n" "$BUILD_DIR"
  rm -rf "$BUILD_DIR"
fi

mkdir -p "$BUILD_DIR"

# Configure
cmake -S "$REPO_ROOT" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

# Determine number of parallel jobs
if [ -z "$PARALLEL" ]; then
  # try common ways to detect CPU count (portable)
  if command -v nproc >/dev/null 2>&1; then
    PARALLEL="$(nproc)"
  elif command -v getconf >/dev/null 2>&1; then
    PARALLEL="$(getconf _NPROCESSORS_ONLN 2>/dev/null || true)"
  elif command -v sysctl >/dev/null 2>&1; then
    PARALLEL="$(sysctl -n hw.ncpu 2>/dev/null || true)"
  fi
  # fallback
  PARALLEL="${PARALLEL:-2}"
fi

printf "Building with %s parallel jobs\n" "$PARALLEL"

# Build using modern CMake --parallel argument (requires CMake >= 3.12; you have 3.15)
cmake --build "$BUILD_DIR" --parallel "$PARALLEL"

printf "Build finished. Binaries (if any) are in: %s\n" "$BUILD_DIR"
