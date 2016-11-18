#!/usr/bin/env sh
set -e

./tools/caffe train --solver=deep-sergal_solver.prototxt $@
