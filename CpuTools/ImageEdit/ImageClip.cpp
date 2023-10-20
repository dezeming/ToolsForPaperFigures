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

#include "ImageClip.hpp"
#include "CpuTools/Utility/cvMat.hpp"

namespace cputools {


bool ImageClip(
	const cv::Mat& inputMat, 
	cv::Mat& outputMat, 
	const ClipConfig& clipCfg) {

	if (!isCvMatHasData(inputMat)) {
		Error_EmptyMat();
		return false;
	}

	int start_w, start_h, offset_w, offset_h;
	if ((clipCfg.index[0] < 0)) {
		if (clipCfg.needClampped) {
			Warning_ExceedingImageBoundaries();
			start_w = 0;
		}
		else {
			Error_ExceedingImageBoundaries();
			return false;
		}
	}
	else start_w = clipCfg.index[0];

	if ((clipCfg.index[1] < 0)) {
		if (clipCfg.needClampped) {
			Warning_ExceedingImageBoundaries();
			start_h = 0;
		}
		else {
			Error_ExceedingImageBoundaries();
			return false;
		}
	}
	else start_h = clipCfg.index[1];

	if ((clipCfg.isOffset && clipCfg.index[0] + clipCfg.index[2] >= inputMat.cols) || 
		(!clipCfg.isOffset && clipCfg.index[2] >= inputMat.cols)) {
		if (clipCfg.needClampped) {
			Warning_ExceedingImageBoundaries();
			offset_w = inputMat.cols - start_w;
		}
		else {
			Error_ExceedingImageBoundaries();
			return false;
		}
	}
	else {
		if (clipCfg.isOffset) offset_w = clipCfg.index[2];	
		else offset_w = clipCfg.index[2] - start_w;	
	}

	if ((clipCfg.isOffset && clipCfg.index[1] + clipCfg.index[3] >= inputMat.rows) ||
		(!clipCfg.isOffset && clipCfg.index[1] >= inputMat.rows)) {
		if (clipCfg.needClampped) {
			Warning_ExceedingImageBoundaries();
			offset_h = inputMat.rows - start_h;
		}
		else {
			Error_ExceedingImageBoundaries();
			return false;
		}
	}
	else {
		if (clipCfg.isOffset) offset_h = clipCfg.index[3];
		else offset_h = clipCfg.index[3] - start_h;
	}

	cv::Mat image_part = inputMat(cv::Rect(start_w, start_h, offset_w, offset_h));
	image_part.copyTo(outputMat);


	return true;
}


bool ImageClip(
	const std::string inputFileName, 
	const std::string outputFileName, 
	const ClipConfig& clipCfg) {

	cv::Mat srcImage = cv::imread(inputFileName, cv::IMREAD_UNCHANGED);
	cv::Mat outImage;

	bool flag = ImageClip(srcImage, outImage, clipCfg);
	if (flag)
		cv::imwrite(outputFileName, outImage);

	return flag;
}





}











