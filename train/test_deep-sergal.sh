#!/usr/bin/env sh
set -e

tput reset

./tools/caffe test --model=deep-sergal_solver.prototxt --weights=snapshots/deep-sergal_iter_100.caffemodel --gpu=all$@
