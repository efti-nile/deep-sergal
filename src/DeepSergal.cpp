/*
 * DeepSergal.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: efti-nile
 */

#include "DeepSergal.hpp"

DeepSergal::DeepSergal(const string& model_file, const string& trained_file){

	Caffe::set_mode(Caffe::GPU);

	net_.reset(new Net<float>(model_file, TEST));
	net_->CopyTrainedLayersFrom(trained_file);

	std::cout << "Number of inputs: " << net_->num_inputs() << std::endl;

	std::cout << "Number of outputs: " << net_->num_outputs() << std::endl;

	for(int i = 0; i < net_->num_outputs(); ++i){
		std::cout << "shape string for net_.output_blobs()[" \
		          << i << "]: " << net_->output_blobs()[i]->shape_string() << std::endl;
	}

	//input_geometry_ = cv::Size(net_->input_blobs()[0]->width(), net_->input_blobs()[0]->height());
	input_geometry_ = cv::Size(100, 100);
}

int DeepSergal::ProcessImage(const string& input_image, const string& output_image) {
	// Read input image to opencv matrix
	cv::Mat img = cv::imread(input_image, CV_LOAD_IMAGE_GRAYSCALE);
	CHECK(!img.empty()) << "Unable to decode image " << input_image;
	// Resize image
	cv::Mat resized_img;
	cv::resize(img, resized_img, input_geometry_);
	// Convert to float
	cv::Mat img_resized_float;
	resized_img.convertTo(img_resized_float, CV_32FC1);
	// Create opencv matrix and map one to the input layer
	//cv::Mat input(input_geometry_, CV_32FC1, (float *)net_->input_blobs()[0]->mutable_cpu_data());
	//input = img_resized_float;
	// Forward
	net_->Forward();
	// Save out to image
	//Blob<float>* output_layer = net_->output_blobs()[0];
	Blob<float>* output_layer = net_->output_blobs()[2];
	cv::Mat output(input_geometry_, CV_32FC1, (float *)(output_layer->mutable_cpu_data()));
	for(int i = 0; i < 100; ++i){
		std::cout << output.at<float>(i,50) << " ";
	}
	cv::imwrite(output_image, output * 255);
	return 0;
}

DeepSergal::~DeepSergal() {
	// TODO Auto-generated destructor stub
}

