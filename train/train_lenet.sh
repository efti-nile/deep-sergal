#!/usr/bin/env sh
set -e

./tools/caffe train --solver=lenet_solver.prototxt $@
