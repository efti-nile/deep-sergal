/*
 * DeepSergal.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: efti-nile
 */

#include "DeepSergal.hpp"

DeepSergal::DeepSergal(const string& model_file,
			   	   	   const string& trained_file,
					   const string& mean_file,
					   const string& label_file){

	Caffe::set_mode(Caffe::GPU);

	net_.reset(new Net<float>(model_file, TEST));
}

DeepSergal::~DeepSergal() {
	// TODO Auto-generated destructor stub
}

