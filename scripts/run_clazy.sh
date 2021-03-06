#!/usr/bin/env bash

set -Eeuo pipefail
IFS=$'\n\t'

# Go to project directory
cd "$(dirname "${BASH_SOURCE[0]}")/.." > /dev/null 2>&1

source scripts/utils.sh

print_important "Building with clazy"
print_info "Tip: you can specify the clang version by using"
print_info "     'export CLANGXX=clang++-9.0;''"
print_info ""

mkdir -p build/clazy
cd build/clazy

print_info "clazy build dir: $(pwd)"

# level3 will be introduced in Clazy 1.7
export CLAZY_CHECKS="level2,tr-non-literal,qhash-with-char-pointer-key,reserve-candidates,signal-with-return-value,thread-with-slots,unneeded-cast,no-qstring-allocations,no-clazy-range-loop"

print_info "Run clazy checks: ${CLAZY_CHECKS}"

cmake -DCMAKE_BUILD_TYPE=Debug \
	-DCMAKE_C_COMPILER=clang \
	-DCMAKE_CXX_COMPILER=clazy \
	-DENABLE_COLOR_OUTPUT=ON \
	-GNinja \
	../..

ninja

print_success "Finished"
