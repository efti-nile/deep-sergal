/*
 * DeepSergal.hpp
 *
 *  Created on: Nov 18, 2016
 *      Author: efti-nile
 */

#ifndef DEEPSERGAL_HPP_
#define DEEPSERGAL_HPP_

#include <iostream>
#include <caffe/caffe.hpp>
#ifdef USE_OPENCV
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#endif  // USE_OPENCV
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>

using namespace caffe;
using std::string;

class DeepSergal {
public:
	DeepSergal(const string& model_file, const string& trained_file);
	virtual ~DeepSergal();
	int ProcessImage(const string& input_image, const string& output_image);
private:
	shared_ptr<Net<float> > net_;
	cv::Size input_geometry_;
};

#endif /* DEEPSERGAL_HPP_ */
