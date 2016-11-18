//============================================================================
// Name        : main.cpp
// Author      : efti-nile
// Version     :
// Copyright   : WTFPL
// Description :
//============================================================================

# include "main.hpp"

using namespace std;

int main(int argc, char *argv[]) {
	::google::InitGoogleLogging(argv[0]);
	const string model_file("train/deep-sergal.prototxt");
	const string trained_file("train/deep-sergal_iter_500.caffemodel");
	const string input_image("train/sketches/sketch-0001.png");
	const string output_image("src/out/out-0001.png");
	DeepSergal ds(model_file, trained_file);
	ds.ProcessImage(input_image, output_image);
	return 0;
}

