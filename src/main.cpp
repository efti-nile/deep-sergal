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
	const string trained_file("train/snapshots/deep-sergal_iter_20000.caffemodel");
	DeepSergal ds(model_file, trained_file);
	int i = 1;
	while(i){
		ds.ProcessRandomImageFromTrainingDB("sketch.png", "line.png", "out.png");
		cin >> i;
	}
	return 0;
}

