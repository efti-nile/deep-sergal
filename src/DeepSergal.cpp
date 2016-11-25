/*
 * DeepSergal.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: efti-nile
 */

#include "DeepSergal.hpp"

DeepSergal::DeepSergal(const string& model_file, const string& trained_file){

	Caffe::set_mode(Caffe::CPU);

	net_.reset(new Net<float>(model_file, TRAIN));
	net_->CopyTrainedLayersFrom(trained_file);

	std::cout << "Number of inputs: " << net_->num_inputs() << std::endl;
	std::cout << "Number of outputs: " << net_->num_outputs() << std::endl;
	std::cout << std::endl;

	for(int i = 0; i < net_->num_outputs(); ++i){
		std::cout << "shape string for net_.output_blobs()[" \
		          << i << "]: " << net_->output_blobs()[i]->shape_string() << std::endl;
	}
	std::cout << std::endl;

	const vector< Blob<float> * > &lp = net_->learnable_params();
	for(unsigned int i = 0; i < lp.size(); ++i){
		std::cout << "shape string for learnable blob #" << i << ": " << lp[i]->shape_string() << std::endl;
	}
	std::cout << std::endl;

	const vector< string > &blob_names = net_->blob_names();
	std::cout << "List of all blobs' names:" << std::endl;
	for(unsigned int i = 0; i < blob_names.size(); ++i){
		std::cout << blob_names[i] << std::endl;
	}
	std::cout << std::endl;

//	const vector< string > &param_display_names = net_->param_display_names();
//	std::cout << "List of all params' display names" << std::endl;
//	for(unsigned int i = 0; i < param_display_names.size(); ++i){
//		std::cout << param_display_names[i] << std::endl;
//	}

//	input_geometry_ = cv::Size(net_->input_blobs()[0]->width(), net_->input_blobs()[0]->height());

	input_geometry_ = cv::Size(100, 100);
	output_geometry_ = input_geometry_;
}

int DeepSergal::ProcessRandomImageFromTrainingDB(const string& sketch, const string& line, const string& out) {

	net_->Forward(); // Some image automatically loaded from training LMDB database

	// Save sketch image from training LMDB database
	shared_ptr< Blob<float> > sketch_blob = net_->blob_by_name("sketch");
	cv::Mat sketch_mat(input_geometry_, CV_32FC1, (float *)(sketch_blob->mutable_cpu_data()));
	cv::imwrite(sketch, sketch_mat * 256);

	// Save line image from training LMDB database
	if(net_->phase() == TRAIN){
		shared_ptr< Blob<float> > line_blob = net_->blob_by_name("line");
		cv::Mat line_mat(input_geometry_, CV_32FC1, (float *)(line_blob->mutable_cpu_data()));
		cv::imwrite(line, line_mat * 256);
	}

	// Save output image from the last layer
	shared_ptr< Blob<float> > out_blob = net_->blob_by_name("out");
	cv::Mat out_mat(output_geometry_, CV_32FC1, (float *)(out_blob->mutable_cpu_data()));
	cv::imwrite(out, out_mat * 256);

	return 0;
}

void DeepSergal::SaveParamsToImage(const string& base_folder_name){
	const vector< Blob<float> * > &lp = net_->learnable_params();
	int conv_layer_num = 0; // Global convolutional layer number
	for(unsigned int blob_num = 0; blob_num < lp.size(); ++blob_num){
		const vector< int > &shape = lp[blob_num]->shape();
		if(shape.size() == 4){
			std::stringstream prefix;
			prefix << base_folder_name << "-" << conv_layer_num;
			mkdir(prefix.str().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
			for(unsigned int out_num = 0; out_num < shape[0]; ++out_num){
				for(unsigned int in_num = 0; in_num < shape[1]; ++in_num){
					int offset = lp[blob_num]->offset(out_num, in_num);
					cv::Size kernel_shape = cv::Size(shape[2], shape[3]);
					cv::Mat kernel_mat(kernel_shape, CV_32FC1, \
							(float *)(lp[blob_num]->mutable_cpu_data() + offset));
					cv::Mat kernel_norm_mat(kernel_shape, CV_32FC1);
					cv::normalize(kernel_mat, kernel_norm_mat, 0, 255, cv::NORM_MINMAX, CV_32FC1);
					std::stringstream output_file_name;
					output_file_name << prefix.str() << "/ker-" << out_num << "-" << in_num << ".png";
					cv::imwrite(output_file_name.str(), kernel_norm_mat);
//					std::cout << output_file_name.str() << std::endl;
				}
			}
			conv_layer_num++;
		}
	}
}

DeepSergal::~DeepSergal() {
	// TODO Auto-generated destructor stub
}

