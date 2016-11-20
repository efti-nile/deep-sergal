#!/usr/bin/env sh
set -e

tput reset

./tools/caffe time --model=deep-sergal.prototxt --gpu=all --iterations=10 $@
