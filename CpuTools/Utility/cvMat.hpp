/**
Copyright (C) <2023>  <Dezeming>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#ifndef __cvMat_h__
#define __cvMat_h__

#include "CpuTools/Common/cpu_Common.hpp"

namespace cputools {


/**
*/
inline cv::Mat createFloatCvMat(const int width, const int height, const int channel) {
	cv::Mat m;
	if (width == 0 || height == 0 || channel == 0) {
		Print_CPU_Error("(width == 0 || height == 0 || channel == 0)");
		return m;
	}
	if (4 == channel)
		m.create(height, width, CV_32FC4);
	else if (3 == channel)
		m.create(height, width, CV_32FC3);
	else if (1 == channel)
		m.create(height, width, CV_32FC1);
	else {
		Print_CPU_Error("Illegal number of image channels");
	}
	return m.clone();
}

/**
*/
inline cv::Mat createUcharCvMat(const int width, const int height, const int channel) {
	cv::Mat m;
	if (width == 0 || height == 0 || channel == 0) {
		Print_CPU_Error("(width == 0 || height == 0 || channel == 0)");
		return m;
	}
	if (4 == channel)
		m.create(height, width, CV_8UC4);
	else if (3 == channel)
		m.create(height, width, CV_8UC3);
	else if (1 == channel)
		m.create(height, width, CV_8UC1);
	else {
		Print_CPU_Error("Illegal number of image channels");
	}
	return m.clone();

}

/**
*/
bool CvMatResize(cv::Mat& srcImage, ImageSize size);

/**
*/
bool CvMatResize(cv::Mat& srcImage, float scale);

/**
*/
bool CvMatResize(std::string srcImage, std::string outImage, float scale);


inline bool isMatHasSameWH(const cv::Mat& mat1, const cv::Mat& mat2) {
	if (mat1.rows != mat2.rows || mat1.cols != mat2.cols) {
		return false;
	}
	return true;
}

inline bool isMatHasSameType(const cv::Mat& mat1, const cv::Mat& mat2) {
	if (mat1.type() != mat2.type()) {
		return false;
	}
	return true;
}

inline bool isMatHasSameSize(const cv::Mat& mat1, const cv::Mat& mat2) {
	if (mat1.rows != mat2.rows || mat1.cols != mat2.cols || mat1.channels() != mat2.channels()) {
		return false;
	}
	return true;
}

inline bool isMatHasSameWH(const cv::Mat& mat1, const cv::Mat& mat2, const cv::Mat& mat3) {

	if (mat1.rows != mat2.rows || mat1.rows != mat3.rows) {
		return false;
	}
	if (mat1.cols != mat2.cols || mat1.cols != mat3.cols) {
		return false;
	}
	return true;
}

inline bool isMatHasSameSize(const cv::Mat& mat1, const cv::Mat& mat2, const cv::Mat& mat3) {

	if (mat1.rows != mat2.rows || mat1.rows != mat3.rows) {
		return false;
	}
	if (mat1.cols != mat2.cols || mat1.cols != mat3.cols) {
		return false;
	}
	if (mat1.channels() != mat2.channels() || mat1.channels() != mat3.channels()) {
		return false;
	}
	return true;
}


inline bool isCvMatHasData(const cv::Mat& srcImage) {
	if (!srcImage.data)return false;
	if (srcImage.cols == 0 || srcImage.rows == 0 || srcImage.channels() == 0) return false;
	return true;
}

inline bool isCvMatTypeEquals8U(const cv::Mat& srcImage) {
	if (srcImage.type() == CV_8UC1 ||
		srcImage.type() == CV_8UC2 ||
		srcImage.type() == CV_8UC3 ||
		srcImage.type() == CV_8UC4) { return true; }
	else return false;
}

inline bool isCvMatTypeEquals32F(const cv::Mat& srcImage) {
	if (srcImage.type() == CV_32FC1 ||
		srcImage.type() == CV_32FC2 ||
		srcImage.type() == CV_32FC3 ||
		srcImage.type() == CV_32FC4) {
		return true;
	}
	else return false;
}

inline bool getImageSizeFromCvMat(const cv::Mat& srcImage, ImageSize& size) {
	if (!srcImage.data) {
		size.height = size.width = size.channels = 0;
	}
	else {
		size.height = srcImage.rows;
		size.width = srcImage.cols;
		size.channels = srcImage.channels();
	}
	return true;
}


/**
*/
inline bool UcharCvMat2FloatCvMat(
	const cv::Mat& srcImage, 
	cv::Mat& outputImage, 
	const float scale = 1.0f / 255.0f) {
	if (!isCvMatHasData(srcImage)) {
		Error_EmptyMat();
		return false;
	}
	if (!isCvMatTypeEquals8U(srcImage)) {
		Error_IllegalImageType();
		return false;
	}

	outputImage.release();
	outputImage = createFloatCvMat(srcImage.cols, srcImage.rows, srcImage.channels());
	if (!isCvMatHasData(outputImage)) {
		Error_EmptyMat();
		return false;
	}

	int channel = srcImage.channels();
	unsigned char* data = (unsigned char*)srcImage.data;
	float* dataOut = (float*)outputImage.data;
	for (int i = 0; i < srcImage.cols; i++) {
		for (int j = 0; j < srcImage.rows; j++) {
			int offset = (i + j * srcImage.cols) * channel;

			for (int k = 0; k < channel; k++) {
				dataOut[offset + k] = data[offset + k] * scale;
			}
		}
	}
	return true;
}

/**
*/
inline bool FloatCvMat2UcharCvMat(
	const cv::Mat& srcImage, 
	cv::Mat& outputImage, 
	const float scale = 255.0f) {
	if (!isCvMatHasData(srcImage)) {
		Error_EmptyMat();
		return false;
	}
	if (!isCvMatTypeEquals32F(srcImage)) {
		Error_IllegalImageType();
		return false;
	}

	outputImage.release();
	outputImage = createUcharCvMat(srcImage.cols, srcImage.rows, srcImage.channels());
	if (!isCvMatHasData(outputImage)) {
		Error_EmptyMat();
		return false;
	}

	int channel = srcImage.channels();
		
	float* data = (float*)srcImage.data;
	unsigned char* dataOut = (unsigned char*)outputImage.data;

	for (int i = 0; i < srcImage.cols; i++) {
		for (int j = 0; j < srcImage.rows; j++) {
			int offset = (i + j * srcImage.cols) * channel;
			for (int k = 0; k < channel; k++) {

				dataOut[offset + k] = (unsigned char)(data[offset + k] * scale);
			}
		}
	}
	return true;

}





}



#endif








