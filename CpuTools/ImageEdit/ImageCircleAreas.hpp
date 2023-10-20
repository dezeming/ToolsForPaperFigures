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

#ifndef __ImageCircleAreas_hpp__
#define __ImageCircleAreas_hpp__

#include "ImageClip.hpp"

namespace cputools {


struct CircleRoundConfig {
	CircleRoundConfig(
		int cent[2], 
		float radius,
		unsigned char c[3],
		int linewidth)
		: lineWidth(linewidth),
		radius(radius)
	{
		center[0] = cent[0]; center[1] = cent[1];
		color[0] = c[0]; color[1] = c[1]; color[2] = c[2];
	}

	CircleRoundConfig(
		int cent0, int cent1, 
		float radius, 
		unsigned char c[3], 
		int linewidth)
		: lineWidth(linewidth),
		radius(radius)
	{
		center[0] = cent0; center[1] = cent1;
		color[0] = c[0]; color[1] = c[1]; color[2] = c[2];
	}

	int center[2];
	float radius;
	int lineWidth;
	unsigned char color[3];
};

/** Circle the image using a rectangle
* Only used for CV_8U_C3/CV_8U_C4
*/
bool Image_CircleAreas_usingRound(
	const cv::Mat& inputMat,
	cv::Mat& outputMat,
	const CircleRoundConfig& circleConfig);

/** Circle the image using a circle
* Only used for PNG/JPG
*/
bool Image_CircleAreas_usingRound(
	std::string inputFilename, 
	std::string outputFileName,
	const CircleRoundConfig& circleConfig);


struct CircleRectConfig {
	CircleRectConfig(int idx0, int idx1, int idx2, int idx3, unsigned char c[3], int linewidth)
		: lineWidth(linewidth)
	{
		index[0] = idx0; index[1] = idx1; index[2] = idx2; index[3] = idx3;
		color[0] = c[0]; color[1] = c[1]; color[2] = c[2];
	}
	CircleRectConfig(int idx[4], unsigned char c[3], int linewidth)
		: lineWidth(linewidth)
	{
		index[0] = idx[0]; index[1] = idx[1]; index[2] = idx[2]; index[3] = idx[3];
		color[0] = c[0]; color[1] = c[1]; color[2] = c[2];
	}
	CircleRectConfig(
		int idx0, int idx1, int idx2, int idx3, 
		unsigned char c0, unsigned char c1, unsigned char c2,
		int linewidth)
		: lineWidth(linewidth)
	{
		index[0] = idx0; index[1] = idx1; index[2] = idx2; index[3] = idx3;
		color[0] = c0; color[1] = c1; color[2] = c2;
	}

	int index[4];
	int lineWidth;
	unsigned char color[3];
};

/** Circle the image using a rectangle
* Only used for CV_8U_C3/CV_8U_C4
*/
bool Image_CircleAreas_usingRectangle(
	const cv::Mat& inputMat,
	cv::Mat& outputMat,
	const CircleRectConfig& circleconfig);

/** Circle the image using a rectangle
* Only used for PNG/JPG
*/
bool Image_CircleAreas_usingRectangle(
	std::string inputFilename, 
	std::string outputFileName,
	const CircleRectConfig& circleconfig);

/** Circle the whole image
* Only used for PNG/JPG
* Add a border to the entire image
*/
bool Image_CircleWholeImage(
	const cv::Mat& inputMat,
	cv::Mat& outputMat,
	const CircleRectConfig& circleconfig);

/** Circle the whole image
* Only used for PNG/JPG
* Add a border to the entire image
*/
bool Image_CircleWholeImage(
	std::string inputFilename, 
	std::string outputFileName,
	const CircleRectConfig& circleconfig);

/** Clip Image and add a color border to the clipped image
* Only used for PNG/JPG
*/
bool Image_Clip_and_CircleWholeImage(
	std::string inputFilename, 
	std::string outputFileName,
	const ClipConfig& clipconfig, 
	const CircleRectConfig& circleconfig);



}



#endif







