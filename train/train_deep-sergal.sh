#!/usr/bin/env sh
set -e

tput reset

./tools/caffe train --solver=deep-sergal_solver.prototxt $@
