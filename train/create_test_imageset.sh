#!/usr/bin/env sh
# Create the imagenet lmdb inputs
# N.B. set the path to the imagenet train + val data dirs
set -e

# Folder for output folder "sketches-test_lmdb"
EXAMPLE=.
# Folder with "sketches-test.txt"
DATA=data
# Folder with tools
TOOLS=tools

TEST_DATA_ROOT=/home/cristopher/workspace/deep-sergal/train/sketches-test/

rm -rf $EXAMPLE/sketches-test_lmdb

echo "Creating test lmdb..."

GLOG_logtostderr=1 $TOOLS/convert_imageset --gray=True \
    $TEST_DATA_ROOT \
    $DATA/sketches-test.txt \
    $EXAMPLE/sketches-test_lmdb

echo "Done."
