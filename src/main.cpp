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
	const string model_file("src/model/deploy.prototxt");
	const string input_image("src/train/train-0001.png");
	const string output_image("src/out/out-0001.png");
	DeepSergal ds(model_file);
	ds.ProcessImage(input_image, output_image);
	return 0;
}

