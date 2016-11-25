//============================================================================
// Name        : main.cpp
// Author      : efti-nile
// Version     :
// Copyright   : WTFPL
// Description :
//============================================================================

# include "main.hpp"

using namespace std;

/*
 * -train model_file [pretrained_file]
 *
 */

int main(int argc, char *argv[]) {
	::google::InitGoogleLogging(argv[0]);
	if(argc > 1){
		if(strcmp(argv[1], "-train") == 0){
			exec("train/train_deep-sergal.sh");
		}
	}

	const string model_file("train/deep-sergal.prototxt");
	const string trained_file("train/snapshots/deep-sergal_iter_615.caffemodel");
	DeepSergal ds(model_file, trained_file);
	ds.SaveParamsToImage("kernels");

	/*int i = 1;
	while(i){
		ds.ProcessRandomImageFromTrainingDB("sketch.png", "line.png", "out.png");
		cin >> i;
	}*/

	/*for(int i = 0; i < 20; ++i){
		stringstream ss;
		ss << i;
		ds.ProcessRandomImageFromTrainingDB("sketch-"+ss.str()+".png", \
				"line-"+ss.str()+".png", "out-"+ss.str()+".png");
	}*/


	return 0;
}

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}
