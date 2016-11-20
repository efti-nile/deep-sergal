#!/usr/bin/env sh
# Create the imagenet lmdb inputs
# N.B. set the path to the imagenet train + val data dirs
set -e

# Folder for output folders "sketches_lmdb" and "lines_lmdb" with generated lmdb databases
EXAMPLE=./
# Folder with "sketches-train.txt" and "lines-train.txt" files containing input images list
DATA=data
# Folder with tools
TOOLS=tools

TRAIN_DATA_ROOT=/home/cristopher/workspace/deep-sergal/train/sketches/
VAL_DATA_ROOT=/home/cristopher/workspace/deep-sergal/train/lines/

rm -rf $EXAMPLE/sketches_lmdb
rm -rf $EXAMPLE/lines_lmdb

if [ ! -d "$TRAIN_DATA_ROOT" ]; then
  echo "Error: TRAIN_DATA_ROOT is not a path to a directory: $TRAIN_DATA_ROOT"
  echo "Set the TRAIN_DATA_ROOT variable in create_imagenet.sh to the path" \
       "where the ImageNet training data is stored."
  exit 1
fi

if [ ! -d "$VAL_DATA_ROOT" ]; then
  echo "Error: VAL_DATA_ROOT is not a path to a directory: $VAL_DATA_ROOT"
  echo "Set the VAL_DATA_ROOT variable in create_imagenet.sh to the path" \
       "where the ImageNet validation data is stored."
  exit 1
fi

echo "Creating train lmdb..."

GLOG_logtostderr=1 $TOOLS/convert_imageset --gray=True \
    $TRAIN_DATA_ROOT \
    $DATA/sketches-train.txt \
    $EXAMPLE/sketches_lmdb

echo "Creating val lmdb..."

GLOG_logtostderr=1 $TOOLS/convert_imageset --gray=True \
    $VAL_DATA_ROOT \
    $DATA/lines-train.txt \
    $EXAMPLE/lines_lmdb

echo "Done."
