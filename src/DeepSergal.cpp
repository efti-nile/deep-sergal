/*
 * DeepSergal.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: efti-nile
 */

#include "DeepSergal.hpp"

DeepSergal::DeepSergal(const string& model_file, const string& trained_file){

	Caffe::set_mode(Caffe::CPU);

	net_.reset(new Net<float>(model_file, TEST));
	net_->CopyTrainedLayersFrom(trained_file);

	std::cout << "Number of inputs: " << net_->num_inputs() << std::endl;

	std::cout << "Number of outputs: " << net_->num_outputs() << std::endl;

	for(int i = 0; i < net_->num_outputs(); ++i){
		std::cout << "shape string for net_.output_blobs()[" \
		          << i << "]: " << net_->output_blobs()[i]->shape_string() << std::endl;
	}

	//input_geometry_ = cv::Size(net_->input_blobs()[0]->width(), net_->input_blobs()[0]->height());
	input_geometry_ = cv::Size(300, 450);
	output_geometry_ = input_geometry_;
}

int DeepSergal::ProcessRandomImageFromTrainingDB(const string& sketch, const string& line, const string& out) {

	net_->Forward(); // Some image automatically loaded from training LMDB database

	// Save sketch image from training LMDB database
	shared_ptr< Blob<float> > sketch_blob = net_->blob_by_name("sketch");
	cv::Mat sketch_mat(input_geometry_, CV_32FC1, (float *)(sketch_blob->mutable_cpu_data()));
	cv::imwrite(sketch, sketch_mat * 256);

	// Save line image from training LMDB database
	//shared_ptr< Blob<float> > line_blob = net_->blob_by_name("line");
	//cv::Mat line_mat(input_geometry_, CV_32FC1, (float *)(line_blob->mutable_cpu_data()));
	//cv::imwrite(line, line_mat * 256);

	// Save output image from the last layer
	shared_ptr< Blob<float> > out_blob = net_->blob_by_name("out");
	cv::Mat out_mat(output_geometry_, CV_32FC1, (float *)(out_blob->mutable_cpu_data()));
	cv::imwrite(out, out_mat * 256);

	return 0;
}

DeepSergal::~DeepSergal() {
	// TODO Auto-generated destructor stub
}

