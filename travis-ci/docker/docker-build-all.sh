#!/usr/bin/env bash

###########################################################
# Create all docker images and build MediaElch
###########################################################

set -euo pipefail
IFS=$'\n\t'

cd "$(dirname "$(realpath -s "$0")")"

./docker-build-dist.sh ubuntu-16.04
./docker-build-dist.sh ubuntu-18.04
./docker-build-dist.sh ubuntu-19.04
./docker-build-dist.sh opensuse-leap-15
./docker-build-dist.sh opensuse-leap-42.3
./docker-build-dist.sh opensuse-tumbleweed
