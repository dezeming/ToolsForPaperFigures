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

#include "ImageCircleAreas.hpp"
#include "CpuTools/Utility/cvMat.hpp"

namespace cputools {


bool Image_CircleAreas_usingRound(
	const cv::Mat& inputMat,
	cv::Mat& outputMat,
	const CircleRoundConfig& circleConfig) {

	if (!isCvMatHasData(inputMat)) {
		Error_EmptyMat();
		return false;
	}

	if (circleConfig.radius < 0.f) {
		Print_CPU_Error("(circleConfig.radius < 0.f)");
		return false;
	}
	if (circleConfig.lineWidth < 0) {
		Print_CPU_Error("(circleConfig.lineWidth < 0)");
		return false;
	}

	//if (circleConfig.center[0] - circleConfig.radius - circleConfig.lineWidth < 0 || \
		circleConfig.center[0] + circleConfig.radius + circleConfig.lineWidth >= inputMat.cols || \
		circleConfig.center[1] - circleConfig.radius - circleConfig.lineWidth < 0 || \
		circleConfig.center[1] + circleConfig.radius + circleConfig.lineWidth >= inputMat.rows) 
	if (circleConfig.center[0] - circleConfig.radius < 0 ||
		circleConfig.center[0] + circleConfig.radius >= inputMat.cols ||
		circleConfig.center[1] - circleConfig.radius < 0 ||
		circleConfig.center[1] + circleConfig.radius >= inputMat.rows) {
		Print_CPU_Error("The range of circle exceeds the image boundary");
		return false;
	}

	inputMat.copyTo(outputMat);

	cv::circle(outputMat, 
		cv::Point(circleConfig.center[0], circleConfig.center[1]),
			circleConfig.radius, 
			cv::Scalar(circleConfig.color[0], circleConfig.color[1], circleConfig.color[2], 255),
		circleConfig.lineWidth);
	return true;
}


bool Image_CircleAreas_usingRound(
	std::string inputFilename, 
	std::string outputFileName,
	const CircleRoundConfig& circleConfig) {

	cv::Mat srcImage = cv::imread(inputFilename, cv::IMREAD_UNCHANGED);
	cv::Mat outImage;

	bool flag = Image_CircleAreas_usingRound(srcImage, outImage, circleConfig);
	if (flag)
		cv::imwrite(outputFileName, outImage);

	return flag;
}


bool Image_CircleAreas_usingRectangle(
	const cv::Mat& inputMat,
	cv::Mat& outputMat,
	const CircleRectConfig& circleconfig) {

	if (!isCvMatHasData(inputMat)) {
		Error_EmptyMat();
		return false;
	}

	if (circleconfig.index[0] < 0 ||
		circleconfig.index[0] + circleconfig.index[2] >= inputMat.cols ||
		circleconfig.index[1] < 0 ||
		circleconfig.index[1] + circleconfig.index[2] >= inputMat.rows
		) {
		Print_CPU_Error("The range of circle exceeds the image boundary");
		return false;
	}

	inputMat.copyTo(outputMat);

	int start_w = circleconfig.index[0], start_h = circleconfig.index[1], 
		offset_w = circleconfig.index[2], offset_h = circleconfig.index[3];

	cv::rectangle(outputMat, 
		cv::Point(start_w, start_h),
		cv::Point(start_w + offset_w, start_h + offset_h),
		cv::Scalar(circleconfig.color[0], circleconfig.color[1], circleconfig.color[2], 255), 
		circleconfig.lineWidth);

	return true;
}


bool Image_CircleAreas_usingRectangle(
	std::string inputFilename,
	std::string outputFileName,
	const CircleRectConfig& circleconfig) {

	cv::Mat srcImage = cv::imread(inputFilename, cv::IMREAD_UNCHANGED);
	cv::Mat outImage;

	bool flag = Image_CircleAreas_usingRectangle(srcImage, outImage, circleconfig);
	if (flag)
		cv::imwrite(outputFileName, outImage);

	return flag;
}


bool Image_CircleWholeImage(
	const cv::Mat& inputMat,
	cv::Mat& outputMat,
	const CircleRectConfig& circleconfig) {

	if (!isCvMatHasData(inputMat)) {
		Error_EmptyMat();
		return false;
	}

	inputMat.copyTo(outputMat);

	cv::rectangle(outputMat, cv::Point(0, 0),
		cv::Point(outputMat.cols - 1, outputMat.rows - 1),
		cv::Scalar(circleconfig.color[0], circleconfig.color[1], circleconfig.color[2], 255),
		circleconfig.lineWidth);

	return true;
}


bool Image_CircleWholeImage(
	std::string inputFilename,
	std::string outputFileName,
	const CircleRectConfig& circleconfig) {

	cv::Mat srcImage = cv::imread(inputFilename, cv::IMREAD_UNCHANGED);
	cv::Mat outImage;

	bool flag = Image_CircleWholeImage(srcImage, outImage, circleconfig);
	if (flag)
		cv::imwrite(outputFileName, outImage);

	return flag;
}


bool Image_Clip_and_CircleWholeImage(
	std::string inputFilename,
	std::string outputFileName,
	const ClipConfig& clipconfig,
	const CircleRectConfig& circleconfig) {

	cv::Mat srcImage = cv::imread(inputFilename, cv::IMREAD_UNCHANGED);
	cv::Mat outImage1;

	bool flag = ImageClip(srcImage, outImage1, clipconfig);
	if (!flag) return false;

	cv::Mat outImage2;
	flag = Image_CircleWholeImage(outImage1, outImage2, circleconfig);

	if (flag)
		cv::imwrite(outputFileName, outImage2);

	return flag;
}







}






